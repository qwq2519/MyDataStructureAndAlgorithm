#include "MyStack.hpp"

#include<string>
#include<iostream>
#include<stack>
#define out(x,y) cout<<x<<y
#define outln(x) cout<<x<<'\n'

using namespace std;
using namespace MyStack;

bool test1(){

    LinkedStack<string> s1;
    ArrayStack<string> s2(1000);
    std::stack<string> s3;
    string s="114514545";
    s1.Push(s);
    s2.Push(s);
    cout<<s1.Top()<<' '<<s2.Top();
    return true;
}

int main(){
    test1();

}
