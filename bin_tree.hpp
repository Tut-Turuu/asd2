#include <cstring>
#include <iostream>



struct Node {
    int data;
    Node* left;
    Node* right;
};

char* without_spaces(const char* s) {
    size_t old_sz = strlen(s);
    char* ns = new char[old_sz + 1];
    size_t j = 0;
    for (size_t i = 0; i < old_sz; ++i) {
        if (s[i] != ' ') {
            ns[j] = s[i];
            ++j;
        }
    }
    ns[j] = '\0';
    return ns;
}

int get_first_num(const char* s) {


    size_t i = 0;
    bool neg = false;
    if (s[0] == '-') {
        ++i;
        neg = true;
    }
    while (s[i] >= '0' && s[i] <= '9') {
        ++i;
    }
    --i;

    size_t start = neg ? 1 : 0;
    int res = 0;
    int charge = 1;
    for (; i + 1 >= start + 1; --i) {

        res += (s[i] - '0')* charge;
        charge *= 10;
    }
    res = neg ? -res : res;
    return res;
}

bool is_num(const char* s, size_t sz) {
    for (size_t i = 0; i < sz; ++i) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

void print(const char* s, size_t sz) {
    for (size_t i = 0; i < sz; ++i) {
        std::cout << s[i];
    }
    std::cout << '\n';
}

Node* create_bin_tree(const char* s, size_t sz) {
    // print(s, sz);
    // std::cout << "sz: " << sz <<'\n';
    if (!sz) return nullptr;
    Node* head = new Node;
    if (is_num(s, sz)) {
        head->data = get_first_num(s);
        head->left = nullptr;
        head->right = nullptr;
        return head;
    }
    head->data = get_first_num(s);
    size_t first_br = 0;
    size_t curr_comma;

    while (s[first_br] != '(') ++first_br;
    curr_comma = first_br;
    size_t br_level = 0;
    while (s[curr_comma] != ',' || br_level != 1)  {
        if (s[curr_comma] == '(') ++br_level;
        else if (s[curr_comma] == ')') --br_level;
        ++curr_comma;
    }
    // std::cout << "x: " << first_br << ' ' << curr_comma << '\n';
    // std::cout << first_br << ' ' << curr_comma;
    // std::cout << "comma: " << curr_comma << " br: " << first_br << '\n';
    head->left = create_bin_tree(s + first_br + 1, curr_comma - first_br - 1);
    head->right = create_bin_tree(s + curr_comma + 1, sz - curr_comma - 2);
    return head;
}

void destroy_bin_tree(const Node* head) {
    if (head->left != nullptr) destroy_bin_tree(head->left);
    if (head->right != nullptr) destroy_bin_tree(head->right);
    delete head;
}

void represent_bin_tree(const Node* head) {
    if (!head->left && !head->right) {
        std::cout << head->data;
        return;
    }
    std::cout << head->data << '(';
    if (head->left) represent_bin_tree(head->left);
    std::cout << ',';
    if (head->right) represent_bin_tree(head->right);
    std::cout << ')';
}