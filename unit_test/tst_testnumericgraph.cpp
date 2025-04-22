#include <QtTest>
#include <numbers>

#include "binary_operator.h"
#include "function.h"
#include "graph_controller.h"
#include "integral_node.h"
#include "negation_node.h"
#include "root_node.h"
#include "scalar.h"
#include "scalar_node.h"
#include "scalar_result_factory.h"
#include "trigonometry.h"
#include "x_node.h"

class TestNumericGraph : public QObject {
  Q_OBJECT
 private slots:
  void testAddTwoNumbers();
  void testXPlusOne();
  void testXPlusOneIsNotScalar();
  void testGraphController();
  void testLatexExpression();
  void testIntegral();
  void testSinus();
  void testCotangent();
  void nestedTrigonometry();
  void testMinus();
  void testDivide();
  void testPower();
  void testNegationParentheses();
};

void TestNumericGraph::testAddTwoNumbers() {
  auto two = ScalarNode<Function>(2);
  auto plus = PlusOperator<Function>();
  auto three = ScalarNode<Function>(3);

  plus.AttachInput(0, two).AttachInput(1, three);

  std::unique_ptr<Function> result = plus.Execute(FunctionFactory());
  auto scalar = dynamic_cast<Scalar&>(*result);

  QCOMPARE(scalar.GetValue(), 5);
}

void TestNumericGraph::testXPlusOne() {
  auto x = XNode<Function>();
  auto plus = PlusOperator<Function>();
  auto one = ScalarNode<Function>(1);

  plus.AttachInput(0, x).AttachInput(1, one);

  std::unique_ptr<Function> result = plus.Execute(FunctionFactory());
  auto function = *result;

  QCOMPARE(function(0), 1);
  QCOMPARE(function(1), 2);
  QCOMPARE(function(2), 3);
}

void TestNumericGraph::testXPlusOneIsNotScalar() {
  auto x = XNode<Function>();
  auto plus = PlusOperator<Function>();
  auto one = ScalarNode<Function>(1);

  plus.AttachInput(0, x).AttachInput(1, one);

  std::unique_ptr<Function> result = plus.Execute(FunctionFactory());

  // There is X in the expression, so cast to Scalar should fail
  QCOMPARE(dynamic_cast<Scalar*>(result.get()), nullptr);
}

void TestNumericGraph::testGraphController() {
  auto controller = GraphController();
  auto root = controller.AddNode<RootNode>();

  auto five = controller.AddNode<ScalarNode>(5);
  auto plus = controller.AddNode<PlusOperator>();
  auto three = controller.AddNode<ScalarNode>(3);

  controller.ConnectNodes(five, plus, 0);
  controller.ConnectNodes(three, plus, 1);
  controller.ConnectNodes(plus, root, 0);

  QCOMPARE(controller.GetGraphResult(), 8);
}

void TestNumericGraph::testLatexExpression() {
  auto controller = GraphController();
  auto root = controller.AddNode<RootNode>();

  auto x = controller.AddNode<XNode>();
  auto plus = controller.AddNode<PlusOperator>();
  auto three = controller.AddNode<ScalarNode>(3);

  controller.ConnectNodes(x, plus, 0);
  controller.ConnectNodes(three, plus, 1);
  controller.ConnectNodes(plus, root, 0);

  QCOMPARE(controller.GetLatex(), "x+3");
}

void TestNumericGraph::testIntegral() {
  auto controller = GraphController();
  auto root = controller.AddNode<RootNode>();

  auto x = controller.AddNode<XNode>();
  auto integral = controller.AddNode<IntegralNode>(0, 1);

  controller.ConnectNodes(x, integral, 0);
  controller.ConnectNodes(integral, root, 0);

  QCOMPARE(controller.GetGraphResult(), 0.5);
}

void TestNumericGraph::testSinus() {
  auto controller = GraphController();
  auto root = controller.AddNode<RootNode>();

  auto half_pi = controller.AddNode<ScalarNode>(std::numbers::pi_v<double> / 2);
  auto sinus = controller.AddNode<SineNode>();

  controller.ConnectNodes(half_pi, sinus, 0);
  controller.ConnectNodes(sinus, root, 0);

  QCOMPARE(controller.GetGraphResult(), 1);
}

