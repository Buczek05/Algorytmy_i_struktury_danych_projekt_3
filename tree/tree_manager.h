#pragma once

#include <iostream>
#include "./branch.h"

template<typename INDEX, typename VALUE>
class TreeManager {
private:
    Branch<INDEX, VALUE> root;
public:
    TreeManager(const INDEX &index, const VALUE &value) : root(index, value) {}
    VALUE *get(INDEX index);
    //VALUE *pop(INDEX index);
    void set(INDEX index, VALUE value);
    void disp_preorder(std::ostream &os = std::cout) const {root.disp_preorder(os);};
    void disp_inorder(std::ostream &os = std::cout) const {root.disp_inorder(os);};
    void disp_postorder(std::ostream &os = std::cout) const {root.disp_postorder(os);};
    friend std::ostream &operator<<(std::ostream &os, const TreeManager<INDEX, VALUE> &tree_manager) {
        tree_manager.disp_inorder(os);
        return os;
    }
};

template<typename INDEX, typename VALUE>
VALUE *TreeManager<INDEX, VALUE>::get(INDEX index) {
    return root.get(index);
}

template<typename INDEX, typename VALUE>
void TreeManager<INDEX, VALUE>::set(INDEX index, VALUE value) {
    root.set(index, value);
}
