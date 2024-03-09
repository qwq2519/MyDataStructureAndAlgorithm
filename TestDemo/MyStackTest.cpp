#include "MyStack.hpp"

#include <stack>
#include<string>
#include<iostream>

#define out(x,y) cout<<x<<y
using namespace std;
using namespace MyStack;

bool test1(){

    stack<char> s;
    MyStack::FixedSizeStack<char> m(50);

    out(m.isEmpty(),'\n');


    string str="123456789";
    for(auto i:str){
        s.push(i);
        m.push(i);
        out(s.size(),' ');
        out(m.Size(),'\n');
    }

    for(auto i:str){
        out(s.top(),' ');
        out(m.top(),'\n');
        s.pop();m.pop();
    }

    return true;
}

int main(){
    test1();

}
