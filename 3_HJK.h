//ջ�ࡢ�ڵ��ࡢ��ͼ�������

#pragma once
#include<iostream>
using namespace std;


class Stack;        //ջ��
class Maze;         //�Թ���
class stacknode     //����ջ�Ľڵ���
{

	friend Stack;   //����ջ������Ԫ
	friend Maze;    //�����Թ��ࣨMaze��������Ԫ
private:
	int x, y;       //x���У�y����
	stacknode* next;
public:
	stacknode()     //���캯������ʼ��λ�õ����ж�����
	{
		x = y = 0;
		next = NULL;
	}
};
 

class Stack     //����ջ�������洢�Թ��ľ���·��
{
private:
	stacknode* top;           //ջ��ָ��
public:
	Stack() { top = NULL; }   //���캯������ʼջΪ��
	void push(stacknode* p);  //������ջ
	stacknode* pop();         //ջ����ջ
	int is_empty();           //�ж�ջ�Ƿ�Ϊ��
};

class Maze
{
private:
	char** maze;                 //��̬�Թ�
	bool** visit;                //���ʴ���
	int row, col;                //row������col����
	stacknode* start, * exit;    //�����յ��ָ��
	Stack path;                  //���߹���·��
	void set_maze(int option);   //�����Թ�
public:
	Maze(int option) { set_maze(option); }//�����Թ�
	void print_maze();                    //��ӡ�Թ�
	int seek();                           //Ѱ��·��,�ɹ�����1��ʧ�ܷ���0
	void print_path();                    //��ӡ·��
};




