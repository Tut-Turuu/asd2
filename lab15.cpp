#include "bin_tree.hpp"


void rec_direct_traversal(const Node* head) {
    std::cout << head->data << '\n';
    if (head->left != nullptr) rec_direct_traversal(head->left);
    if (head->right != nullptr) rec_direct_traversal(head->right);
}

void rec_central_traversal(const Node* head) {
    if (head->left != nullptr) rec_central_traversal(head->left);
    std::cout << head->data << '\n';
    if (head->right != nullptr) rec_central_traversal(head->right);
}

void rec_end_traversal(const Node* head) {
    if (head->left != nullptr) rec_end_traversal(head->left);
    if (head->right != nullptr) rec_end_traversal(head->right);
    std::cout << head->data << '\n';
}

int main() {
    const char* s = "1(2, 8(7(88,9),3))";

    char * ns = without_spaces(s);
    Node* head = create_bin_tree(ns, strlen(ns));
    // std::cout << get_first_num(ns);

    rec_end_traversal(head);
    destroy_bin_tree(head);
    delete[] ns;
}