#include <iostream>
#include <vector>
#include "types.h"
#include "book.h"

int main() {
  Order order(Side::Buy, 250.f, 100, OrderType::Limit);
  std::cout << "order created with id " << order.id << std::endl;
}
