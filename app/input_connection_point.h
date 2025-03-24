#ifndef INPUT_CONNECTION_POINT_H
#define INPUT_CONNECTION_POINT_H

#include "connection_point.h"

class InputConnectionPoint : public ConnectionPoint {
public:
    InputConnectionPoint(size_t index, size_t totalPoints, QGraphicsRectItem *parent = nullptr);

    void updateHovered(const QPointF &scenePos,
                       bool mousePressed,
                       bool currentlyConnecting) override;

    bool acceptsDrop(const QPointF& scenePos) override;

    bool acceptsOutputPress(const QPointF&) override;

    bool acceptsInputPress(const QPointF& scenePos) override;
};

#endif // INPUT_CONNECTION_POINT_H
