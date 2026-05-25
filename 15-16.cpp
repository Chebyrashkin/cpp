#include <iostream>
#include <vector>
#include <string>
#include <utility>

std::string to_roman(int num) {
    const std::vector<std::pair<int, std::string>> roman = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };
    std::string result;
    for (const auto& [value, symbol] : roman) {
        while (num >= value) {
            result += symbol;
            num -= value;
        }
    }
    return result;
}

int main() {
    int number;
    std::cin >> number;
    if (number < 1 || number > 3999) {
        std::cerr << "Число вне диапазона (1-3999)\n";
        return 1;
    }
    std::cout << "Римская запись: " << to_roman(number) << std::endl;
    return 0;
}
