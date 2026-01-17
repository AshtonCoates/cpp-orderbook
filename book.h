#pragma once

#include <list>
#include <unordered_map>
#include <vector>
#include "types.h"

struct LevelInfo{
  LevelInfo(Price price_);
  Price price;
  std::list<Order> orders;
};

class Orderbook {
  std::vector<LevelInfo> book;
public:
  Orderbook();
  Price get_bid();
  Price get_ask();
  void cancel_order(ID id);
  void place_order(Order order);
};
