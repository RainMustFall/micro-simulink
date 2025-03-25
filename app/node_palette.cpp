#include "node_palette.h"

#include <QDataStream>
#include <QIODevice>
#include <QMimeData>
#include <QtGui/QDrag>
#include <QtWidgets/QListWidgetItem>

#include "node_palette.h"

NodePalette::NodePalette(QWidget *parent) : QListWidget(parent) {
  setDragEnabled(true);
  addItem(new QListWidgetItem("New Node"));
  addItem(new QListWidgetItem("New Node"));
}

void NodePalette::startDrag(Qt::DropActions supportedActions) {
  QListWidgetItem *item = currentItem();
  if (item) {
    QMimeData *mimeData = new QMimeData;
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    QString label = item->text();
    dataStream << label;

    mimeData->setData("application/x-node", itemData);
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->exec(supportedActions, Qt::MoveAction);
  }
}
