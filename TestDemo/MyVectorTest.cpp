
#include<bits/stdc++.h>
#include"ds/MyVector.hpp"
#include<iterator>
using  namespace std;
namespace MergeSort {
    template<typename Iterator>
    void Merge(Iterator aBegin, Iterator aEnd, Iterator bBegin, Iterator bEnd, Iterator begin) {
        std::vector<std::decay_t<decltype(*begin)> > temp;
        while (aBegin != aEnd && bBegin != bEnd) {
            temp.emplace_back((*aBegin < *bBegin) ? (*aBegin++) : (*bBegin++));
        }
        std::copy(aBegin, aEnd, std::back_inserter(temp));
        std::copy(bBegin, bEnd, std::back_inserter(temp));
        std::copy(temp.begin(), temp.end(), begin);
    }

    template<typename Iterator>
    void SortRecursion(Iterator begin, Iterator end) {
        auto len = std::distance(begin, end);
        if (len <= 1) return;
        Iterator middle = begin + (len >> 1);
        SortRecursion(begin, middle);
        SortRecursion(middle, end);
        Merge(begin, middle, middle, end, begin);
//        std::inplace_merge(begin, middle, end);//系统自带的合并，会申请缓存空间，申请成功会使用线性合并，否则用的是低效合并
    }

    template<typename Iterator>
    void SortBinaryLifting(Iterator begin, Iterator end) {
        size_t len = std::distance(begin, end);
        if (len <= 1) return;
        for (size_t seg(1); seg < len; seg <<= 1) {
            for (size_t left1(0); left1 < len - seg; left1 += seg + seg) {//n-seg最后剩下一个段，就不用合并了
                size_t right1(left1 + seg);
                size_t left2(right1);
                size_t right2 = std::min(left2 + seg, len);//最后一个段的边界
                Merge(begin + left1, begin + right1, begin + left2, begin + right2, begin + left1);
            }
        }
    }
}

void test(){
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distribution(-100, 100);


    MyVector::Vector<int> a,b;
    for(int i=1;i<=10;++i){
        a.PushBack(distribution(engine));
        b.PushBack(distribution(engine));
    }
    MyVector::Vector<int> ans(50,0);

    MergeSort::SortRecursion(a.begin(),a.end());
    MergeSort::SortRecursion(b.begin(),b.end());
    a.Print();
    cout<<endl;
    b.Print();
    cout<<endl;


    MergeSort::Merge(a.begin(),a.end(),b.begin(),b.end(),ans.begin());
    ans.Print();
}
int main(){
    test();
    return 0;
}