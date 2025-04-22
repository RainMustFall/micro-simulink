#include <QtTest>
#include <numbers>

#include "binary_operator.h"
#include "function.h"
#include "graph_controller.h"
#include "scalar.h"
#include "scalar_node.h"
#include "scalar_result_factory.h"
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
  auto root = controller.AddRootNode();

  auto five = controller.AddScalarNode(5);
  auto plus = controller.AddPlusNode();
  auto three = controller.AddScalarNode(3);

  controller.ConnectNodes(five, plus, 0);
  controller.ConnectNodes(three, plus, 1);
  controller.ConnectNodes(plus, root, 0);

  QCOMPARE(controller.GetGraphResult(), 8);
}

void TestNumericGraph::testLatexExpression() {
  auto controller = GraphController();
  auto root = controller.AddRootNode();

  auto x = controller.AddXNode();
  auto plus = controller.AddPlusNode();
  auto three = controller.AddScalarNode(3);

  controller.ConnectNodes(x, plus, 0);
  controller.ConnectNodes(three, plus, 1);
  controller.ConnectNodes(plus, root, 0);

  QCOMPARE(controller.GetLatex(), "x+3");
}

void TestNumericGraph::testIntegral() {
  auto controller = GraphController();
  auto root = controller.AddRootNode();

  auto x = controller.AddXNode();
  auto integral = controller.AddIntegralNode(0, 1);

  controller.ConnectNodes(x, integral, 0);
  controller.ConnectNodes(integral, root, 0);

  QCOMPARE(controller.GetGraphResult(), 0.5);
}

void TestNumericGraph::testSinus() {
  auto controller = GraphController();
  auto root = controller.AddRootNode();

  auto half_pi = controller.AddScalarNode(std::numbers::pi_v<double> / 2);
  auto sinus = controller.AddSineNode();

  controller.ConnectNodes(half_pi, sinus, 0);
  controller.ConnectNodes(sinus, root, 0);

  QCOMPARE(controller.GetGraphResult(), 1);
}

void TestNumericGraph::testCotangent() {
  auto controller = GraphController();
  auto root = controller.AddRootNode();

  auto pi = controller.AddScalarNode(std::asin(0));
  auto cotangent = controller.AddCotangentNode();

  controller.ConnectNodes(pi, cotangent, 0);
  controller.ConnectNodes(cotangent, root, 0);

  QCOMPARE(controller.GetGraphResult(),
           std::numeric_limits<double>::infinity());
}

void TestNumericGraph::nestedTrigonometry() {
  auto controller = GraphController();
  auto root = controller.AddRootNode();

  auto x = controller.AddXNode();
  auto sin_inner = controller.AddSineNode();
  auto sin_outer = controller.AddSineNode();
  auto integral = controller.AddIntegralNode(-1, 1);

  controller.ConnectNodes(x, sin_inner, 0);
  controller.ConnectNodes(sin_inner, sin_outer, 0);
  controller.ConnectNodes(sin_outer, integral, 0);
  controller.ConnectNodes(integral, root, 0);

  // About zero
  QVERIFY(std::fabs(controller.GetGraphResult() < 1e-15));
}

QTEST_APPLESS_MAIN(TestNumericGraph)

#include "tst_testnumericgraph.moc"
