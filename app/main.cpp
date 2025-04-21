#include <QRect>
#include <QTranslator>
#include <cmath>

#include "calculation_widget.h"
#include "graph_widget.h"
#include "latex_display_widget.h"
#include "mainwindow.h"
#include "node_drag_buffer.h"
#include "node_palette.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  QTranslator translator;
  if (!translator.load(":/i18n/app_en_US")) {
    qDebug() << "Could not load translation file";
    return 1;
  }

  if (!QCoreApplication::installTranslator(&translator)) {
    qDebug() << "Could not apply translator";
    return 1;
  }

  MainWindow mainWindow(QRect(100, 100, 1000, 600));
  mainWindow.show();

  return app.exec();
}
