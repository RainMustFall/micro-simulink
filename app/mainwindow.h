#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include "graph_controller.h"
#include "node_drag_buffer.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(const QRect &windowSize, QWidget *parent = nullptr);

 private:
  GraphController controller;
  NodeDragBuffer dragBuffer;

  QWidget *createRightPanel();
};

#endif  // MAINWINDOW_H
