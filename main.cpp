#include <iostream>
#include "types.h"
#include "book.h"

int main() {
  auto book = Orderbook();

  Order buy1(Side::Buy, 250.f, 100, OrderType::Limit);
  book.place_order(std::move(buy1));
  Order buy2(Side::Buy, 255.f, 100, OrderType::Limit);
  book.place_order(std::move(buy2));

  Order sell_order(Side::Sell, 255.f, 100, OrderType::Limit);
  book.place_order(std::move(sell_order));

  std::cout << book.get_bid() << std::endl;
}
