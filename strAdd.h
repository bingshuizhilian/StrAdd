#ifndef USERMAIN_H_
#define USERMAIN_H_

#include <iostream>
#include <string>
#include <map>

using std::string;

//map容器，字符串数字与整型数字一一对应的键值对
typedef std::pair<string, int> Pair;
const std::map<string, int> NUM_MAP = {
	Pair("zero", 0), Pair("one", 1),
	Pair("two", 2), Pair("three", 3),
	Pair("four", 4), Pair("five", 5),
	Pair("six", 6), Pair("seven", 7),
	Pair("eight", 8), Pair("nine", 9),
};

class StrAdd{
private:
	static const char SPACE = ' ';//默认输入的字符串间隔为空格，可以更改
	enum MODE { STRING, INTEGER };//标识符，根据字符串或整型数计算数字位数
	string m_string;//保存输入的字符串
	int m_numOfDigits;//数字位数
	int m_integer;//字符串对应的整型数
public:
	StrAdd();
	StrAdd(const string& str);
	friend std::istream& operator >> (std::istream& is, StrAdd& strAdd);
	friend std::ostream& operator << (std::ostream& os, const StrAdd& strAdd);
	StrAdd operator + (StrAdd& strAdd);
	void ToLower(void);//使输入不区分大小写
	void CalculateDigits(MODE mode);//根据字符串或整型数计算数字位数
	void StringToInteger(void);//字符串转换到整型数
	void IntegerToString(void);//整型数转换到字符串
};

#endif
