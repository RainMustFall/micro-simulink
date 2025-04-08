#include "node_palette.h"

#include <QDataStream>
#include <QIODevice>
#include <QMimeData>
#include <QtGui/QDrag>
#include <QtWidgets/QListWidgetItem>

#include "integral_visual_node.h"
#include "number_visual_node.h"
#include "x_visual_node.h"
#include "binary_operator.h"

NodePalette::NodePalette(GraphController *controller,
                         NodeDragBuffer *dragBuffer, QWidget *parent)
    : QListWidget(parent), m_dragBuffer(dragBuffer), m_controller(controller) {
  setDragEnabled(true);
  addItem(new NodePaletteItem<NumberVisualNode>("Number"));
  addItem(new NodePaletteItem<XVisualNode>("X"));
  addItem(new NodePaletteItem<PlusVisualNode>("Plus"));
  addItem(new NodePaletteItem<IntegralVisualNode>("Integral"));
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
