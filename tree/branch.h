#pragma once

template<typename INDEX, typename VALUE>
class Branch {
private:
    INDEX index;
    VALUE value;
    Branch *left = nullptr, *right = nullptr;

    void delete_branch();

    Branch *pop_min();

public:
    Branch(const INDEX &search_index, const VALUE &new_value) : index(search_index), value(new_value) {}

    ~Branch() {
        delete left;
        delete right;
    }

    VALUE *get(const INDEX &search_index);

    void set(const INDEX &search_index, const VALUE &new_value);

    VALUE *pop(const INDEX &search_index);

    void disp_preorder(std::ostream &os = std::cout) const;

    void disp_inorder(std::ostream &os = std::cout) const;

    void disp_postorder(std::ostream &os = std::cout) const;

    friend std::ostream &operator<<(std::ostream &os, const Branch<INDEX, VALUE> &branch) {
        branch.disp_inorder(os);
        return os;
    }
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
VALUE *Branch<INDEX, VALUE>::pop(const INDEX &search_index) {
    Branch *previous = nullptr, *current = this, *min;
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
        } else return nullptr;
    }
    if (!previous && !current->left && !current->right) throw std::exception();
    else if (!previous && !current->left) *current = *current->right;
    else if (!previous && !current->right) *current = *current->left;
    else if (!previous) {
        if (current->right->left) min = current->right->pop_min();
        else min = current->right;
        current->index = min->index;
        current->value = min->value;
        current->right = min->right;
        min->right = nullptr;
        delete min;
    } else if (!current->left && !current->right){
        if (is_left) previous->left = nullptr;
        else previous->right = nullptr;
        delete current;
    }
    else if (!current->right && is_left) {
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
    } else {
        if (current->right->left) min = current->right->pop_min();
        else min = current->right;
        current->index = min->index;
        current->value = min->value;
        current->right = min->right;
        min->right = nullptr;
        delete min;
    }
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
