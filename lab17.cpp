#include "bin_tree.hpp"


Node* find_element(Node* head, int value) {
    if (head == nullptr) {
        return head;
    }
    if (head->data == value) {
        return head;
    }
    if (head->left != nullptr && value < head->data) {
        return find_element(head->left, value);
    }
    if (head->right != nullptr && value > head->data) {
        return find_element(head->right, value);
    }
    return nullptr;
}

Node* find_place_in_tree(Node* head, int value) {
    if (head == nullptr) {
        return nullptr;
    }
    if (value == head->data) {
        return nullptr;
    }
    if (value < head->data) {
        if(head->left == nullptr){
            return head;
        }
        else {
            return find_place_in_tree(head->left, value);
        }
    }
    if (value > head->data) {
        if (head->right == nullptr) {
            return head;
        }
        else {
            return find_place_in_tree(head->right, value);
        }
    }
}

void put_element_into_tree(Node* head, int element) {
    if (find_element(head, element) != nullptr) {
        std::cout << "This element already in tree\n";
        return;
    }

    Node* parent = find_place_in_tree(head, element);
    if (parent != nullptr) {
        if (element < parent->data) {
            parent->left = new Node;
            parent->left->data = element;
        }
        else {
            parent->right = new Node;
            parent->right->data = element;
        }
    }
}

Node* find_min_in_tree(Node* root) {
    if (root->left == NULL) {
        return root;
    }
    else return find_min_in_tree(root->left);
}

Node* delete_element_from_tree(Node* head, int element) {
    if (head == nullptr) {
        return head;
    }
    if (element < head->data) {
        head->left = delete_element_from_tree(head->left, element);
    }
    else if (element > head->data) {
        head->right = delete_element_from_tree(head->right, element);
    }
    else {
        if (head->left == nullptr) {
            Node* ptr = head->right;
            delete head;
            return ptr;
        }
        else if (head->right == nullptr) {
            Node* ptr = head->left;
            delete head;
            return ptr;
        }
        
        Node* minNode = find_min_in_tree(head->right);
        head->data = minNode->data;
        head->right = delete_element_from_tree(head->right, minNode->data);
        
    }
    return head;
}