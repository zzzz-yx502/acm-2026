#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	//定义&初始化
	string s1;  //空字符串
	string s2 = "hello"; string s3("world");  //直接赋值
	string s4 = s2;   //拷贝构造，只能是两个字符串之间  或者string s4(s2);
	string s5(5, 'a');   //指定n个相同的 单个字符        在字符串拼接时，如果有字符/符号是未知的s[i]需要拼接进去，就可以用这种方式 eg.s=s1+string(1,s[i])+s2;
	string s6("hello", 0, 3); string s7(s2, 2);  //截取一部分字符初始化，s6是从下标0开始，取3个字符  或者string s6(s2,0,3); s7是从s2下标2开始，一直取到末尾
	string s8(s3.begin() + 1, s3.begin() + 4);   //迭代器区间构造 左开右闭 [1,4)下标1，2，3->“orl”

	
	//赋值操作  operator= 与 assign
	string s; s = 't';  s = "test"; s = s2;   //字符串赋值时可以赋给它单个字符，但是初始化时不能eg.string s='y';这样会报错。因为std::string重载了赋值运算符operator=(char ch),专门支持把单个char赋值给string;但是std::string的构造函数中没有string(char)，若想给string初始化单个字符char，只能用string s1(1,'t')。
	string a; a.assign("abcd"); a.assign("abcd", 2); a.assign(3, 'x');  a.assign(s2.begin(), s2.end()); a.assign(s2); a.assign(s3, 1, 3);   //其中，aiassign("abcd",2)的意思是取"abcd"的前2个字符，这里的"abcd"不能写成string对象；a.assign(string字符串名，size_t pos,size_ len);从字符串的下标pos位置开始，截取长度len个字符，赋值给a


	//获取大小、容量相关成员函数
	/*
	.size() : 有效字符个数，不包括末尾‘\0’，返回size_t
	.length() : 和size()完全等价，string独有
	.capacity() : 底层分配的内存容量，>=size()
	.empty() : 判断字符串是否为空，为空返回true,返回值是bool类型
	.reserve(n) : 预分配n个内存，修改capacity，不改变size，减少多次扩容
	.resize(n) : 修改有效字符数量，改变size。capacity>=n>size,有效字符增加到n，新增位置填充默认字符‘\0’；n<size,直接截断有效字符，size变成n，capacity不变；n>capacity,先扩容
	.resize(n,ch) : 新增位置填充字符ch
	*/


	//访问字符
	/*
	operator[]下标访问 ： s[idx] 返回引用，可修改；越界不检查
	.at(idx) : 安全访问，越界抛出异常，返回引用
	.front() : 返回首字符引用
	.back() : 返回末尾字符引用
	*/
	cout << s2 << endl;
	s2.at(1) = 'y';
	s2.back() = 'x';
	cout << s2 << endl;


	//增加字符、字符串（拼接)
	/*
	.push_back(char ch) : 尾部追加单个字符，只能传char,不能传string类的
	.append() : 追加string字符串，多种重载      1.s.append(   ) ; 2.s.append(   ,n) 追加字符串前n个字符;  3.s.append(n,' ') 追加n个字符  4.s.append(s1.begin(),s1.end()) 迭代器区间追加 ；   其中，1和2里的空格，既可以是用双引号引起来的字符串“ ”，也可以是字符串对象名eg.s2
	operator+= : 支持字符、字符串、string对象 （前提：进行的是赋值操作，而不是初始化，初始化操作只支持+字符串、string对象）
	*/  


	//删除 erase、clear、pop_back
	/*
	.pop_back() : 删除末尾1个字符，无返回值
	.erase() : 四种重载      1.erase(pos,length)从下标pos开始删length个字符   2.erase(pos)从下标pos开始，删除后面全部字符    3.erase(iterator it)删除迭代器指向的单个字符    4.erase(first,last)删除迭代器区间，[first,last)左闭右开
	.clear() : 清空所有字符，size=0，capacity不变，不释放内存
	*/


	//插入insert
	/*
	.insert(pos,"c字符串”/string对象)   不存在.insert(pos,ch)
	.insert(pos,str,subpos,len) : 在下标pos处插入str(string对象)的一部分字串，该子串是从str下标subpos处开始的len个字符
	.insert(pos,count,char ch) : 下标pos处插入count个相同字符ch
	.insert(it,char ch) : 在迭代器it位置插入单个字符ch
	.insert(it,n,char ch) :  在迭代器it位置插入n个相同单个字符ch
	.insert(it,first,last) : 区间插入，左闭右开
	*/


	//替换/修改 replace ---->删掉和插入的部分长度不需要相等，容器会自动扩容/缩短
	/*
	.replace(pos,len,"c字符串"/string对象) ： 从下标pos处开始删除len个字符，替换成"c字符串"/string对象
	.replace(pos,len,string对象,subpos,sublen) : 从string对象中截子串拿来替换
	.replace(pos,len,size_t n,char ch) : 从下标pos处开始删除len个字符，替换成n个相同字符ch
	.replace(first,last,"c字符串"/string对象) ： 删除迭代器区间[first,last)里所有字符，替换成"c字符串"/string对象
	.replace(first,last,size_t n,char ch) ： 删除迭代器区间[first,last)里所有字符，替换成n个相同字符ch
	.replace(first,last,it_first,it_last) ： 删除迭代器区间[first,last)里所有字符，用另一个容器迭代器区间内容替换
	*/


	//截取子串 substr ----会生成一个全新的string副本，需要用一个string对象来接
	/*
	.substr(pos,len) : 从下标pos处开始截取len个字符
	.substr(pos) : 从下标pos处开始 一直截取到字符串末尾
	*/


	//查找系列成员函数 --->找到，返回下标(返回值类型是string::size_type,本质是size_t，无符号整数)；没找到，返回string::npos(它是一个极大值，无符号，等价-1)
	/*
	.find(str,pos) : 从下标pos开始，找子串str，返回找到的第一个匹配的起始下标；第二个参数pos可以省略，默认pos=0,从头开始寻找
	.rfind(str,pos) : 反向查找，找最后一次出现的子串；其中pos代表查找范围的终点，在[0,pos]区间内找；第二个参数pos可以省略，默认pos=npos,从最后面开始寻找
	*/


	// 比较
	/*
	1.比较运算符
	  比较规则：字典序（ASCII码逐字符对比）。从第0位开始，两个字符不一样，谁的ascii码小，字符串就更小；前面全都一样，短的字符串更小
	2.compare()成员函数，返回值：
	  0-->两个字符串完全相等
	  正数-->s大
	  负数-->s小
	s.compare(str) 整体对比
	s.compare(pos,len,str) 取s中从下标pos开始长度len的子串，和str比较
	s.compare(pos,len,str,subpos,sublen) 截取s里的一段和str里的一段对比
	*/


	//string其他常用操作
	/*
	1.swap交换 s1.swap(s2);
	2.反转字符串 reverse(起始迭代器，结束迭代器)；原地修改  eg.reverse(s.begin(),s.end())   reverse是全局算法，在头文件#include <algorithm>
	3.反转字符串，生成新字符串，原串不变  string str(s.rbegin(),s.rend());   rbegin()、rend()是反向迭代器，rbegin()指向容器最后一个有效元素；rend()指向容器第一个有效字符的前面一位   !!不能对rend(),end()解引用*
	4.to_string( )转string类 : 只支持int、long long、float、double、char等基本类型，不支持容器、结构体、类对象 
	*/
	int h = -7865;
	string y = to_string(h);//可自动处理正负
	cout << y << endl;




	return 0;
}
/*
1.string 本质是专门用来存放字符的特殊容器，底层和vector很像(连续内存)，但是封装了大量字符串专用操作
2.底层原理：和vector很像，但是多了一个SSO短字符串优化！当字符串很短（一般在15字符以内，含末尾\0），字符直接存在string对象栈内的内置缓冲区，不申请堆内存；当字符串超过缓冲区上限，才去堆上开辟连续内存存储字符
3.string内部会隐式保存\0，用于支持c_str(),但是size()不统计这个末尾的‘\0’
4.string迭代器失效规则：扩容 - 全部迭代器、指针、引用失效；erase - 删除点以及删除点之后的所有点的迭代器全部失效；insert - 插入后触发扩容，则所有迭代器失效，不扩容则插入点及之后的所有点的迭代器失效
5.string的size()、find()返回的类型是string::size_type,等价size_t,无符号整型
6.find()在string容器中是成员函数，但在vector中，是<algorithm>里的算法
*/

