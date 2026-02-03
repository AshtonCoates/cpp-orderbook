#pragma once

using Price = float;
using Quantity = unsigned int;
using Id = unsigned int;

enum class Side {Buy, Sell};

enum class OrderType {Market, Limit};

struct Order {
  Side side;
  Price price;
  Quantity quantity;
  OrderType type;
  Id id;
  Order(Side side_, Price price_, Quantity quantity_); // limit order constructor
  Order(Side side_, Quantity quantity_); // market order constructor
  Order(Side side_, Price price_, Quantity quantity_, OrderType type_, Id id_):
    side(side_), price(price_), quantity(quantity_), type(type_), id(id_) {}
};
