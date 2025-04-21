#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtWidgets/QGraphicsScene>

#include "connection_point.h"

/*!
 * @brief Graphics item representing connection between nodes
 */
class Connection : public QGraphicsItem {
 public:
  /*!
   * @brief Connection contructor
   *
   * It accepts pointers to source and destination connection points, but
   * doesn't own them.
   * @param source - point from which the connection starts
   * @param dest - point at which the connection ends
   * @param parent - parent QGraphicsItem
   */
  Connection(ConnectionPoint *source, ConnectionPoint *dest,
             QGraphicsItem *parent = nullptr);

  /*!
   * @brief Getter for source point
   * @return source point
   */
  ConnectionPoint *sourcePoint();

  /*!
   * @brief Getter for destination point
   * @return destination point
   */
  ConnectionPoint *destPoint();

  /*!
   * @brief Getter for source point
   * @return source point
   */

  const ConnectionPoint *sourcePoint() const;
  /*!
   * @brief Getter for destination point
   * @return destination point
   */
  const ConnectionPoint *destPoint() const;

  ~Connection() override;

  QRectF boundingRect() const override;

 protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
             QWidget *) override;

 private:
  ConnectionPoint *m_sourcePoint;
  ConnectionPoint *m_destPoint;
};

#endif  // CONNECTION_H
