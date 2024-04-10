//
// Created by 2519 on 2024/4/9.
//

#ifndef MYDATASTRUCTUREANDALGORITHM_MYKMP_H
#define MYDATASTRUCTUREANDALGORITHM_MYKMP_H

#include<string>
#include<vector>
#include<iterator>
#include<iostream>

namespace MyKMP {

    void CalcNext(std::vector<int> &kmp, const std::string &patternStr) {
        //kmp[i]表示的是0~ [i-1]的子串的相同真前后缀长度
        kmp.resize(patternStr.size() + 1);
        auto len = patternStr.size();
        // 双指针变量：
        //   i：遍历 patternStr 的主指针，从第一个字符开始。
        //   j：表示当前正在尝试匹配的最长相同前后缀子串的长度，初始值为 -1。
        for (int i{1}, j{0}; i < len;) {
            if (patternStr[i] == patternStr[j]) {//尝试前后缀匹配成功,
                kmp[++i ] = ++j;
            } else {//尝试匹配失败，j往回跳,尝试缩短要匹配的长度
                if (j != 0) {
                    j = kmp[j];
                } else {//没有公共前后缀，只能移动指针，并从0开始匹配最长公共前后缀
                    kmp[++i] = 0;
                    j = 0;
                }
            }
        }

    }

    void KMP(const std::string &textStr, const std::string &patternStr) {
        auto textLen = textStr.size();
        auto patternLen = patternStr.size();
        //部分匹配表
        std::vector<int> next(patternLen);

        CalcNext(next, patternStr);

        for (int i{0}, j{0}; i < textLen;) {
            if (textStr[i] == patternStr[j]) {
                ++i;
                ++j;
            } else if (j > 0) {//匹配不成功，尝试寻找合适的前后缀来跳
                j = next[j];
            } else {//无法匹配了，也找不到可以跳的了，文本串只能前进
                i++;
            }

            if (j == patternLen) {
                std::cout << i - patternLen << std::endl;
                j = next[j];
            }
        }
//        next.erase(next.begin());
//        std::copy(next.begin(), next.end(), std::ostream_iterator<int>(std::cout, " "));
    }
}



#endif //MYDATASTRUCTUREANDALGORITHM_MYKMP_H
