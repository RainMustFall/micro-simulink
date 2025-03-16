#include <QtTest>

#include "core.h"

class TestNumericGraph : public QObject {
  Q_OBJECT
 private slots:
  void testBasic();
};

void TestNumericGraph::testBasic() {
    QCOMPARE(Core().GetNumber(), 4);
}

QTEST_APPLESS_MAIN(TestNumericGraph)

#include "tst_testnumericgraph.moc"
