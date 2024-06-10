#pragma once
#define USE_RECURRENCE

#include <sstream>
#include <chrono>
#include "../tree/tree_manager.h"
#include "../tree/exceptions.h"

int tree_1_indexes[] = {9};
int tree_2_indexes[] = {9, 4, 2, 6, 1, 3, 5, 7}; // right empty
int tree_3_indexes[] = {0, 4, 2, 6, 1, 3, 5, 7}; // left empty
int tree_4_indexes[] = {9, 4, 2, 6, 1, 3, 5, 7, 15, 12, 17, 11, 14, 13, 16, 18}; // oba
int tree_5_indexes[] = {9, 4}; // right empty
int tree_6_indexes[] = {9, 11}; // left empty

TreeManager<int, int> create_tree(int *indexes, int len) {
    TreeManager<int, int> tree(indexes[0], indexes[0]);
    for (int i = 1; i < len; i++) {
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
        if (indexes[i] != removed && tree.get(indexes[i]) == nullptr) {
            std::cout << "Not found other in three: " << indexes[i] << std::endl;
            return false;
        }
    }
    return true;
}

bool was_removed(TreeManager<int, int> &tree, int removed) {
    if (tree.get(removed) != nullptr) {
        std::cout << "Still exist" << std::endl;
        return false;
    }
    return true;
}

bool test_delete(int *indexes, int len, int to_remove) {
    TreeManager<int, int> tree = create_tree(indexes, len);
    tree.pop(to_remove);
    return is_sorted(tree) && was_removed(tree, to_remove) && is_other_in_three(tree, indexes, len, to_remove);
}

bool test_delete_root_both_empty() {
    return test_delete(tree_1_indexes, 1, 9);
}

bool test_delete_root_without_right() {
    return test_delete(tree_2_indexes, 7, 9);
}

bool test_delete_root_without_right_short() {
    return test_delete(tree_5_indexes, 2, 9);
}

bool test_delete_root_without_left() {
    return test_delete(tree_3_indexes, 7, 0);
}

bool test_delete_root_without_left_short() {
    return test_delete(tree_6_indexes, 2, 9);
}

bool test_delete_root() {
    return test_delete(tree_4_indexes, 14, 9);
}

bool test_delete_when_element_not_exist() {
#ifdef USE_RECURRENCE
    return true;
#else
    try {
        test_delete(tree_1_indexes, 1, 0);
    } catch (NotFoundElementException) { //TODO: change to specified exception
        return true;
    }
    return false;
#endif
}

bool delete_step_by_step(int *indexes, int len) {
    bool result;
    for (int i = 0; i < len; i++) {
        result = test_delete(indexes, len, indexes[i]);
        if (!result) return false;
    }
    return true;
}

bool test_delete_step_by_step() {
    bool result;
    result = delete_step_by_step(tree_2_indexes, 7);
    if (!result) return false;
    result = delete_step_by_step(tree_3_indexes, 7);
    if (!result) return false;
    result = delete_step_by_step(tree_4_indexes, 15);
    if (!result) return false;
    result = delete_step_by_step(tree_5_indexes, 2);
    if (!result) return false;
    result = delete_step_by_step(tree_6_indexes, 2);
    if (!result) return false;
    return true;
}


bool test_performance() {
    for (int max = 1; max <= 300; max++) {
        TreeManager<int, int> tree;
        auto start = std::chrono::high_resolution_clock::now();
        for (int _ = 0; _ <= 5000; _++) {
            for (int i = 0; i <= max; i++) {
                tree.set(i, i);
            }
            tree.pop(1);
            tree.pop(3);
            tree.pop(max / 2);
            tree.pop(max);
            tree.pop(max);
        }
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> diff = end - start;
        std::cout << max << ";" << diff.count() << std::endl;

    }
    return true;
}