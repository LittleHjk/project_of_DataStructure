//栈类、节点类、地图类的声明

#pragma once
#include<iostream>
using namespace std;


class Stack;        //栈类
class Maze;         //迷宫类
class stacknode     //定义栈的节点类
{

	friend Stack;   //声明栈是其友元
	friend Maze;    //声明迷宫类（Maze）是其友元
private:
	int x, y;       //x是行，y是列
	stacknode* next;
public:
	stacknode()     //构造函数，初始化位置的行列都是零
	{
		x = y = 0;
		next = NULL;
	}
};
 

class Stack     //定义栈，用来存储迷宫的经历路线
{
private:
	stacknode* top;           //栈顶指针
public:
	Stack() { top = NULL; }   //构造函数，初始栈为空
	void push(stacknode* p);  //数据入栈
	stacknode* pop();         //栈顶出栈
	int is_empty();           //判断栈是否为空
};

class Maze
{
private:
	char** maze;                 //动态迷宫
	bool** visit;                //访问次数
	int row, col;                //row行数和col列数
	stacknode* start, * exit;    //起点和终点的指针
	Stack path;                  //存走过的路径
	void set_maze(int option);   //设置迷宫
public:
	Maze(int option) { set_maze(option); }//构造迷宫
	void print_maze();                    //打印迷宫
	int seek();                           //寻找路径,成功返回1，失败返回0
	void print_path();                    //打印路线
};




