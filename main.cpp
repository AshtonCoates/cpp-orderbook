#include <iostream>
#include <vector>
#include "types.h"
#include "book.h"

int main() {
  Order order(Side::Buy, 250.f, 100, OrderType::Limit);
  std::cout << "order created with id " << order.id << std::endl;
  auto id = order.id;

  auto book = Orderbook();
  std::cout << "orderbook created" << std::endl;

  book.place_order(std::move(order));
  book.cancel_order(id);
  
  std::cout << "order cancelled" << std::endl;
}
