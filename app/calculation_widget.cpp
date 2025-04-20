#include "calculation_widget.h"

#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrentRun>
#include <QtTranslation>

CalculationWidget::CalculationWidget(GraphController *controller,
                                     QWidget *parent)
    : QWidget(parent), m_controller(controller) {
  m_button = new QPushButton(qtTrId("button-calculate"));
  m_label = new QLabel(qtTrId("press-button-to-calculate"));
  m_label->setWordWrap(true);

  m_resultLineEdit = new QLineEdit();
  m_resultLineEdit->setReadOnly(true);

  m_layout = new QVBoxLayout(this);
  m_layout->addWidget(m_label);
  m_layout->addWidget(m_button);
  m_layout->addWidget(m_resultLineEdit);

  setLayout(m_layout);

  m_futureWatcher = new QFutureWatcher<double>(this);
  connect(m_button, &QPushButton::clicked, this,
          &CalculationWidget::startCalculation);
  connect(m_futureWatcher, &QFutureWatcher<double>::finished, this,
          &CalculationWidget::calculationFinished);
  connect(m_futureWatcher, &QFutureWatcher<double>::resultReadyAt, this,
          &CalculationWidget::handleResult);
}

void CalculationWidget::startCalculation() {
  if (!m_controller) {
    m_resultLineEdit->setText(tr("err-controller-not-set"));
    return;
  }

  m_resultLineEdit->clear();

  m_progressDialog = new QProgressDialog(qtTrId("calculating"),
                                         qtTrId("button-cancel"), 0, 0, this);
  m_progressDialog->setWindowModality(Qt::WindowModal);
  connect(m_progressDialog, &QProgressDialog::canceled, m_futureWatcher,
          &QFutureWatcher<double>::cancel);
  m_progressDialog->show();

  // Launch the calculation in a separate thread and get the QFuture
  QFuture<double> future =
      QtConcurrent::run([this]() { return m_controller->GetGraphResult(); });

  // Set the future for the watcher
  m_futureWatcher->setFuture(future);
}

void CalculationWidget::calculationFinished() {
  if (m_progressDialog) {
    m_progressDialog->close();
    delete m_progressDialog;
    m_progressDialog = nullptr;
  }
}

void CalculationWidget::handleResult(int resultIndex) {
  m_resultLineEdit->setText(
      QString::number(m_futureWatcher->resultAt(resultIndex)));
}
