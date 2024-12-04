#include "brackets+stack.hpp"


int main() {
    
    std::string s;

    std::cout << "Введите строку: ";
    std::cin >> s;

    if (brackets(s) == string_cond::invalid) std::cout << "Строка не существует\n";
    else std::cout << 'Строка существует\n';

}