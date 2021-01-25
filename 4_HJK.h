#pragma once
#include<iostream>
#include<algorithm>
using namespace std;

template<class T>      //模板类Stack的声明
class Stack;

template<class T>
class stacknode        //栈的模板节点类
{
	friend  Stack<T>;  //声明为友元模板类
private:
	T data;            //栈内元素的数据成员
	T sign;            //区分单双目
	stacknode<T>* next;//指向下一个节点的指针
public:
	stacknode() { next = NULL; }
};

template<class T>
class Stack            //模板类栈Stack
{
private:
	stacknode<T>* top;             //栈顶指针
public:
	Stack() { top = NULL; }        //构造函数，将top初始化为NULL
	~Stack()                       //析构函数，调用empty（）函数来清空栈
	{
		empty();
	}
	void push(const T& item);      //将item的数值添加到栈的新节点中
	T pop();                       //数据或运算符出栈
	bool is_empty();               //判断是否为空
	void empty();                  //清空链表
	T get_top() {return top->data;}//读取栈顶的数据
};

class calculate            //负责算数表达式的处理
{
private:
	Stack<double> Operand; //操作数栈
	Stack<char> Operator;  //操作符栈
	int tag ;              //标记前一次是否是操作数进栈，辨别运算符是单目还是双目
	bool get2operand(double& left, double& right);//从栈中取两个操作数
	int PRI1(char ch);     //返回运算符栈外优先级
	int PRI2(char ch);     //返回运算符栈内优先级
	bool do_operator(char op);//对当前运算符进行运算,返回运算的成功或失败信号
public:
	calculate() { clear(); } //构造函数，调用clear（）函数，将两个栈类数据成员清空，tag置为0
	~calculate() { clear(); }//析构函数，运算结束时栈的释放空间
	void clear() { Operand.empty(); Operator.empty(); tag = 0; }//清空私有成员栈
	void run();            //完成整个算术表达式的运算
};
