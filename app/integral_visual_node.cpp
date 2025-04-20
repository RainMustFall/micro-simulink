#include "integral_visual_node.h"

IntegralVisualNode::IntegralVisualNode(GraphController *controller,
                                       QGraphicsItem *parent)
    : VisualNode(/* numberOfInputs=*/1, /* numberOfOutputs=*/1,
                 controller->AddIntegralNode(0, 1),
                 QRect(0, 0, kHeight, kHeight), parent),
      upperLimit(1),
      lowerLimit(0),
      m_controller(controller) {}

void IntegralVisualNode::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *option,
                               QWidget *widget) {
  VisualNode::paint(painter, option, widget);
  int integralSize = kHeight / 2;
  QFont font("Times", integralSize, QFont::Cursive);
  painter->setFont(font);

  painter->drawText(rect().center().x() - 0.7 * integralSize,
                    rect().center().y() + integralSize / 2,
                    "∫");  // Integral sign
}

void IntegralVisualNode::mouseDoubleClickEvent(
    QGraphicsSceneMouseEvent *event) {
  QDialog dialog;
  dialog.setWindowTitle("Edit Limits");
  QFormLayout form(&dialog);

  QLineEdit upperEdit;
  upperEdit.setText(QString::number(upperLimit));
  form.addRow("Upper Limit:", &upperEdit);

  QLineEdit lowerEdit;
  lowerEdit.setText(QString::number(lowerLimit));
  form.addRow("Lower Limit:", &lowerEdit);

  QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
  form.addRow(&buttonBox);

  QObject::connect(&buttonBox, &QDialogButtonBox::accepted, &dialog,
                   &QDialog::accept);
  QObject::connect(&buttonBox, &QDialogButtonBox::rejected, &dialog,
                   &QDialog::reject);

  if (dialog.exec() == QDialog::Accepted) {
    bool okUpper, okLower;
    double newUpper = upperEdit.text().replace(',', '.').toDouble(&okUpper);
    double newLower = lowerEdit.text().replace(',', '.').toDouble(&okLower);
    if (okUpper && okLower && newLower < newUpper) {
      upperLimit = newUpper;
      lowerLimit = newLower;
      m_controller->SetIntegralLimits(getId(), lowerLimit, upperLimit);
      update();
    }
  }
}