void TestNumericGraph::testCotangent() {
  auto controller = GraphController();
  auto root = controller.AddNode<RootNode>();

  auto pi = controller.AddNode<ScalarNode>(std::asin(0));
  auto cotangent = controller.AddNode<CotangentNode>();

  controller.ConnectNodes(pi, cotangent, 0);
  controller.ConnectNodes(cotangent, root, 0);

  QCOMPARE(controller.GetGraphResult(),
           std::numeric_limits<double>::infinity());
}

void TestNumericGraph::nestedTrigonometry() {
  auto controller = GraphController();
  auto root = controller.AddNode<RootNode>();

  auto x = controller.AddNode<XNode>();
  auto sin_inner = controller.AddNode<SineNode>();
  auto sin_outer = controller.AddNode<SineNode>();
  auto integral = controller.AddNode<IntegralNode>(-1, 1);

  controller.ConnectNodes(x, sin_inner, 0);
  controller.ConnectNodes(sin_inner, sin_outer, 0);
  controller.ConnectNodes(sin_outer, integral, 0);
  controller.ConnectNodes(integral, root, 0);

  // About zero
  QVERIFY(std::fabs(controller.GetGraphResult() < 1e-15));
}

void TestNumericGraph::testPower() {
  auto controller = GraphController();
  auto root = controller.AddNode<RootNode>();

  auto two = controller.AddNode<ScalarNode>(2);
  auto pow = controller.AddNode<PowerOperator>();
  auto three = controller.AddNode<ScalarNode>(3);

  controller.ConnectNodes(two, pow, 0);
  controller.ConnectNodes(three, pow, 1);
  controller.ConnectNodes(pow, root, 0);

  QCOMPARE(controller.GetGraphResult(), 8);
}

void TestNumericGraph::testDivide() {
  auto controller = GraphController();
  auto root = controller.AddNode<RootNode>();

  auto one = controller.AddNode<ScalarNode>(1);
  auto divides = controller.AddNode<DividesOperator>();
  auto two = controller.AddNode<ScalarNode>(2);

  controller.ConnectNodes(one, divides, 0);
  controller.ConnectNodes(two, divides, 1);
  controller.ConnectNodes(divides, root, 0);

  QCOMPARE(controller.GetGraphResult(), 0.5);

  controller.SetScalarValue(two, 0);
  QCOMPARE(controller.GetGraphResult(),
           std::numeric_limits<double>::infinity());
}

void TestNumericGraph::testMinus() {
  auto controller = GraphController();
  auto root = controller.AddNode<RootNode>();

  auto two = controller.AddNode<ScalarNode>(2);
  auto minus = controller.AddNode<MinusOperator>();
  auto one = controller.AddNode<ScalarNode>(1);

  controller.ConnectNodes(two, minus, 0);
  controller.ConnectNodes(one, minus, 1);
  controller.ConnectNodes(minus, root, 0);

  QCOMPARE(controller.GetGraphResult(), 1);
}

void TestNumericGraph::testNegationParentheses() {
  auto controller = GraphController();
  auto root = controller.AddNode<RootNode>();

  auto two = controller.AddNode<ScalarNode>(2);
  auto minus = controller.AddNode<MinusOperator>();
  auto minus_one = controller.AddNode<ScalarNode>(-1);
  auto outer_minus = controller.AddNode<NegationNode>();

  controller.ConnectNodes(two, minus, 0);
  controller.ConnectNodes(minus_one, minus, 1);
  controller.ConnectNodes(minus, outer_minus, 0);
  controller.ConnectNodes(outer_minus, root, 0);

  QCOMPARE(controller.GetLatex(), "-\\left(2-\\left(-1\\right)\\right)");
}

QTEST_APPLESS_MAIN(TestNumericGraph)

#include "tst_testnumericgraph.moc"
