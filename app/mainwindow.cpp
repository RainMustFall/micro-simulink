#include "mainwindow.h"

#include <QSplitter>

#include "calculation_widget.h"
#include "graph_widget.h"
#include "latex_display_widget.h"
#include "node_palette.h"

MainWindow::MainWindow(const QRect &windowSize, QWidget *parent)
    : QMainWindow(parent) {
  setWindowTitle(qtTrId("window-name"));

  QWidget *centralWidget = new QWidget(this);
  QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
  QSplitter *splitter = new QSplitter(centralWidget);
  mainLayout->addWidget(splitter);

  splitter->addWidget(new GraphWidget(&controller, &dragBuffer));
  splitter->addWidget(createRightPanel());

  setCentralWidget(centralWidget);
  setGeometry(windowSize);

  const int rightPanelWidth = 200;
  splitter->setSizes({width() - rightPanelWidth, rightPanelWidth});
}

QWidget *MainWindow::createRightPanel() {
  QWidget *rightPanel = new QWidget();
  QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);

  NodePalette *nodePalette = new NodePalette(&controller, &dragBuffer);
  CalculationWidget *calcWidget =
      new CalculationWidget(&controller, rightPanel);
  LatexDisplayWidget *latex_widget = new LatexDisplayWidget(&controller);

  rightLayout->addWidget(calcWidget);
  rightLayout->addWidget(latex_widget);
  rightLayout->addStretch();
  rightLayout->addWidget(nodePalette);

  return rightPanel;
}
