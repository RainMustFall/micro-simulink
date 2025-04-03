#ifndef GRAPH_UPDATE_SUBSCRIPTION_H
#define GRAPH_UPDATE_SUBSCRIPTION_H

#include <vector>

class GraphUpdateSubscriber {
 public:
  virtual void Notify() = 0;
};

class GraphUpdateNotifier {
 public:
  void SubscribeForUpdates(GraphUpdateSubscriber* subscriber);

 protected:
  void NotifySubscribers();

 private:
  std::vector<GraphUpdateSubscriber*> subscribers_;
};

#endif  // GRAPH_UPDATE_SUBSCRIPTION_H
