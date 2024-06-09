#include <sstream>
#include "../tree/tree_manager.h"

int tree_1_indexes[] = {9};
int tree_2_indexes[] = {9, 4, 2, 6, 1, 3, 5, 7}; // prawe puste
int tree_3_indexes[] = {0, 4, 2, 6, 1, 3, 5, 7}; // lewe puste
int tree_4_indexes[] = {9, 4, 2, 6, 1, 3, 5, 7, 15, 13, 17, 12, 14, 16, 18}; // oba
int tree_5_indexes[] = {9, 4}; // prawe puste
int tree_6_indexes[] = {9, 11}; // lewe puste

TreeManager<int, int> create_tree(int *indexes, int len) {
    TreeManager<int, int> tree(indexes[0], indexes[0]);
    for (int i = 1; indexes[i] != len; i++) {
        tree.set(indexes[i], indexes[i]);
    }
    return tree;
}

bool is_sorted(TreeManager<int, int> &tree) {
    std::ostringstream osstream;
    tree.disp_inorder(osstream);
    std::istringstream stream(osstream.str());

    int currentVal, previousVal = INT_MIN;
    while (stream >> currentVal) {
        if (currentVal < previousVal)
            return false;
        previousVal = currentVal;

        if (stream.peek() == '\n')
            stream.ignore();
    }

    return true;
}

bool is_other_in_three(TreeManager<int, int> &tree, int *indexes, int len, int removed) {
    for (int i = 0; i < len; i++) {
        if (indexes[i] != removed && tree.get(indexes[i]) == nullptr) return false;
    }
    return true;
}

bool test_delete_root_without_right() {
    TreeManager<int, int> tree = create_tree(tree_2_indexes, 7);
    tree.pop(9);
    if (tree.get(9) != nullptr) {
        std::cout << "Still exist";
        return false;
    }
    return is_sorted(tree) && is_other_in_three(tree, tree_2_indexes, 7, 9);
}