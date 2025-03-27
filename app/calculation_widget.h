#ifndef CALCULATION_WIDGET_H
#define CALCULATION_WIDGET_H

#include <QFuture>
#include <QLabel>
#include <QLineEdit>
#include <QProgressDialog>
#include <QPushButton>
#include <QThread>
#include <QVBoxLayout>
#include <QWidget>
#include <QtConcurrent>

#include "graph_controller.h"

class CalculationWidget : public QWidget {
  Q_OBJECT

 public:
  explicit CalculationWidget(GraphController* controller,
                             QWidget* parent = nullptr);

 private slots:
  void startCalculation();

  void calculationFinished();

  void handleResult(double result);

 private:
  GraphController* m_controller;
  QLabel* m_label;
  QPushButton* m_button;
  QLineEdit* m_resultLineEdit;
  QVBoxLayout* m_layout;
  QProgressDialog* m_progressDialog = nullptr;
  QFutureWatcher<double>* m_futureWatcher;
};

#endif  // CALCULATION_WIDGET_H
