#include "graph_update_subscription.h"

void GraphUpdateNotifier::SubscribeForUpdates(
    GraphUpdateSubscriber *subscriber) {
  subscribers_.push_back(subscriber);
}

void GraphUpdateNotifier::NotifySubscribers() {
  for (auto subscriber : subscribers_) {
    subscriber->Notify();
  }
}
