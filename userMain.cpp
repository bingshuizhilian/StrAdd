#include "strAdd.h"

int main(){
	using std::cout;
	using std::endl;
	using std::cin;

	StrAdd add1, add2, result;//可以像内置类型一样使用，只重载了无符号加法
	cout << "请输入第一个加数：";
	cin >> add1;
	cout << "请输入第二个加数：";
	cin >> add2;

	result = add1 + add2;
	cout << "结果为：" << result << endl;

	/* 可以直接如下所示打印结果，或者以你想要的格式打印，就像使用内置类型一样
	cout << "结果为：" << add1 + add2 << endl;
	*/
		
	return 0;
}
