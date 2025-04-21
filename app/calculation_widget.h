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
#include <variant>

#include "graph_controller.h"

/*!
 * @brief Qt widget to query and display calculation result
 */
class CalculationWidget : public QWidget {
  Q_OBJECT

 public:
  /*!
   * @brief Constructor
   * @param controller - GraphController object to query execution results
   * @param parent - parent widget
   */
  explicit CalculationWidget(GraphController* controller,
                             QWidget* parent = nullptr);

 private slots:
  void startCalculation();

  void calculationFinished();

  void handleResult(int resultIndex);

 private:
  GraphController* m_controller;
  QLabel* m_label;
  QLabel* m_errorLabel;
  QPushButton* m_button;
  QLineEdit* m_resultLineEdit;
  QVBoxLayout* m_layout;
  QProgressDialog* m_progressDialog = nullptr;

  typedef std::variant<double, QString> ExecutionResult;
  QFutureWatcher<ExecutionResult>* m_futureWatcher;

  ExecutionResult processGraphExecution() const;
  void showDialog();
  QLabel* setUpErrorLabel();
};

#endif  // CALCULATION_WIDGET_H
