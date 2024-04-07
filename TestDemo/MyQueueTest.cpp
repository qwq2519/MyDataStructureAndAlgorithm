#include "MyQueue.hpp"
#include <iostream>
#include<cstdint>
#include<bits/stdc++.h>
using namespace MyQueue;
using namespace std;
void test() {

    int n;
    ArrayLoopQueue<int> q(10110);
    cin >> n;
    while (n--) {
        int x, y;
        cin >> x;
        switch (x) {
            case 1: {
                cin >> y;
                q.Push(y);
                break;
            }
            case 2: {
                if (q.IsEmpty()) {
                    std::cout << "ERR_CANNOT_POP" << std::endl;

                } else q.Pop();
                break;
            }
            case 3: {
                if (q.IsEmpty()) {
                    cout << "ERR_CANNOT_QUERY" << std::endl;
                } else cout << q.Front() << endl;
                break;
            }
            case 4: {
                cout << q.Size() << endl;
                break;
            }
            default: {
            }
        }

       // std::cout << "SIZE:" << q.Size() << endl;
    }
}

void test2(){
    LinkedQueue<vector<int>> q;
    vector<int> v;

    for(int i=1;i<=10;++i){
            v.push_back(i);
            q.Push(v);
    }
    while(!q.IsEmpty()){
        auto i=q.Front();
        for(auto j:i){
            cout<<j<<' ';
        }cout<<endl;
        q.Pop();
    }
    return ;
}

int main() {
    //test();
    test2();
    return 0;
}
/*
 *
 */