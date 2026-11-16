//int 范围 +-21亿          unsigned int 范围 0—42亿


//unique--->STL算法--->去重 #include <algorithm>  O(n) --->只适应于vector、string、deque(支持向前迭代器),list自带成员函数
/*
!!!!核心:unique只能看见相邻的重复元素，所以在使用unique前先要用sort排序，使重复的元素相邻；unique不会真正的删除掉内存里的元素，只是把不重复的元素挪到前面，返回新逻辑末尾的迭代器。

函数原型:1.默认用==判断相等 unique(first_it,last_it);   2.自定义判断规则(适用于结构体、类等自定义数据类型) unique(first_it,last_it,BinaryPredicate p);区间左闭右开
BinaryPredicate是二元谓词，本质是可以接收两个参数、返回bool类型的东西，告诉unique什么时候认为两个元素相等。 !!必须满足bool pred(const T& a,const T& b); 自定义比较规则的时候会用到，通常有三种写法，普通函数、重载比较运算符、lambda

底层原理:双指针
auto unique(vector<int>& v){
	int j=0; //j:保存不重复元素的位置
	for(int i=0;i<v.size();i++){
	if(j==0||v[i]!=v[j-1]){v[j]=v[i];j++;}
	}
	return v.begin()+j;//返回新末尾迭代器(第一个垃圾元素的位置)
}
 真正删除:sort+unique+erase    auto it=unique(v.begin(),v.end()); v.erase(it,v.end()); 区间左闭右开

 时间复杂度:O(n)    对于完整的一系列删除操作，时间复杂度由sort决定，O(n*logn)
 */


//自定义排序--->本质就是给sort传一个比较规则，lambda是最方便的写法      用sort的前提是，该容器支持随机访问迭代器（可以it+i、it++、it--） 只有vector string deque
/*
sort(first_it,last_it,comp);  comp（a,b)是一个可调用对象（lambda、普通函数、伪函数), !!comp(a,b)返回true代表a应该排在b前面。
comp必须满足严格弱序，不能写<=、>=，只能用<、>       当sort不传第三个参数时，默认使用operator< (升序)    comp本质上就是二元谓词，二元谓词是一类函数的统称，comp是在排序比较里二元谓词的别名

方法一 lambda    代码直接写在参数里面，一次性比较规则首选
lambda基础语法：[](const T& a，const T& b){ 比较规则 };
[]:捕获列表。绝大多数排序场景直接写[]，不需要捕获外部变量，只用a、b ；  [target]值捕获，拷贝target，lambda内部只读副本，不能修改实际值，用于比较规则需要外部变量的时候 ； [&target]引用捕获 ； [&]全部引用捕获 ； [=]全部值捕获
eg:struct student{
 int id;
 int score;
 };
 vector<student>stus;  需求：分数高的在前面，分数相同id小的在前面
 sort(stus.begin(),stus.end(),[](const student& a,const student& b){if(a.score!=b.score)return a.score>b.score;else if(a.score==b.score)return a.id<b.id;});

 方法二 全局cmp函数    适用于多处代码复用同一个比较规则，写在main外面
 eg:struct student{
 int id;
 int score;
 };
 bool cmp(const student& a,const student& b){
 if(a.score!=b.score)return a.score>b.score;
 else if(a.score==b.score)return a.id<b.id;
 }
 int main(){
 vector<student> stus;
 sort(stus.begin(),stus.end(),cmp);
 return 0;
 }

 方法三 重载结构体内部operator<  不用传第三个参数    如果要降序排序，sort的第三个参数写greater<T>(),重载operator>；或者在operator<里,用>比较
 sort会不断随机取出容器里的两个元素a、b，判断a该不该在b前面；可以只写一个参数，参数代表b，另一个就是当前对象this,代表a
 eg:struct student{
 int id;
 int score;
 bool operator<(const student& b){
     if(score!=b.score)return score>b.score;    如果返回true，代表a<b，a的score比b大，a在前面；返回false，b在前面
	 else if(score==b.score)return id<b.id;
     }
 };
 int main(){
 vector<student> stus;
 sort(stus.begin(),stus.end());
 return 0;
 }
*/


//pair--->C++标准库给的模板结构体，可以把两个不同(或相同)类型的数据打包合并成一个变量   #include <utility>
/*
语法:pair<类型1，类型2> 变量名；   .first第一个成员，.second第二个成员
赋值：!！pair对象（实体变量），访问成员用.点运算符；只有pair的指针才用->     eg.pair<int,string> p; p.first=10;p.second="hello";
初始化：1.大括号初始化pair<int,int> b={10,20};  2.直接auto接收make_pair(值1,值2) auto c=make_pair(10,20);make_pair()自动推导你传入两个值的类型，返回一个pair对象    3.pair<T1,T2> d{ , };
pair的比较运算符：pair自带比较规则，优先比.first，如果.first相等才去比较.second
*/


//reverse--->全局算法，#include <algorithm>--->在容器原地修改，只适用于vector、string、deque(支持双向迭代器，可以++it、--it)
/*
语法:reverse(it_begin(),it_end());
时间复杂度:O(n)，和for循环交换一半的效率差不多，更方便
*/