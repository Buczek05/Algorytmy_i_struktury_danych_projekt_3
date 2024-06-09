#include "../tree/tree_manager.h"
#include <iostream>


#include <string>
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(1, 100000);

    TreeManager<int, std::string> manager(distr(eng), std::to_string(distr(eng)));
    int temp;
    for (int i = 0; i < 100; i++) {
        temp = distr(eng);
        manager.set(temp, std::to_string(temp));
    }
    manager.disp_preorder();
    std::cout << std::endl;
    manager.disp_inorder();
    std::cout << std::endl;
    manager.disp_postorder();
    return 1;
}