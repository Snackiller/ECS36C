#include<iostream>
#include<fstream>
#include"AVL.h"
#include"json.hpp"
int main(int argc, char const *argv[])
{
    std::ifstream file;
    file.open(argv[1]);
    nlohmann::json jsonObject;
    if(file.is_open()){
        file >> jsonObject;
    }
    file.close();

    Avl tree;

    for (auto itr = jsonObject.begin(); itr != std::prev(jsonObject.end()); itr++){
        if(itr.value()["operation"] == "Insert"){
           size_t key = itr.value()["key"];
           tree.add(key);
        }
        
    }
    int treeHeight = tree.root->height_;
    nlohmann::json balancedAVLTree = tree.JSON();
    balancedAVLTree["height"] = treeHeight;
    std::cout << balancedAVLTree.dump(2) << std::endl;
    
    return 0;
}