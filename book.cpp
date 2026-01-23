#include <algorithm>
#include <utility> // for std::move
#include <limits>
#include "types.h"
#include "book.h"



LevelInfo::LevelInfo(Price price_)
  :price(price_), total_quantity(0) {}

OrderIter LevelInfo::add_order(Order order) {
  auto iter = orders.emplace(orders.end(), order);
  total_quantity += order.quantity;
  return iter;
}

void LevelInfo::match_order(Order& order) {
  Quantity& remaining = order.quantity;
  while (!orders.empty() && remaining > 0) {
    Order& other_order = orders.front();
    Quantity& other_quantity = other_order.quantity;
    assert(other_quantity > 0);
    if (remaining >= other_quantity) {
      remaining -= other_quantity;
      orders.pop_front();
    } else {
      other_quantity -= remaining;
      remaining = 0;
    }
  }
}


Price Orderbook::get_bid() {
  auto& top_level = bids.front();
  return top_level.price;
}

Price Orderbook::get_ask() {
  auto& top_level = asks.front();
  return top_level.price;
}

Quantity Orderbook::get_ask_quantity() {
  auto& top_level = asks.front();
  return top_level.total_quantity;
}

Quantity Orderbook::get_bid_quantity() {
  auto& top_level = bids.front();
  return top_level.total_quantity;
}

void Orderbook::place_limit_order(Order order) {
  auto& book = (order.side == Side::Buy) ? bids : asks;
  auto& opp_book = (order.side == Side::Sell) ? bids : asks;

  // first match our order with other side
  while (!opp_book.empty() && order.quantity > 0) {
    if (
      (order.side == Side::Buy && opp_book[0].price < order.price) ||
      (order.side == Side::Sell && opp_book[0].price > order.price)
    ) {
      break; // no matches to be made
    }

    assert(false && "match making logic not implemented yet");

  }
}

void Orderbook::place_market_order(Order order) {
  Price price = std::numeric_limits<float>::infinity();
  if (order.side == Side::Sell) { price *= -1; }
  place_limit_order(Order{order.side, 
                          price,
                          order.quantity,
                          OrderType::Limit,
                          order.id
                          }
  );
}

void Orderbook::place_order(Order order) {
  switch (order.type) {
    case OrderType::Limit:
      place_limit_order(std::move(order));
    case OrderType::Market:
      place_market_order(std::move(order));
  }
}

// comparator used for heap operations
bool BookComp::operator()(const LevelInfo& a, const LevelInfo& b) const {
  switch(side) {
    case Side::Buy:
      return a.price > b.price;
    case Side::Sell:
      return a.price < b.price;
  }
  assert(false && "undefined side");
}

LevelInfo& Orderbook::find_level(Side side, Price price) {
  std::vector<LevelInfo>& book = (side == Side::Buy) ? bids : asks;

  for (auto& level : book) {
    if (level.price == price) {
      return level;
    }
  }
  assert(false && "level not found");
}
