#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

class Stock {
public:
    std::string symbol;
    double price;
    int quantity;

    Stock(std::string symbol, double price, int quantity = 0)
        : symbol(symbol), price(price), quantity(quantity) {}
};

class TreeNode {
public:
    Stock data;
    TreeNode *left, *right;

    TreeNode(Stock stock) : data(stock), left(nullptr), right(nullptr) {}
};

class StockTradingApp {
private:
    TreeNode *root;

    TreeNode *insert(TreeNode *node, Stock stock) {
        if (node == nullptr) {
            return new TreeNode(stock);
        }

        if (stock.symbol < node->data.symbol) {
            node->left = insert(node->left, stock);
        } else if (stock.symbol > node->data.symbol) {
            node->right = insert(node->right, stock);
        }

        return node;
    }

    TreeNode *search(TreeNode *node, std::string symbol) {
        if (node == nullptr || node->data.symbol == symbol) {
            return node;
        }

        if (symbol < node->data.symbol) {
            return search(node->left, symbol);
        } else {
            return search(node->right, symbol);
        }
    }

    void inorderTraversal(TreeNode *node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            std::cout << std::setw(8) << node->data.symbol
                      << std::setw(10) << "$" << node->data.price
                      << std::setw(10) << node->data.quantity << "\n";
            inorderTraversal(node->right);
        }
    }

public:
    StockTradingApp() : root(nullptr) {}

    void addStock(Stock stock) {
        root = insert(root, stock);
    }

    Stock buyStock(std::string symbol, int quantity) {
        TreeNode *resultNode = search(root, symbol);

        if (resultNode != nullptr) {
            resultNode->data.quantity += quantity;
            return resultNode->data;
        } else {
            // Return a default Stock if not found
            return Stock("", 0.0);
        }
    }

    Stock sellStock(std::string symbol, int quantity) {
        TreeNode *resultNode = search(root, symbol);

        if (resultNode != nullptr) {
            int remainingQuantity = resultNode->data.quantity - quantity;

            if (remainingQuantity >= 0) {
                resultNode->data.quantity = remainingQuantity;
                return resultNode->data;
            } else {
                std::cout << "Insufficient quantity to sell.\n";
                return Stock("", 0.0);
            }
        } else {
            // Return a default Stock if not found
            return Stock("", 0.0);
        }
    }

    void displayPortfolio() {
        std::cout << std::setw(8) << "Symbol"
                  << std::setw(10) << "Price"
                  << std::setw(10) << "Quantity\n";
        std::cout << "--------------------------\n";
        inorderTraversal(root);
    }
};

void displayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Display Portfolio\n";
    std::cout << "2. Buy Stock\n";
    std::cout << "3. Sell Stock\n";
    std::cout << "4. Exit\n";
}

int main() {
    StockTradingApp tradingApp;

    // Adding stocks to the app
    tradingApp.addStock(Stock("AAPL", 150.0));
    tradingApp.addStock(Stock("GOOGL", 2500.0));
    tradingApp.addStock(Stock("MSFT", 300.0));

    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                tradingApp.displayPortfolio();
                break;
            case 2: {
                std::string symbol;
                int quantity;
                std::cout << "Enter stock symbol: ";
                std::cin >> symbol;
                std::cout << "Enter quantity: ";
                std::cin >> quantity;

                Stock boughtStock = tradingApp.buyStock(symbol, quantity);

                if (boughtStock.symbol.empty()) {
                    std::cout << "Stock not found.\n";
                } else {
                    std::cout << "Bought: " << boughtStock.symbol
                              << " - Price: $" << boughtStock.price
                              << " - Quantity: " << quantity << "\n";
                }
                break;
            }
            case 3: {
                std::string symbol;
                int quantity;
                std::cout << "Enter stock symbol: ";
                std::cin >> symbol;
                std::cout << "Enter quantity: ";
                std::cin >> quantity;

                Stock soldStock = tradingApp.sellStock(symbol, quantity);

                if (soldStock.symbol.empty()) {
                    std::cout << "Stock not found.\n";
                } else {
                    std::cout << "Sold: " << soldStock.symbol
                              << " - Price: $" << soldStock.price
                              << " - Quantity: " << quantity << "\n";
                }
                break;
            }
            case 4:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }

    } while (choice != 4);

    return 0;
}