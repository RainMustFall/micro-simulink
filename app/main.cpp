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

  QMainWindow mainWindow;
  mainWindow.setWindowTitle("Simulink Prototype");

  // Create the central widget
  QWidget* centralWidget = new QWidget(&mainWindow);
  QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

  GraphController controller;
  NodeDragBuffer dragBuffer;

  // Create the graph widget
  GraphWidget* graphWidget = new GraphWidget(&controller, &dragBuffer);
  mainLayout->addWidget(graphWidget);

  // Create the right panel
  QWidget* rightPanel = new QWidget();
  rightPanel->setFixedWidth(200);
  QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);

  // Create the node palette
  NodePalette* nodePalette = new NodePalette(&controller, &dragBuffer);
  CalculationWidget* calcWidget =
      new CalculationWidget(&controller, rightPanel);
  LatexDisplayWidget* latex_widget = new LatexDisplayWidget(&controller);

  graphWidget->connect(graphWidget, &GraphWidget::graphEdited, latex_widget,
                       &LatexDisplayWidget::updatePreviewBuilderThreadInput,
                       Qt::QueuedConnection);

  rightLayout->addWidget(calcWidget);
  rightLayout->addWidget(latex_widget);
  rightLayout->addStretch();
  rightLayout->addWidget(nodePalette);

  mainLayout->addWidget(rightPanel);

  mainWindow.setCentralWidget(centralWidget);
  mainWindow.setGeometry(100, 100, 1000, 600);
  mainWindow.show();

  return app.exec();
}
