/*****************************************************************//**
 * \file   word_spilt_re.cpp
 * \brief  递归方法
 * \author Hyoung
 * \date   2024 03 31
 *********************************************************************/
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
using namespace std;

/**
 * \brief  递归方法判断字符串是否可以被拆分为字典中的单词
 * \param  s: 待判断的字符串
 * \param  wordDict: 字典
 * \return 是否可以被拆分为字典中的单词
 */
bool wordSpilt_re(string s, unordered_set<string>& wordDict)
{
	if(s.empty()) //判断是否为空，为空则说明可以被分割，返回true
		return true;
	for (int i = 1; i <= s.length(); ++i) {
		string prefix = s.substr(0, i);
		if (wordDict.find(prefix) != wordDict.end() && wordSpilt_re(s.substr(i), wordDict)) {
			return true; //如果前缀在字典中，且后缀也在字典中，则返回true
		}
	}
	return false;
}

int main()
{
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

	if (wordSpilt_re(s, wordDict))
		cout << "true" << endl;
	else
		cout << "false" << endl;
	return 0;
}