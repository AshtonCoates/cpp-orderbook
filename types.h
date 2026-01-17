#pragma once

using Price = float;
using Quantity = unsigned int;
using ID = unsigned int;

enum class Side {Buy, Sell};

struct Order {
  Side side;
  Price price;
  Quantity quantity;
  ID id;
};
