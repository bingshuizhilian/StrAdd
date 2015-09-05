#include "strAdd.h"

StrAdd::StrAdd() :m_string(""), m_integer(0), m_numOfDigits(1){
//默认构造函数，设定以此函数构造的对象携带空字符串，以及1位数字0
}

StrAdd::StrAdd(const string& str) : m_string(str){//e.g. StrAdd temp("one two");
	ToLower();
	StringToInteger();//初始化m_numOfDigits与m_integer
}

void StrAdd::ToLower(void){//把用户输入的每一位转换为小写
	for (auto it = m_string.begin(); it != m_string.end(); ++it)
		*it = tolower(*it);
}

void StrAdd::CalculateDigits(MODE mode){
	if (STRING == mode)//由字符串信息计算数字位数
		for (auto it = m_string.begin(); it != m_string.end(); ++it){
		if (isspace(*it))//字符串里有几个间隔（默认为空格），位数就为间隔数加一
			++m_numOfDigits;
		}
	else if (INTEGER == mode){//由整型数信息计算数字位数
		int temp = m_integer;
		for (int count = 0; count < INT_MAX; ++count){//改为INT_MAX的位数好一些，不过确保退出循环条件正确即可
			if (0 != temp / 10){//计算位数，默认位数为1，不断除10，结果不为0位数就加一
				temp /= 10;
				++m_numOfDigits;
			}
			else
				break;
		}
	}
}

void StrAdd::StringToInteger(void){//这个函数写的好臃肿，希望有高人点拨下，功能："one two three"->123，不限位数
	CalculateDigits(STRING);//由字符串信息计算数字位数
	if (1 == m_numOfDigits){//只有一位数的情况，比较简单
		for (auto elem : NUM_MAP){
			if (elem.first == m_string)
				m_integer = elem.second;
		}
	}
	else{
		string::iterator *pIter = new string::iterator[m_numOfDigits - 1];//存储指向找到的间隔符的迭代器
		int count = 0;
		for (auto it = m_string.begin(); it != m_string.end(); ++it){//遍历字符串，把指向间隔符的迭代器存储起来
			if (SPACE == *it)
				pIter[count++] = it;
		}

		string intTemp;//临时存储内容为整型数的字符串，e.g. "1234"
		string strTemp;//临时存储提取的子字符串
		char c_tempDigit[2];//为了使用_itoa，把1位阿拉伯数字转为字符，预留1位'\0'位
		for (int counter = 0; counter < m_numOfDigits - 1; ++counter){
			if (2 == m_numOfDigits){//只有两位数，则只有一个指向间隔符的迭代器
				strTemp.assign(m_string.begin(), pIter[counter]);//提取字符串的第一个子字符串
				for (auto elem : NUM_MAP){
					if (elem.first == strTemp)//把这个子字符串对应的整型数转换为字符串后拼接到intTemp后面
						intTemp.append(_itoa(elem.second, c_tempDigit, 10));
				}

				strTemp.assign(pIter[counter] + 1, m_string.end());//提取字符串的最后一个子字符串（此时为两位数）
				for (auto elem : NUM_MAP){
					if (elem.first == strTemp)
						intTemp.append(_itoa(elem.second, c_tempDigit, 10));
				}
				m_integer = atoi(intTemp.c_str());//得到字符串携带的整型数，e.g. "1234"->1234
			}
			else{//位数大于2的时候
				if (0 == counter){//提取字符串的第一个子字符串，并转换拼接到intTemp后面
					strTemp.assign(m_string.begin(), pIter[counter]);
					for (auto elem : NUM_MAP){
						if (elem.first == strTemp)
							intTemp.append(_itoa(elem.second, c_tempDigit, 10));
					}
				}

				if (m_numOfDigits - 2 != counter){//提取字符串的中间部分的子字符串，并转换拼接到intTemp后面
					strTemp.assign(pIter[counter] + 1, pIter[counter + 1]);
					for (auto elem : NUM_MAP){
						if (elem.first == strTemp)
							intTemp.append(_itoa(elem.second, c_tempDigit, 10));
					}
				}

				if (m_numOfDigits - 2 == counter){//提取字符串的最后一个子字符串，并转换拼接到intTemp后面
					strTemp.assign(pIter[counter] + 1, m_string.end());
					for (auto elem : NUM_MAP){
						if (elem.first == strTemp)
							intTemp.append(_itoa(elem.second, c_tempDigit, 10));
					}
					m_integer = atoi(intTemp.c_str());//得到字符串携带的整型数，e.g. "1234"->1234
				}
			}
		}
	
		delete[] pIter;
	}
}

void StrAdd::IntegerToString(void){//整型数转换到字符串
	CalculateDigits(INTEGER);//由整型数信息计算数字位数
	char* intBuff = new char[m_numOfDigits + 1];//_itoa使用，预留'\0'位
	string strTemp = _itoa(m_integer, intBuff, 10);//e.g. 1234->"1234"
	for (int count = 0; count < m_numOfDigits; ++count)
		for (auto elem : NUM_MAP){//把每一位整型数对应的字符串拼接到m_string后面
		if (elem.second == atoi(strTemp.substr(count, 1).c_str())){
			m_string.append(elem.first);
			if (count != m_numOfDigits - 1)
				m_string.push_back(SPACE);//只要不是最后一位，就添加间隔符
		}
		}
	delete[] intBuff;
}

std::istream& operator >> (std::istream& is, StrAdd& strAdd){//重载>>运算符，以使用cin
	getline(is, strAdd.m_string);
	return is;
}

std::ostream& operator << (std::ostream& os, const StrAdd& strAdd){//重载<<运算符，以使用cout
	os << strAdd.m_string;//此处可以追加额外打印信息，即字符串代表的整型数与位数信息
	return os;
}

StrAdd StrAdd::operator + (StrAdd& strAdd){//重载+运算符
	StrAdd temp;
	ToLower();
	StringToInteger();
	strAdd.ToLower();
	strAdd.StringToInteger();
	temp.m_integer = m_integer + strAdd.m_integer;
	temp.IntegerToString();

	return temp;
}
