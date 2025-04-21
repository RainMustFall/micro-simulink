#ifndef GRAPH_UPDATE_SUBSCRIPTION_H
#define GRAPH_UPDATE_SUBSCRIPTION_H

#include <vector>

/*!
 * @brief Interface which allows to be notified when the graph is updated
 */
class GraphUpdateSubscriber {
 public:
  /*!
   * @brief Process graph update event
   */
  virtual void Notify() = 0;
};

/*!
 * @brief Interface which allows to subscribe on graph update events
 *
 * Although Qt provides a powerful mechanism for slots and signals, it was not
 * sufficient for all cases: a graph can be changed by graphical items (for
 * example, double-clicking on a number allows you to change it), which do not
 * have the ability to send signals in the Qt system, as they don't inherit
 * QObject.
 */
class GraphUpdateNotifier {
 public:
  /*!
   * @brief Subscribe for graph updates
   * @param subscriber
   */
  void SubscribeForUpdates(GraphUpdateSubscriber* subscriber);

 protected:
  void NotifySubscribers();

 private:
  std::vector<GraphUpdateSubscriber*> subscribers_;
};

#endif  // GRAPH_UPDATE_SUBSCRIPTION_H
