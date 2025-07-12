#include <iostream>
#include <vector>
#include <iomanip>  // for std::fixed and std::setprecision

class CashRegister {
private:
    std::vector<double> prices;

public:
    // Clear the current sale
    void clear() {
        prices.clear();
    }

    // Add an item price to the sale
    void add_item(double price) {
        prices.push_back(price);
    }

    // Get the total price of all items
    double get_total() const {
        double total = 0.0;
        for (double price : prices) {
            total += price;
        }
        return total;
    }

    // Get the number of items in the sale
    int get_count() const {
        return static_cast<int>(prices.size());
    }

    // Display all item prices
    void display_all() const {
        std::cout << "Items in the current sale:\n";
        if (prices.empty()) {
            std::cout << "  (No items)\n";
            return;
        }
        for (size_t i = 0; i < prices.size(); ++i) {
            std::cout << "  Item " << i + 1 << ": $" << std::fixed << std::setprecision(2) << prices[i] << "\n";
        }
    }
};

// Example usage
int main() {
    CashRegister register1;

    register1.add_item(2.99);
    register1.add_item(5.49);
    register1.add_item(1.50);

    register1.display_all();

    std::cout << "Total items: " << register1.get_count() << "\n";
    std::cout << "Total price: $" << std::fixed << std::setprecision(2) << register1.get_total() << "\n";

    register1.clear();
    std::cout << "\nAfter clearing:\n";
    register1.display_all();

    return 0;
}
