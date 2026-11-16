#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Student {
	int id;
	string name;
	//构造函数---1.构造函数名称和结构体类型名/类名完全一样  2.没有函数类型  3.如果自己不写，编译器会自动生成一个无参默认构造函数  4.结构体struct和class构造函数语法完全一样，struct默认public  5.可以写多个构造函数，满足不同的初始化需求  6.创建对象的时候自动调用
	Student(int id_,string name_):id(id_),name(name_){}
};

int main() {
	//vector定义: vector <T> v;          T:存储元素类型，可以是int、double、string、结构体、类
	
	/*
	vector初始化
	1. vector<int>v1;   空vector,存储int.
	2. vector<int>v2(5);   开辟5个元素，全部初始化为0.
	3. vector<int>v3(5,10);   开辟5个元素，全部初始化为10.
	4. vector<int>v4{1,2,3,4,5};   用大括号直接初始化(C++11及以上支持)
	5. vector<int>v5(v4);   拷贝构造，复制v4全部内容
	6. vector<int>v6(v4.begin()+1,v4.end());   迭代器区间拷贝，把v4[1]-v4[4]复制过来
	*/

	//vector存放结构体   vector<Student>
	vector<Student>stu;
	stu.push_back(Student{ 1001,"zhangsan" });//Student{1001,"zhangsan"}是临时结构体对象；先在容器外面的栈上创建临时对象，vector拿到之后把这个对象拷贝/移动到vector内部的内存，外面的临时对象随后销毁。
	stu.emplace_back(1002,"lisi");//emplace_back直接在vector容器内部的内存空间原地构造Student对象；

	
	//vector存放结构体指针   vector<Student*>,要注意内存管理!!指针指向的结构体，要自己new开辟堆内存，用完必须delete释放，否则内存泄漏。
	vector<Student*> STU;
	Student* p1 = new Student{ 1003,"wang" };
	STU.push_back(p1); //STU.push_back(new Student{1003,"wang"});
	cout << stu[0].id << " " << stu[1].name<< " " << STU[0]->id << " " << STU[0]->name << endl;//访问指针容器元素!!注意->
	delete(STU[0]);//手动释放每一个new的内存
	STU.clear();//.clear()是vector的成员函数，清空vector容器里的元素，size直接变成0，但是capacity容量不会释放，内存还占着

	
	//vector模拟二维数组(vector没有真正的二维数组，是容器嵌套容器)    vector<vector<T>> 变量名；
	//外层vector:每一个元素是一个内层vector<T>    内存特点:行与行之间内存不连续，同一行内部元素之间内存连续。
	vector<vector<int>> arr(3,vector<int>(4,0)); //指定行数、列数，且全部初始化为默认值。  vector<vector<T>> 变量名 (行数，vector<T>(列数)）；
	vector<vector<int>> a{ {1,2,3},{4,5,6},{7,8,9} }; //初始化列表直接赋值
	vector<vector<int>> b; b.push_back({ 10,20,30 }); //定义一个空二维vector，后续动态push_back()增加行，这种方式每行列数可以不一样
	vector<vector<int>> c(5); c[0].push_back(1); //行数确定，每一行是一个空vector.  c[i]代表第i行
	size_t cnt1 = arr.size(),cnt2=arr[0].size(); //size_t 专门存放容器大小、下标、长度等无符号(非负数)的数据类型，最小值是0，vector中的.size()、.capacity()返回值就是size_t类型的。  !!！可以int-size_t，但是不可以用size_t-int,因为无符号数永远不会出现负数。0-1时，二进制全部置1，变成极大的数值
	for (int i = 0; i < a.size(); i++) { //遍历完整二维vector的安全写法---下标遍历
		for (int j = 0; j < a[i].size(); j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	for (auto& row : b) { //范围for循环:auto-自动类型推导，让编译器自动判别row的类型；&-引用符号，只引用不拷贝；row-循环变量名；b-要循环的容器名
		for (auto& col : row) {
			cout << col << " ";
		}
		cout << endl;
	}
	for (auto it_row = a.begin(); it_row != a.end(); it_row++) { //迭代器:用来指向容器中元素的"像指针一样的对象"，不是原生指针，但用法很像指针。  .begin()返回指向第一个元素的迭代器，.end()返回末尾的后一位(不指向有效元素)
		for (auto it_col = it_row->begin(); it_col != it_row->end(); it_col++) { //it_row是外层迭代器，指向一行vector<int>；it_row->begin()是这一行的起始迭代器
			cout << *it_col << " "; //it_col相当于一个指针，在访问其元素值时，必须对迭代器解引用；   扩容后，会重新分配内存，指针/迭代器会失效
		}
		cout << endl;
	}

	//vector的变量名v 不能当作首元素的地址,首元素的地址只能是v[0]；和数组不一样；
	//指针int* p=&v[0] (int* p=v.data(),p指向堆上v的首元素的地址) 中，p[i]=*(p+i)表示第i个元素

	
	//vector大小、容量相关成员函数
	/*
	.size()   实际元素个数，返回size_t位有符号整数
	.capacity()     当前分配的内存能容纳的总容量(最多容纳元素个数)>=size，扩容才会变大
	.resize(n)    修改有效元素数量。size变大补默认值；变小截断末尾   (resize(n)新增元素时，会调用该类型的默认构造函数来创建新元素，每种类型都有对应的默认构造(int/double/char - 0;string - "";bool - false)) 对于结构体:1.当结构体没有写任何构造函数时，编译器自动合成默认构造 2.结构体写了带参数的构造函数，没有写无参，默认构造函数不会出现(要手动补上默认构造函数)，此时resize()直接编译报错
	.resize(n,val)    修改size,新增元素填val(如果是结构体struct/class类这种复杂类型，val就是一个已经构造好的、和vector元素同类型的现成对象 eg:Student stmp={1001,"zhang"};a.resize(3,stmp);)
	.reserve(n)    预分配容量capacity，不改变size! 只提前开辟内存，不会创建任何对象!完全不会调用构造函数
	.empty()    判断是否为空，返回值为bool类型，为空返回true(.size()==0)
	*/


	//vector增删改查
	/*
	1.增加元素
	.push_back(val):尾部增加
	.emplace_back(val):尾部增加，不用拷贝更高效，但依赖于构造函数
	.insert(迭代器位置pos，val):在指定迭代器位置插入元素，后面元素全部后移，效率低
	.insert(pos,n,val):在指定位置插入n个val
	.insert(pos1,pos2,pos3):在vector的pos1位置插入另一个容器的一段元素，pos2、pos3为起始迭代器位置
	vec.begin()+i:指向下标为i的元素

	2.删除元素
	.pop_back():删除尾部元素，无返回值
	.erase(迭代器位置pos):删除某一位置元素
	.erase(begin,end):删除区间[begin,end)上的元素，左闭右开；begin、end是起始迭代器位置
	.clear():清空全部元素，size()=0;capacity容量不会释放，内存还占着

	3.修改元素
	下标[]访问修改，不做越界检查!越界直接崩溃
	.at(下标index):访问修改，会做越界检查，越界抛异常，更安全

	4.查找元素
	[]下标访问
	.at(index):带检查访问
	.front():获取第一个元素      在二维vector中，v.front()返回的是第0行，类型是vector<T>&(是第0行vector的别名，可直接修改容器里的元素值) eg.auto& row=v.front();row[0]=999;第0行第0个元素值修改为999
	.back():获取最后一个元素      v.back()[0]返回最后一行第0列的元素；v.back().size()返回值是size_t类型，返回最后一行的元素个数
	
	
	--->find算法  O(n)    find是STL(标准模板库)通用算法，用来在容器里查找某个值。不是vector的成员函数，是<algorithm>里的全局函数
	
	函数原型:auto it=find(起始迭代器，结束迭代器，要找的值/容器对象)；

	[begin,end)区间左闭右开     返回值:一个迭代器       找到了:返回指向该元素的迭代器      找不到:返回结束迭代器
	找到后能做什么:if(it!=v.end()){
	                   *it=999;  修改找到的元素
					   v.erase(it);   删除找到的元素
					   int pos=it-v.begin();   获取下标
	               }

	--->find查找结构体/自定义类型
	find查找时，会依靠==逐个比较元素和目标值是否相等。在结构体等复杂的数据类型中，往往有许多不一样的成员变量，编译器不知道怎么比较就会报错!
	这个时候就需要 重载==运算符(在结构体/自定义类型的大括号里) ，告诉编译器两个结构体什么情况下算"相等"，是比较id还是什么。
	--->运算符重载:你自己定义==、+、< 这些运算符的运算规则。 写在结构体/类的大括号里，和成员变量、构造函数平级
	**语法:bool 函数名(参数)const{return 规则;}        函数名:operator运算符(operator是关键字，后面跟要重载的运算符)    const:表示这个函数不会修改成员变量(只读)      参数:随便一个名字都可以,运算符右边的，在这里是find的目标值target
	eg.struct student{
	int id;
	string name;
	bool operator==(const student& other )const{return id==other.id;}  这里的id就是this->id，是容器里的一个
	bool operator!=(const student& other )const(return !(*this==other);)
	}
	*/
	vector<int> vec={ 10,20,30,40,50 };
	auto it = find(vec.begin(), vec.end(), 20);
	if (it != vec.end()) {
		cout << *it << endl;
		int pos = it - vec.begin();
		cout << pos << endl;
	}
	else {
		cout << "没找到20" << endl;
	}


	//vector其他常用操作
	/*
	1.在cpp中，数组/vector可以直接用=复制
	eg.vector<int> arr1={1,2};
		vector<int> arr2;
		arr2=arr1;
		for (int& h : arr2) {
			cout << h << " ";
		}
	2.swap交换两个vector，包括他们的size、capacity   a.swap(b);
	3.sort排序  O(n*log n)  STL的通用算法<algorithm>
	普通数据类型:sort(v.begin(),v.end());默认升序排序         sort(v.begin(),v.end(),greater<T>());降序排序-->其中greater<T>()是降序比较规则，greater<T>在sort里是降序，在priority_queue里是小根堆
	结构体/类:在全局中，结构体/类后面写排序规则函数bool cmp(const T& a,const T& b){return 关系表达式/比较规则；}；在主函数里，sort(v.begin(),v.end(),排序函数cmp);       这里的a是类型为T(也就是v这个容器对象对应的数据类型T)的这个容器里比较前面的一个，b是比较后面的一个
	--->排序规则函数 内部{可以用if else多条件排序}
	eg.bool cmp(const Student& a,const Student& b){
	if(a.score!=b.score) return a.score>b.score; 分数高的在前面
	else return a.id<b.id;  分数相同，学号小的在前面
	}
	*/
    
	return 0;
}



/*
1. vector是动态连续数组(底层内存连续，相当于可以自动扩容的数组)，扩容数据全部在堆heap上，但是vector对象(变量名v这个空壳子）在栈上，这个栈上的v内部就存3个指针，其中指针_start指向堆；属于STL容器。    头文件:  #include<vector>
2. 底层:一块连续堆内存；容量不够自动扩容(重新开辟更大内存，拷贝旧数据，释放旧内存)。
3. vector末尾插入语法:push_back(参数:已经构造完成的完整对象  T{val}) ; emplace_back(参数列表...)
   对于int这种简单类型，性能几乎没有差别。
   vector<int> a;
   a.push_back(10);
   a.emplace_back(10);
   emplace_back()的优势主要体现在 结构体、string、自定义类、对象拷贝开销大的时候。   !!!emplace_back()调用的是构造函数，会把参数交给结构体里的构造函数，但是编译器生成的默认构造函数是无参构造，没有接收参数的构造函数。当参数不唯一时，需要在结构体里写构造函数。
4. 迭代器失效:当发生扩容、erase、insert，旧迭代器会失效，不能继续使用
5. &:在范围for循环中，不加&-拷贝一份，改的是副本；只有加&，才会直接对容器里的元素进行操作
*/