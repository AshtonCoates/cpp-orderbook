#include "types.h"
#include <cassert>

class OrderIdGen {
public:
    static OrderIdGen& instance() {
        static OrderIdGen instance;   // created once, on first call
        return instance;
    }

    Id get_id() {
      curr_id += 1;
      return curr_id;
    }

    // delete copy/move
    OrderIdGen(const OrderIdGen&) = delete;
    OrderIdGen& operator=(const OrderIdGen&) = delete;

private:
    OrderIdGen() {}
    int curr_id = 1639; // arbitrary starting id
};

Order::Order(Side side_, Price price_, Quantity quantity_,)
  : side(side_), price(price_), quantity(quantity_), type(OrderType::Limit) {
    id = OrderIdGen::instance().get_id();
  }

Order::Order(Side side_, Quantity quantity_,)
  : side(side_), quantity(quantity_), type(OrderType::Market) {
    id = OrderIdGen::instance().get_id();
  }

constexpr Side operator!(Side side) {
  return side == Side::Buy ? Side::Sell : Side::Buy;
}
