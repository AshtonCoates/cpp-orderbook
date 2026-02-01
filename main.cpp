#include <iostream>
#include "types.h"
#include "book.h"

int main() {
  Order buy_order(Side::Buy, 250.f, 100, OrderType::Limit);
  std::cout << "order created with id " << buy_order.id << std::endl;
  auto id = buy_order.id;

  auto book = Orderbook();
  std::cout << "orderbook created" << std::endl;

  book.place_order(std::move(buy_order));

  Order sell_order(Side::Sell, 255.f, 100, OrderType::Limit);
  book.place_order(std::move(sell_order));
}
