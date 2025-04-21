#include "calculation_widget.h"

#include <QApplication>
#include <QColor>
#include <QFuture>
#include <QFutureWatcher>
#include <QPalette>
#include <QString>
#include <QtConcurrentRun>
#include <QtTranslation>
#include <variant>

CalculationWidget::CalculationWidget(GraphController *controller,
                                     QWidget *parent)
    : QWidget(parent), m_controller(controller) {
  m_button = new QPushButton(qtTrId("button-calculate"));
  m_label = new QLabel(qtTrId("press-button-to-calculate"));
  m_label->setWordWrap(true);

  m_resultLineEdit = new QLineEdit();
  m_resultLineEdit->setReadOnly(true);

  m_errorLabel = setUpErrorLabel();

  m_layout = new QVBoxLayout(this);
  m_layout->addWidget(m_label);
  m_layout->addWidget(m_button);
  m_layout->addWidget(m_resultLineEdit);
  m_layout->addWidget(m_errorLabel);

  setLayout(m_layout);

  m_futureWatcher = new QFutureWatcher<ExecutionResult>(this);
  connect(m_button, &QPushButton::clicked, this,
          &CalculationWidget::startCalculation);
  connect(m_futureWatcher, &QFutureWatcher<double>::finished, this,
          &CalculationWidget::calculationFinished);
  connect(m_futureWatcher, &QFutureWatcher<double>::resultReadyAt, this,
          &CalculationWidget::handleResult);
}

void CalculationWidget::showDialog() {
  m_progressDialog = new QProgressDialog(qtTrId("calculating"),
                                         qtTrId("button-cancel"), 0, 0, this);
  m_progressDialog->setWindowModality(Qt::WindowModal);
  connect(m_progressDialog, &QProgressDialog::canceled, m_futureWatcher,
          &QFutureWatcher<ExecutionResult>::cancel);
  m_progressDialog->show();
}

QLabel *CalculationWidget::setUpErrorLabel() {
  auto label = new QLabel();
  QString color = QApplication::palette()
                      .color(QPalette::Active, QPalette::Highlight)
                      .name();
  label->setStyleSheet("QLabel { color : " + color + "; }");
  label->setWordWrap(true);
  return label;
}

void CalculationWidget::startCalculation() {
  if (!m_controller) {
    m_errorLabel->setText(qtTrId("err-controller-not-set"));
    return;
  }

  m_resultLineEdit->clear();
  m_errorLabel->clear();
  showDialog();

  // Set the future for the watcher
  m_futureWatcher->setFuture(
      QtConcurrent::run([this]() { return processGraphExecution(); }));
}

void CalculationWidget::calculationFinished() {
  if (m_progressDialog) {
    m_progressDialog->close();
    delete m_progressDialog;
    m_progressDialog = nullptr;
  }
}

void CalculationWidget::handleResult(int resultIndex) {
  ExecutionResult result = m_futureWatcher->resultAt(resultIndex);
  if (std::holds_alternative<double>(result)) {
    // Execution successful, we have a value
    m_resultLineEdit->setText(QString::number(std::get<double>(result)));
  } else if (std::holds_alternative<QString>(result)) {
    // Execution failed, we got error string
    m_errorLabel->setText(std::get<QString>(result));
  }
}

CalculationWidget::ExecutionResult CalculationWidget::processGraphExecution()
    const {
  try {
    return m_controller->GetGraphResult();
  } catch (GraphIsIncomplete &) {
    return qtTrId("graph-is-incomplete");
  } catch (ResultIsNotScalar &) {
    return qtTrId("result-is-not-scalar");
  }
}
