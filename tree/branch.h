#pragma once

#include "./exceptions.h"

template<typename INDEX, typename VALUE>
class Branch {
private:
    INDEX index;
    VALUE value;
    Branch *left = nullptr, *right = nullptr;

    Branch *pop_min();

public:
    Branch(const INDEX &search_index, const VALUE &new_value) : index(search_index), value(new_value) {}

    ~Branch() {
        delete left;
        delete right;
    }

    VALUE *get(const INDEX &search_index);

    void set(const INDEX &search_index, const VALUE &new_value);


    void disp_preorder(std::ostream &os = std::cout) const;

    void disp_inorder(std::ostream &os = std::cout) const;

    void disp_postorder(std::ostream &os = std::cout) const;

    friend std::ostream &operator<<(std::ostream &os, const Branch<INDEX, VALUE> &branch) {
        branch.disp_inorder(os);
        return os;
    }

    Branch *findMin(Branch *node);

    VALUE get_value() { return value; }

#ifdef USE_RECURRENCE

    INDEX get_index() { return index; }

    Branch *deleteNode(Branch *root, INDEX key);

#else

    VALUE pop(const INDEX &search_index);

#endif


};

template<typename INDEX, typename VALUE>
VALUE *Branch<INDEX, VALUE>::get(const INDEX &search_index) {
    if (search_index < index && left) return left->get(search_index);
    else if (index < search_index && right) return right->get(search_index);
    else if (index == search_index) return &value;
    else return nullptr;
}

template<typename INDEX, typename VALUE>
void Branch<INDEX, VALUE>::set(const INDEX &search_index, const VALUE &new_value) {
    if (search_index < index) {
        if (left) left->set(search_index, new_value);
        else left = new Branch(search_index, new_value);
    } else if (index < search_index) {
        if (right) right->set(search_index, new_value);
        else right = new Branch(search_index, new_value);
    } else value = new_value;
}

template<typename INDEX, typename VALUE>
Branch<INDEX, VALUE> *Branch<INDEX, VALUE>::pop_min() {
    if (left && left->left) return left->pop_min();
    Branch *temp = left;
    left = left->left;
    return temp;
}

template<typename INDEX, typename VALUE>
void Branch<INDEX, VALUE>::disp_preorder(std::ostream &os) const {
    os << index << std::endl;
    if (left) left->disp_inorder(os);
    if (right) right->disp_inorder(os);
}


template<typename INDEX, typename VALUE>
void Branch<INDEX, VALUE>::disp_inorder(std::ostream &os) const {
    if (left) left->disp_inorder(os);
    os << index << std::endl;
    if (right) right->disp_inorder(os);
}

template<typename INDEX, typename VALUE>
void Branch<INDEX, VALUE>::disp_postorder(std::ostream &os) const {
    if (left) left->disp_inorder(os);
    if (right) right->disp_inorder(os);
    os << index << std::endl;
}

#ifdef USE_RECURRENCE

template<typename INDEX, typename VALUE>
Branch<INDEX, VALUE> *Branch<INDEX, VALUE>::findMin(Branch *node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template<typename INDEX, typename VALUE>
Branch<INDEX, VALUE> *Branch<INDEX, VALUE>::deleteNode(Branch<INDEX, VALUE> *root, INDEX key) {
    if (root == nullptr) {
        return root;
    }

    if (key < root->value) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->value) {
        root->right = deleteNode(root->right, key);
    } else {
        // Węzeł do usunięcia został znaleziony

        // Węzeł z jednym dzieckiem lub bez dzieci
        if (root->left == nullptr) {
            Branch *temp = root->right;
            root->left = nullptr;
            root->right = nullptr;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Branch *temp = root->left;
            root->left = nullptr;
            root->right = nullptr;
            delete root;
            return temp;
        }

        // Węzeł z dwoma dziećmi
        Branch *temp = findMin(root->right);
        root->value = temp->value;
        root->index = temp->index;
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

#else

template<typename INDEX, typename VALUE>
VALUE Branch<INDEX, VALUE>::pop(const INDEX &search_index) {
    Branch *previous = nullptr, *current = this, *min;
    VALUE pop_value;
    bool is_left;
    while (search_index != current->index) {
        if (search_index < current->index && current->left) {
            previous = current;
            current = current->left;
            is_left = true;
        } else if (current->index < search_index && current->right) {
            previous = current;
            current = current->right;
            is_left = false;
        } else throw NotFoundElementException();
    }
    pop_value = current->value;
    if (!previous && !current->left && !current->right) throw PopElementIsRoot();
    else if (!previous && !current->left) *current = *current->right;
    else if (!previous && !current->right) *current = *current->left;
    else if (!previous) {
        if (current->right->left) min = current->right->pop_min();
        else min = current->right;
        current->index = min->index;
        current->value = min->value;
        min->right = nullptr;
        delete min;
    } else if (!current->left && !current->right) {
        if (is_left) previous->left = nullptr;
        else previous->right = nullptr;
        delete current;
    } else if (!current->right && is_left) {
        previous->left = current->left;
        current->left = nullptr;
        current->right = nullptr;
        delete current;
    } else if (!current->right) {
        previous->right = current->left;
        current->left = nullptr;
        current->right = nullptr;
        delete current;
    } else if (!current->left && is_left) {
        previous->left = current->right;
        current->left = nullptr;
        current->right = nullptr;
        delete current;
    } else if (!current->right) {
        previous->right = current->right;
        current->left = nullptr;
        current->right = nullptr;
        delete current;
    } else if (is_left) {
        if (current->right->left) min = current->right->pop_min();
        else min = current->right;
        previous->left = min;
        min->left = current->left;
        if (min != current->right) min->right = current->right;
        current->left = nullptr;
        current->right = nullptr;
        delete current;
    } else {
        if (current->right->left) min = current->right->pop_min();
        else min = current->right;
        previous->right = min;
        min->left = current->left;
        if (min != current->right) min->right = current->right;
        current->left = nullptr;
        current->right = nullptr;
        delete current;
    }
    return value;
}

#endif