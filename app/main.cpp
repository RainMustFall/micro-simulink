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

#include "graph_widget.h"
#include "node_palette.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  QMainWindow mainWindow;
  mainWindow.setWindowTitle("Simulink Prototype");

  // Create the central widget
  QWidget* centralWidget = new QWidget(&mainWindow);
  QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

  GraphController controller;

  // Create the graph widget
  GraphWidget* graphWidget = new GraphWidget(&controller);
  mainLayout->addWidget(graphWidget);

  // Create the right panel
  QWidget* rightPanel = new QWidget();
  rightPanel->setFixedWidth(200);
  QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);

  // Create the node palette
  NodePalette* nodePalette = new NodePalette();
  rightLayout->addWidget(nodePalette);
  rightLayout->addStretch();

  mainLayout->addWidget(rightPanel);

  mainWindow.setCentralWidget(centralWidget);
  mainWindow.setGeometry(100, 100, 1000, 600);
  mainWindow.show();

  return app.exec();
}
