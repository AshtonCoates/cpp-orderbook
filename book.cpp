#include <algorithm>
#include <utility> // for std::move
#include "types.h"
#include "book.h"

LevelInfo::LevelInfo(Price price_)
  :price(price_){}

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

void Orderbook::place_order(Order order) {
  switch (order.type) {
    case OrderType::Limit:
      place_limit_order(order);
    case OrderType::Market:
      place_limit_order(order);
  }
}

void Orderbook::fill_market_order(Order& order)
