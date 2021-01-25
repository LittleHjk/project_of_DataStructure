#pragma once
#include<iostream>
using namespace std;

#define disconnection 20000000  //���˵�֮�䲻���ܴﵽ�ľ��룬��ʾû�б�

/***************************��ؽṹ��Ķ���*****************************/
template<class T>
struct edge                     //��С���еġ��ߡ�ģ���ඨ��
{
	string node1, node2;        //���ߡ��������˵�
	T key;                      //���ߡ��ĳ��ȣ�Ȩֵ��
	edge()
	{
		key = disconnection;    //�߳���ʼ���ɡ������
	}
	friend istream& operator >>(istream& in, edge<T>& the_edge)//�������룬���롰�ߡ�����������
	{
		in >> the_edge.node1 >> the_edge.node2 >> the_edge.key;
		return in;
	}
	bool operator <(edge<T>& another_edge) //����<�����,�Ƚ������ߵĴ�С
	{
		return key < another_edge.key;
	}
	bool operator >(edge<T>& another_edge) //����>�����,�Ƚ������ߵĴ�С
	{
		return key > another_edge.key;
	}
};

template<class T>
struct edge_of_adj             //�ڽӱ�ı߽�㶨��
{
	int index;                 //index�Ƕ����λ��
	T key;                     //�ߵĳ��ȣ�Ȩֵ��
	edge_of_adj<T>* next;      //��һ���߽���ָ��
	edge_of_adj()
	{
		index = -1;            //�����±��ʼ��Ϊ-1
		key = disconnection;   //�߳���ʼ���ɡ������
		next = NULL;
	}
};

template<class T>
struct vertex                     //�ڽӱ��ͷ����
{
	string name;                  //���������
	edge_of_adj<T>* first, * tail;//�ö�����ڽӱ��ͷָ���βָ��
	vertex()                      //��ʼ��������ڽӱ������
	{
		name = "\0";
		first = tail = NULL;
	}
};

/******************************graph���ඨ��*******************************/
template<class T>
class graph                    //��С����ͼ���ඨ��
{
private:
	vertex<T>* node_table;     //�������ж����ڽӱ�����飬�����洢ͼ����Ϣ
	int vertex_number;         //ͼ�Ķ�����
	int edge_number;           //ͼ�ı���
public:
	graph()                                      //���캯������ʼ������
	{
		vertex_number = 0;
		edge_number = 0;
		node_table = NULL;
	}

	void create(int N)                           //���ٶ����ڽӱ�����
	{
		vertex_number = N;
		node_table = new vertex<T>[N];
	}
	void insert_vertex(string name, int index)   //��indexλ�ò��붥��
	{
		node_table[index].name = name;
	}
	void insert_edge(edge<T>* new_edge);          //�ڶ���֮������±�
	int find(string name);                       //�ҵ���Ϊname�Ķ��㣬�����±�
	int get_vertex_number() { return vertex_number; }//�õ�������Ŀ
	int get_edge_number() { return edge_number; }    //�õ��ߵ���Ŀ
	int get_first_neighbor(int index);               //�ҵ�indexλ�õĵ�ĵ�һ���ڽӵ�
	int get_next_neighbor(int index1, int index2);   //�ҵ�index1����index2����ڽӵ�
	T get_key(int index1, int index2);           //���������ľ���
	string get_name(int index)                   //����λ����index�Ķ�������� 
	{
		return node_table[index].name;
	}
	void Prim(edge<T> min_span_tree[], string start_vertex);           //Prim�㷨������С������
};