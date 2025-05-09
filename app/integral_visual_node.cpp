#include "integral_visual_node.h"

#include "integral_node.h"

IntegralVisualNode::IntegralVisualNode(GraphController *controller,
                                       QGraphicsItem *parent)
    : VisualNode(/* numberOfInputs=*/1, /* numberOfOutputs=*/1,
                 controller->AddNode<IntegralNode>(0, 1),
                 QRect(0, 0, kHeight, kHeight), parent),
      upperLimit(1),
      lowerLimit(0),
      m_controller(controller) {}

void IntegralVisualNode::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *option,
                               QWidget *widget) {
  VisualNode::paint(painter, option, widget);
  int integralSize = kHeight / 2;
  QFont font({"Times", "Times New Roman"}, integralSize, QFont::Cursive);
  painter->setFont(font);
  painter->drawText(rect(), Qt::AlignCenter | Qt::AlignHCenter, "∫");
}

void IntegralVisualNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) {
  QDialog dialog;
  dialog.setWindowTitle(qtTrId("update-limits"));
  QFormLayout form(&dialog);

  QLineEdit upperEdit;
  upperEdit.setText(QString::number(upperLimit));
  form.addRow(qtTrId("upper-limit"), &upperEdit);

  QLineEdit lowerEdit;
  lowerEdit.setText(QString::number(lowerLimit));
  form.addRow(qtTrId("lower-limit"), &lowerEdit);

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
