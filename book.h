#pragma once

#include <list>
#include <unordered_map>
#include <vector>
#include <iterator>
#include "types.h"

struct LevelInfo {
  LevelInfo(Price price_);
  std::list<Order>::iterator add_order(Order order);
  Price price;
  Quantity total_quantity;
  std::list<Order> orders;
};

// stored in Orderbook.order_map
// gives us enough info to search for our orders list in the heap
struct OrderHandle {
  std::list<Order>::iterator iter;
  Price price;
  Side side;
};

class Orderbook {
  std::vector<LevelInfo> bids;
  std::vector<LevelInfo> asks;
  std::unordered_map<Id, OrderHandle> order_map;

  void fill_market_order(Order& order);
  void place_limit_order(Order&& order);

public:
  Orderbook();
  Price get_bid();
  Quantity get_bid_quantity();
  Price get_ask();
  Quantity get_ask_quantity();
  void cancel_order(Id id);
  void place_order(Order order);
};
