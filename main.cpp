#include <iostream>
#include "BinaryTree.h"
#define newline std::cout << '\n'

int main() {
    BSTree<int> bst;
    int n=0;
    int val=0;
    std::cin>>n;
    for(int i=0;i<n;i++){
        std::cin>>val;
        bst.insert(val);
    }
    newline;
    std::cout << bst.size() << " "<<bst.depth()<<" "<<std::endl;
    newline;
    std::cout << "PRINT IN ORDER: " << std::endl;
    bst.printInOrder();
    newline;
    std::cout << "FOR-EACH " << std::endl;
    for(const auto& k : bst)
    {
        std::cout << k << std::endl;
    }

    return 0;
}
