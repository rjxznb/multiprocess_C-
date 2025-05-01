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
   
    
    vector<int> v(6);
    string s2 = "nihao";
    copy(s2.begin(), s2.end(), v.begin() + 1);
    for (auto i : v) {
        cout << i;
    }
    return 0;

}