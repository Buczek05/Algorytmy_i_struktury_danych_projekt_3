#pragma once

template<typename INDEX, typename VALUE>
class Branch {
private:
    INDEX index;
    VALUE value;
    Branch *left = nullptr, *right = nullptr;
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
};


template<typename INDEX, typename VALUE>
VALUE *Branch<INDEX, VALUE>::get(const INDEX &search_index) {
    if (index == search_index) return &value;
    else if (search_index < index && left) return left->get(search_index);
    else if (index < search_index && right) return right->get(search_index);
    else return nullptr;
}

template<typename INDEX, typename VALUE>
void Branch<INDEX, VALUE>::set(const INDEX &search_index, const VALUE &new_value) {
    if (index == search_index) value = new_value;
    else if (search_index < index) {
        if (left) left->set(search_index, new_value);
        else left = new Branch(search_index, new_value);
    } else if (index < search_index) {
        if (right) right->set(search_index, new_value);
        else right = new Branch(search_index, new_value);
    }
}

template<typename INDEX, typename VALUE>
void Branch<INDEX, VALUE>::disp_preorder(std::ostream &os) const{
    os << index << std::endl;
    if (left) left->disp_inorder(os);
    if (right) right->disp_inorder(os);
}


template<typename INDEX, typename VALUE>
void Branch<INDEX, VALUE>::disp_inorder(std::ostream &os) const{
    if (left) left->disp_inorder(os);
    os << index << std::endl;
    if (right) right->disp_inorder(os);
}

template<typename INDEX, typename VALUE>
void Branch<INDEX, VALUE>::disp_postorder(std::ostream &os) const{
    if (left) left->disp_inorder(os);
    if (right) right->disp_inorder(os);
    os << index << std::endl;
}
