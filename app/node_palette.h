#ifndef NODE_PALETTE_H
#define NODE_PALETTE_H

#include <QtWidgets/QListWidget>

#include "graph_controller.h"
#include "node_drag_buffer.h"
#include "visual_node.h"

/*!
 * @brief Qt widget allowing to select nodes and drag them onto the graph editor
 */
class NodePalette : public QListWidget {
 public:
  /*!
   * @brief NodePalette
   * @param controller - GraphController maintaining the graph model
   * @param dragBuffer - buffer providing node objects which have been dragged
   * from palette
   * @param parent - parent widget
   */
  NodePalette(GraphController* controller, NodeDragBuffer* dragBuffer,
              QWidget* parent = nullptr);

 protected:
  void startDrag(Qt::DropActions supportedActions) override;

 private:
  NodeDragBuffer* m_dragBuffer;
  GraphController* m_controller;

  class AbstractNodePaletteItem : public QListWidgetItem {
   public:
    AbstractNodePaletteItem(const QString& text);
    virtual std::unique_ptr<VisualNode> createVisualNode(
        GraphController* controller) = 0;
  };

  template <typename NodeType>
  class NodePaletteItem : public AbstractNodePaletteItem {
   public:
    NodePaletteItem(const QString& text) : AbstractNodePaletteItem(text) {}

    std::unique_ptr<VisualNode> createVisualNode(
        GraphController* controller) override {
      return std::unique_ptr<VisualNode>(new NodeType(controller));
    }
  };
};

#endif  // NODE_PALETTE_H
