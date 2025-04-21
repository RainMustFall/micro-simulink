#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include "graph_controller.h"
#include "node_drag_buffer.h"

/*!
 * @brief The Main window which contains all other widgets
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /*!
   * @brief MainWindow constructor
   * @param windowSize size of the window
   * @param parent - parent widget
   */
  MainWindow(const QRect &windowSize, QWidget *parent = nullptr);

 private:
  GraphController controller;
  NodeDragBuffer dragBuffer;

  QWidget *createRightPanel();
};

#endif  // MAINWINDOW_H
