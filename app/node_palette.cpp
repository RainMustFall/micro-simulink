#include "node_palette.h"

#include <QDataStream>
#include <QIODevice>
#include <QMimeData>
#include <QtGui/QDrag>
#include <QtWidgets/QListWidgetItem>

#include "binary_operator.h"
#include "integral_visual_node.h"
#include "number_visual_node.h"
#include "trigonometry_visual_nodes.h"
#include "x_visual_node.h"

NodePalette::NodePalette(GraphController *controller,
                         NodeDragBuffer *dragBuffer, QWidget *parent)
    : QListWidget(parent), m_dragBuffer(dragBuffer), m_controller(controller) {
  setDragEnabled(true);
  addItem(new NodePaletteItem<NumberVisualNode>(qtTrId("number-option")));
  addItem(new NodePaletteItem<XVisualNode>(qtTrId("x-option")));
  addItem(new NodePaletteItem<PlusVisualNode>(qtTrId("plus-option")));
  addItem(new NodePaletteItem<MinusVisualNode>(qtTrId("minus-option")));
  addItem(new NodePaletteItem<DividesVisualNode>(qtTrId("divides-option")));
  addItem(
      new NodePaletteItem<MultipliesVisualNode>(qtTrId("multiplies-option")));
  addItem(new NodePaletteItem<PowerVisualNode>(qtTrId("power-option")));
  addItem(new NodePaletteItem<IntegralVisualNode>(qtTrId("integral-option")));
  addItem(new NodePaletteItem<SineVisualNode>(qtTrId("sin-option")));
  addItem(new NodePaletteItem<CosineVisualNode>(qtTrId("cos-option")));
  addItem(new NodePaletteItem<TangentVisualNode>(qtTrId("tan-option")));
  addItem(new NodePaletteItem<CotangentVisualNode>(qtTrId("cot-option")));
}

void NodePalette::startDrag(Qt::DropActions supportedActions) {
  auto item = dynamic_cast<AbstractNodePaletteItem *>(currentItem());
  if (item != nullptr) {
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-node", "new-node");
    m_dragBuffer->setNode(item->createVisualNode(m_controller));

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->exec(supportedActions, Qt::MoveAction);
  }
}

NodePalette::AbstractNodePaletteItem::AbstractNodePaletteItem(
    const QString &text)
    : QListWidgetItem(text) {}
