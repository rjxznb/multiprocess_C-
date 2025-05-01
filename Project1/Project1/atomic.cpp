#include<iostream>
#include<vector>
#include"DataStruct.h"
using namespace std;



int main() {
    RedBlackTree rbt;
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(40);
    rbt.insert(50);
    rbt.insert(25);

    cout << "Tree after insertion:" << endl;
    rbt.print();

    rbt.deleteNode(30);
    cout << "Tree after deleting 30:" << endl;
    rbt.print();

    rbt.search(25);
    rbt.search(30);

}