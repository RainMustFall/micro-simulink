#include <QtTest>

#include "binary_operator.h"
#include "scalar.h"
#include "function.h"
#include "scalar_node.h"
#include "x_node.h"
#include "scalar_result_factory.h"

class TestNumericGraph : public QObject {
  Q_OBJECT
 private slots:
  void testAddTwoNumbers();
  void testXPlusOne();
};

void TestNumericGraph::testAddTwoNumbers() {
  auto two = ScalarNode(2);
  auto three = ScalarNode(3);
  auto plus = PlusOperator();
  plus.AttachInput(0, two).AttachInput(1, three);

  auto scalar_factory = ScalarResultFactory();
  auto result = plus.Execute(scalar_factory);
  auto scalar = static_cast<Scalar&>(*result);

  QCOMPARE(scalar.GetValue(), 5);
}

void TestNumericGraph::testXPlusOne() {
  auto x = XNode();
  auto one = ScalarNode(1);
  auto plus = PlusOperator();
  plus.AttachInput(0, x).AttachInput(1, one);

  auto scalar_factory = ScalarResultFactory();
  auto result = plus.Execute(scalar_factory);
  auto function = static_cast<Function&>(*result);

  QCOMPARE(function(0), 1);
  QCOMPARE(function(1), 2);
  QCOMPARE(function(2), 3);
}

QTEST_APPLESS_MAIN(TestNumericGraph)

#include "tst_testnumericgraph.moc"
