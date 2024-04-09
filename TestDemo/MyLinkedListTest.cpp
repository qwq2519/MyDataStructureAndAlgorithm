#include "ds/MyLinkedList.hpp"
#include <iostream>
#include <bits/stdc++.h>
#include"ds/MyOrthogonalList.hpp"
using namespace std;

void test() {

    MyLinkedList::DoubleLinkedList<int> a,b,t;

    int n,m,ele;
    cin>>n;
    while(n--){
        cin>>ele;
        a.InsertLast(ele);
    }
    cin>>m;
    while(m--){
        cin>>ele;
        b.InsertLast(ele);
    }
    t=a-b;
    cout<<t;
    return ;
}
/*
10
2 1 4 5 8 7 8 9 0 -1
6
1 3 6 8 4 3
 */
void test2(){
    MyLinkedList::DoubleLinkedList<int> a;
    a.InsertLast(-1);
    a.InsertLast(0);//1
    a.InsertLast(1);
    a.InsertLast(2);//3
    a.InsertLast(3);
    a.InsertLast(4);//5
    a.InsertLast(5);
    a.InsertLast(6);//7
    a.InsertLast(7);
    a.InsertLast(8);//9
    a.InsertLast(8);
    a.InsertLast(8);//10
    a.InsertLast(9);

    cout<<a.GetValue(10)<<endl;


}

void test3(){
    MyOrthogonalList::OrthogonalList<int> t(4,4);
    t.AddNode(3,4,4);
    t.AddNode(1,4,5);
    t.AddNode(2,2,-1);
    t.AddNode(3,1,2);

    t.Print();
    cout<<endl;
}

int main() {
//    test();
test3();
    return 0;
}