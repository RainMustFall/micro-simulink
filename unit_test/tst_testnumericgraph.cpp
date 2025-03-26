#include <QtTest>

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
  void testGraphController();
};

void TestNumericGraph::testAddTwoNumbers() {
  auto two = ScalarNode<Function>(2);
  auto plus = PlusOperator<Function>();
  auto three = ScalarNode<Function>(3);

  plus.AttachInput(0, two).AttachInput(1, three);

  std::unique_ptr<Function> result = plus.Execute(FunctionFactory());
  auto scalar = static_cast<Scalar&>(*result);

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

void TestNumericGraph::testGraphController() {
  auto controller = GraphController();
  controller.AddRootNode();

  auto five = controller.AddScalarNode(5);
  auto plus = controller.AddPlusNode();
  auto three = controller.AddScalarNode(3);

  controller.ConnectNodes(five, plus, 0);
  controller.ConnectNodes(three, plus, 1);
  controller.ConnectNodes(plus, GraphController::kRootIndex, 0);

  QCOMPARE(controller.GetGraphResult(), 8);
}

QTEST_APPLESS_MAIN(TestNumericGraph)

#include "tst_testnumericgraph.moc"
