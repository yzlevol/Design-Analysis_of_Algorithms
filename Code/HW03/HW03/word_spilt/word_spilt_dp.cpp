/*****************************************************************//**
 * \file   word_spilt_dp.cpp
 * \brief  ��̬�滮����
 * \author Hyoung
 * \date   2024 03 31
 *********************************************************************/
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
using namespace std;

/**
 * \brief ʹ�ö�̬�滮�����ж��ַ����Ƿ���Ա����Ϊ�ֵ��еĵ���
 * \param s ������ַ���
 * \param wordDict �ֵ�
 * \return ����ַ������Ա����Ϊ�ֵ��еĵ��ʣ��򷵻�true�����򷵻�false
 */
bool wordSpilt_DP(string s, unordered_set<string>& wordDict) {
    vector<bool> dp(s.length() + 1, false); // dp[i]��ʾs��ǰi���ַ��Ƿ���Ա����Ϊ�ֵ��еĵ���
    dp[0] = true; // ���ַ������Ա����
    for (int i = 1; i <= s.length(); ++i) {// �����ַ���s
        for (int j = 0; j < i; ++j) {// �����ַ���s��ǰi���ַ�
            if (dp[j] && wordDict.find(s.substr(j, i - j)) != wordDict.end()) {
                dp[i] = true;// ���ǰj���ַ����Ա���֣���s[j,i)���ֵ��У���s[0,i)���Ա����
                break;
            }
        }
    }
    return dp[s.length()];// ���ش˲����Ӵ��Ƿ���Ա����
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
