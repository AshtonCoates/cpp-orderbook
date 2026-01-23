#pragma once

#include <list>
#include <unordered_map>
#include <vector>
#include "types.h"

using OrderIter = std::list<Order>::iterator;

struct LevelInfo {
  LevelInfo(Price price_);
  OrderIter add_order(Order order);
  Price price;
  Quantity total_quantity;
  std::list<Order> orders;

  void match_order(Order& order); 
};

// stored in Orderbook.order_map
// gives us enough info to search for our orders list in the heap
struct OrderHandle {
  std::list<Order>::iterator iter;
  Price price;
  Side side;
};

struct BookComp {
  Side side;
  BookComp(Side side_)
    : side(side_) {}
  bool operator()(const LevelInfo& a, const LevelInfo& b) const;
};

class Orderbook {
  std::vector<LevelInfo> bids;
  std::vector<LevelInfo> asks;
  std::unordered_map<Id, OrderHandle> order_map;
  
  BookComp bid_comp; // comparators to be used
  BookComp ask_comp; // for heap operations

  void place_limit_order(Order order);
  void place_market_order(Order order);
  LevelInfo& find_level(Side side, Price price);

public:
  Orderbook() // constructor
    :bid_comp(Side::Buy), ask_comp(Side::Sell) {};
  Price get_bid();
  Quantity get_bid_quantity();
  Price get_ask();
  Quantity get_ask_quantity();
  void cancel_order(Id id);
  void place_order(Order order);
};
