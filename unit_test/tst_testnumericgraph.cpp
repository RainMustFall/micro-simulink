#include <QtTest>

class TestNumericGraph : public QObject {
  Q_OBJECT
 private slots:
  void testBasic();
};

void TestNumericGraph::testBasic() { QCOMPARE(2 + 2, 4); }

QTEST_APPLESS_MAIN(TestNumericGraph)

#include "tst_testnumericgraph.moc"
