#include "bin_tree.hpp"
#include "brackets+stack.hpp"



void direct_traversal(const Node* head) {
    my::stack<const Node*> prev;
    prev.push_back(head);

}

int main() {
    const char* s = "1(2, 8(7(88,9),3))";

    char * ns = without_spaces(s);
    Node* head = create_bin_tree(ns, strlen(ns));
    // std::cout << get_first_num(ns);
    represent_bin_tree(head);

    destroy_bin_tree(head);
    delete[] ns;
}