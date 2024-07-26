/*****************************************************************//**
 * \file   word_spilt_re.cpp
 * \brief  �ݹ鷽��
 * \author Hyoung
 * \date   2024 03 31
 *********************************************************************/
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
using namespace std;

/**
 * \brief  �ݹ鷽���ж��ַ����Ƿ���Ա����Ϊ�ֵ��еĵ���
 * \param  s: ���жϵ��ַ���
 * \param  wordDict: �ֵ�
 * \return �Ƿ���Ա����Ϊ�ֵ��еĵ���
 */
bool wordSpilt_re(string s, unordered_set<string>& wordDict)
{
	if(s.empty()) //�ж��Ƿ�Ϊ�գ�Ϊ����˵�����Ա��ָ����true
		return true;
	for (int i = 1; i <= s.length(); ++i) {
		string prefix = s.substr(0, i);
		if (wordDict.find(prefix) != wordDict.end() && wordSpilt_re(s.substr(i), wordDict)) {
			return true; //���ǰ׺���ֵ��У��Һ�׺Ҳ���ֵ��У��򷵻�true
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