#include "MyStack.hpp"

#include <stack>
#include<string>
#include<iostream>

#define out(x,y) cout<<x<<y
#define outln(x) cout<<x<<'\n'

using namespace std;
using namespace MyStack;

bool test1(){

    stack<int> s;
    MyStack::ArrayStack<int> t(55);
    for(int i=0;i<=9;++i){
        int tt=i;
        t.push(tt);
        out(t.top(),t.Size());cout<<'\n';
    }
}

int main(){
    test1();

}
