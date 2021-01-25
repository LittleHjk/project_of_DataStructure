#pragma once
#include<iostream>
using namespace std;

#define disconnection 20000000  //两端点之间不可能达到的距离，表示没有边

/***************************相关结构体的定义*****************************/
template<class T>
struct edge                     //最小堆中的“边”模板类定义
{
	string node1, node2;        //“边”的两个端点
	T key;                      //“边”的长度（权值）
	edge()
	{
		key = disconnection;    //边长初始化成“无穷大”
	}
	friend istream& operator >>(istream& in, edge<T>& the_edge)//重载输入，输入“边”的三个数据
	{
		in >> the_edge.node1 >> the_edge.node2 >> the_edge.key;
		return in;
	}
	bool operator <(edge<T>& another_edge) //重载<运算符,比较两个边的大小
	{
		return key < another_edge.key;
	}
	bool operator >(edge<T>& another_edge) //重载>运算符,比较两个边的大小
	{
		return key > another_edge.key;
	}
};

template<class T>
struct edge_of_adj             //邻接表的边界点定义
{
	int index;                 //index是顶点的位置
	T key;                     //边的长度（权值）
	edge_of_adj<T>* next;      //下一个边界点的指针
	edge_of_adj()
	{
		index = -1;            //顶点下标初始化为-1
		key = disconnection;   //边长初始化成“无穷大”
		next = NULL;
	}
};

template<class T>
struct vertex                     //邻接表的头顶点
{
	string name;                  //顶点的名字
	edge_of_adj<T>* first, * tail;//该顶点的邻接表的头指针和尾指针
	vertex()                      //初始化顶点和邻接表的数据
	{
		name = "\0";
		first = tail = NULL;
	}
};

/******************************graph的类定义*******************************/
template<class T>
class graph                    //最小生成图的类定义
{
private:
	vertex<T>* node_table;     //包含所有顶点邻接表的数组，用来存储图的信息
	int vertex_number;         //图的顶点数
	int edge_number;           //图的边数
public:
	graph()                                      //构造函数，初始化数据
	{
		vertex_number = 0;
		edge_number = 0;
		node_table = NULL;
	}

	void create(int N)                           //开辟顶点邻接表数组
	{
		vertex_number = N;
		node_table = new vertex<T>[N];
	}
	void insert_vertex(string name, int index)   //在index位置插入顶点
	{
		node_table[index].name = name;
	}
	void insert_edge(edge<T>* new_edge);          //在顶点之间插入新边
	int find(string name);                       //找到名为name的顶点，返回下标
	int get_vertex_number() { return vertex_number; }//得到顶点数目
	int get_edge_number() { return edge_number; }    //得到边的数目
	int get_first_neighbor(int index);               //找到index位置的点的第一个邻接点
	int get_next_neighbor(int index1, int index2);   //找到index1处，index2后的邻接点
	T get_key(int index1, int index2);           //返回两点间的距离
	string get_name(int index)                   //返回位置在index的顶点的名字 
	{
		return node_table[index].name;
	}
	void Prim(edge<T> min_span_tree[], string start_vertex);           //Prim算法生成最小生成树
};