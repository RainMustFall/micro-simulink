#include <QtTest>

#include "binary_operator.h"
#include "scalar.h"
#include "scalar_result.h"
#include "scalar_result_factory.h"

class TestNumericGraph : public QObject {
  Q_OBJECT
 private slots:
  void testAddTwoNumbers();
};

void TestNumericGraph::testAddTwoNumbers() {
  auto two = Scalar(2);
  auto three = Scalar(3);
  auto plus = PlusOperator();
  auto scalar_factory = ScalarResultFactory();

  plus.AttachInput(0, two).AttachInput(1, three);
  auto result = plus.Execute(scalar_factory);

  QCOMPARE(static_cast<ScalarResult&>(*result).GetValue(), 5);
}

QTEST_APPLESS_MAIN(TestNumericGraph)

#include "tst_testnumericgraph.moc"
