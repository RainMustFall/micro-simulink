#include <QDir>
#include <QSplitter>
#include <QTranslator>
#include <QtCore/QPointF>
#include <QtCore/QRectF>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <cmath>

#include "calculation_widget.h"
#include "graph_widget.h"
#include "latex_display_widget.h"
#include "node_drag_buffer.h"
#include "node_palette.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  QTranslator translator;
  if (!translator.load(":/i18n/app_en_US")) {
    qDebug() << "Could not load translation file" << QDir::currentPath();
    return 1;
  }

  if (!QCoreApplication::installTranslator(&translator)) {
    qDebug() << "Could not apply translator";
    return 1;
  }

  QMainWindow mainWindow;
  mainWindow.setWindowTitle("Simulink Prototype");

  // Create the central widget
  QWidget* centralWidget = new QWidget(&mainWindow);
  QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

  QSplitter* splitter = new QSplitter(centralWidget);
  mainLayout->addWidget(splitter);

  GraphController controller;
  NodeDragBuffer dragBuffer;

  // Create the graph widget
  GraphWidget* graphWidget = new GraphWidget(&controller, &dragBuffer);
  splitter->addWidget(graphWidget);

  // Create the right panel
  QWidget* rightPanel = new QWidget();
  QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);

  // Create the node palette
  NodePalette* nodePalette = new NodePalette(&controller, &dragBuffer);
  CalculationWidget* calcWidget =
      new CalculationWidget(&controller, rightPanel);
  LatexDisplayWidget* latex_widget = new LatexDisplayWidget(&controller);

  rightLayout->addWidget(calcWidget);
  rightLayout->addWidget(latex_widget);
  rightLayout->addStretch();
  rightLayout->addWidget(nodePalette);

  splitter->addWidget(rightPanel);

  mainWindow.setCentralWidget(centralWidget);
  mainWindow.setGeometry(100, 100, 1000, 600);
  splitter->setSizes({mainWindow.width() - 200, 200});
  mainWindow.show();

  return app.exec();
}
