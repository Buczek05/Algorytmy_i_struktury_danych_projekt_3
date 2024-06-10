#pragma once

#include <iostream>
#include "./branch.h"
#include "./exceptions.h"

template<typename INDEX, typename VALUE>
class TreeManager {
private:
    Branch<INDEX, VALUE> *root;

    void set_root(const INDEX &index, const VALUE &value) { root = new Branch<INDEX, VALUE>(index, value); };
public:
    TreeManager() : root(nullptr) {}

    TreeManager(const INDEX &index, const VALUE &value) { set_root(index, value); }

    VALUE *get(INDEX index);

#ifdef USE_RECURRENCE

    void pop(INDEX index);

#else

    VALUE pop(INDEX index);

#endif

    void set(INDEX index, VALUE value);

    void disp_preorder(std::ostream &os = std::cout) const { if (root) root->disp_preorder(os); };

    void disp_inorder(std::ostream &os = std::cout) const { if (root) root->disp_inorder(os); };

    void disp_postorder(std::ostream &os = std::cout) const { if (root) root->disp_postorder(os); };

    friend std::ostream &operator<<(std::ostream &os, const TreeManager<INDEX, VALUE> &tree_manager) {
        tree_manager.disp_inorder(os);
        return os;
    }
};

template<typename INDEX, typename VALUE>
VALUE *TreeManager<INDEX, VALUE>::get(INDEX index) {
    if (!root) return nullptr;
    return root->get(index);
}

template<typename INDEX, typename VALUE>
void TreeManager<INDEX, VALUE>::set(INDEX index, VALUE value) {
    if (!root) set_root(index, value);
    else root->set(index, value);
}

#ifdef USE_RECURRENCE

template<typename INDEX, typename VALUE>
void TreeManager<INDEX, VALUE>::pop(INDEX index) {
    root = root->deleteNode(root, index);
}

#else

template<typename INDEX, typename VALUE>
VALUE TreeManager<INDEX, VALUE>::pop(INDEX index) {
    VALUE pop_value;
    if (root != nullptr) {

        try {
            return root->pop(index);
        }
        catch (PopElementIsRoot) {
            pop_value = root->get_value();
            root = nullptr;
            return pop_value;
        }
    }
}

#endif