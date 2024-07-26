/*****************************************************************//**
 * \file   word_spilt_dp.cpp
 * \brief  动态规划方法
 * \author Hyoung
 * \date   2024 03 31
 *********************************************************************/
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
using namespace std;

/**
 * \brief 使用动态规划方法判断字符串是否可以被拆分为字典中的单词
 * \param s 输入的字符串
 * \param wordDict 字典
 * \return 如果字符串可以被拆分为字典中的单词，则返回true，否则返回false
 */
bool wordSpilt_DP(string s, unordered_set<string>& wordDict) {
    vector<bool> dp(s.length() + 1, false); // dp[i]表示s的前i个字符是否可以被拆分为字典中的单词
    dp[0] = true; // 空字符串可以被拆分
    for (int i = 1; i <= s.length(); ++i) {// 遍历字符串s
        for (int j = 0; j < i; ++j) {// 遍历字符串s的前i个字符
            if (dp[j] && wordDict.find(s.substr(j, i - j)) != wordDict.end()) {
                dp[i] = true;// 如果前j个字符可以被拆分，且s[j,i)在字典中，则s[0,i)可以被拆分
                break;
            }
        }
    }
    return dp[s.length()];// 返回此部分子串是否可以被拆分
}

int main() {
    string s;
    cout << "Enter the string: ";
    cin >> s;

    int n;
    cout << "Enter the number of words in dictionary: ";
    cin >> n;

    cout << "Enter the words of dictionary: ";
    unordered_set<string> wordDict;
    for (int i = 0; i < n; ++i) {
        string word;
        cin >> word;
        wordDict.insert(word);
    }

    if (wordSpilt_DP(s, wordDict)) {
        cout << "true" << endl;
    }
    else {
        cout << "false" << endl;
    }
    return 0;
}
