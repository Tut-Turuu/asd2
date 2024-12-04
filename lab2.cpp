#include <iostream>
#include <string>
#include "brackets+stack.hpp"


bool str_is_num(const char* s, int size) {
    for (int i = 0; i < size; ++i)
        if (s[i] < '0' || s[i] > '9' ) return false;
    return true;
}


double str_to_num(const char* s, int size) {
    double res = 0;
    double rank = 1;
    for (int i = size - 1; i >= 0; --i) {
        res += (s[i] - '0')* rank;
        rank *= 10;
    }
    return res;
}

int find(const char* s, int size, char req) {
    for (int i = 0; i < size; ++i) {
        if (s[i] == req) return i;
    }
    return size;
}

bool common_brackets(const char* s, int size) {
    if (s[0] != '(' || s[size-1] != ')') return false;
    int c = 0;
    for (int i = 0; i < size - 1; ++i) {
        if (s[i] == ')') --c;
        else if (s[i] == '(') ++c;

        if (c == 0) return false;
    }
    return true;
}

void print(const char* s, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << s[i];
    }
    std::cout << '\n';
}

// 012345
// 1 + 7
// (1 + 3)* 7 + 9 + (8 / (1+ 28)) - 78 * (1 * 9) * 78
double evaluate(const char* s, int size) {

    while (common_brackets(s, size)) {
        s += 1;
        size -= 2;
    }
    // print(s, size);

    if (str_is_num(s, size)) return str_to_num(s, size);

    my::stack<char> brackets;
    int left_ind;
    int right_ind;
    for (int i = 0; i < size; ++i) {
        if (brackets.size() == 0 && (s[i] == '+' || s[i] == '-')) {
            left_ind = i;
            right_ind = i;
            while (s[left_ind] == ' ' || s[left_ind] == '+' || s[left_ind] == '-') --left_ind;
            while (s[right_ind] == ' ' || s[right_ind] == '+' || s[right_ind] == '-') ++right_ind;
            if (s[i] == '+')
                //012345
                //7 + 9
                return evaluate(s, left_ind + 1) + evaluate(s + right_ind, size - right_ind); 
            if (s[i] == '-') 
                return evaluate(s, left_ind + 1) - evaluate(s + right_ind, size - right_ind);
        }

        if (s[i] == '(') {
            brackets.push_back('(');
        } else if (s[i] == ')') {
            brackets.pop_back();
        }
    } // |(1 + 3)* 7| + 9 + |(8 / (1+ 28))| - |78 * (1 * 9) * 78|


    for (int i = 0; i < size; ++i) {
        if (brackets.size() == 0 && (s[i] == '*' || s[i] == '/')) {
            left_ind = i;
            right_ind = i;
            while (s[left_ind] == ' ' || s[left_ind] == '*' || s[left_ind] == '/') --left_ind;
            while (s[right_ind] == ' ' || s[right_ind] == '*' || s[right_ind] == '/') ++right_ind;
            if (s[i] == '*')
                return evaluate(s, left_ind + 1) * evaluate(s + right_ind, size - right_ind);
            if (s[i] == '/') {
                double left = evaluate(s + right_ind, size - right_ind);
                if (left == 0) {
                    throw 1;
                }
                return evaluate(s, left_ind + 1) / left;
            }
                
        }

        if (s[i] == '(') {
            brackets.push_back('(');
        } else if (s[i] == ')') {
            brackets.pop_back();
        }
    }
    

    std::cout << "Something extremly bad happend\n";
    return -100;

}


int main() {
    
    char arr[100];

    std::cout << "Введите выражение: ";
    std::cin.getline(arr, 100);
    
    std::string s(arr);
    
    if (!s_is_valid(s)) {
        std::cout << "Строка невалидна\n";
        return -1;
    }
    if (s[s.size() - 1] != '=') {
        std::cout << "Вы забыли '='\n";
        return -1;
    }

    try {
        std::cout << evaluate(s.c_str(), s.size()-1) << '\n';
    } catch (...) {
        std::cout << "Деление на ноль\n";
    }


    

}