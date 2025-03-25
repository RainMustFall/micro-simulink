#ifndef NODE_PALETTE_H
#define NODE_PALETTE_H

#include <QtWidgets/QListWidget>

class NodePalette : public QListWidget {
 public:
  NodePalette(QWidget* parent = nullptr);

 protected:
  void startDrag(Qt::DropActions supportedActions) override;
};

#endif  // NODE_PALETTE_H
