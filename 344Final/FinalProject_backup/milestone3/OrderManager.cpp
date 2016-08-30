
#include "Item.h"
#include "CustomerOrder.h"
#include "ItemManager.h"
#include "OrderManager.h"
#include <algorithm>

void OrderManager::push_back(CustomerOrder&& customerOrder) {
    customerOrders.push_back(std::move(customerOrder));
}

std::vector<CustomerOrder>::iterator OrderManager::begin() {
    return customerOrders.begin();
}

std::vector<CustomerOrder>::iterator OrderManager::end() {
    return customerOrders.end();
}

const std::vector<CustomerOrder>::const_iterator OrderManager::cbegin() const {
    return customerOrders.cbegin();
}

const std::vector<CustomerOrder>::const_iterator OrderManager::cend() const {
    return customerOrders.cend();
}

void OrderManager::display(std::ostream& os) const {
    for (auto& s : customerOrders)
        s.display(os);
}

void validate(const OrderManager& orderManager, const ItemManager& itemManager, std::ostream& os) {

    for (auto it = orderManager.cbegin(); it != orderManager.cend(); it++) {

        const auto& customerOrder = *it;
        for (int i = 0; i < customerOrder.noOrders(); i++) {

            auto available = [&] (const Item& item) {
                return !item.getName().compare(customerOrder[i]);
            };

            if (std::find_if (itemManager.cbegin(), itemManager.cend(), available) == itemManager.cend())
                os << customerOrder[i] << " is unavailable\n";
        }
    }
}
