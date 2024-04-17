#include<bits/stdc++.h>

using namespace std;


int main() {

    shared_ptr<int> s;
    s= make_shared<int>(5);
    cout<<*s;
    return 0;
}