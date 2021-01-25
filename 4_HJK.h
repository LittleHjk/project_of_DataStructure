#pragma once
#include<iostream>
#include<algorithm>
using namespace std;

template<class T>      //ģ����Stack������
class Stack;

template<class T>
class stacknode        //ջ��ģ��ڵ���
{
	friend  Stack<T>;  //����Ϊ��Ԫģ����
private:
	T data;            //ջ��Ԫ�ص����ݳ�Ա
	T sign;            //���ֵ�˫Ŀ
	stacknode<T>* next;//ָ����һ���ڵ��ָ��
public:
	stacknode() { next = NULL; }
};

template<class T>
class Stack            //ģ����ջStack
{
private:
	stacknode<T>* top;             //ջ��ָ��
public:
	Stack() { top = NULL; }        //���캯������top��ʼ��ΪNULL
	~Stack()                       //��������������empty�������������ջ
	{
		empty();
	}
	void push(const T& item);      //��item����ֵ��ӵ�ջ���½ڵ���
	T pop();                       //���ݻ��������ջ
	bool is_empty();               //�ж��Ƿ�Ϊ��
	void empty();                  //�������
	T get_top() {return top->data;}//��ȡջ��������
};

class calculate            //�����������ʽ�Ĵ���
{
private:
	Stack<double> Operand; //������ջ
	Stack<char> Operator;  //������ջ
	int tag ;              //���ǰһ���Ƿ��ǲ�������ջ�����������ǵ�Ŀ����˫Ŀ
	bool get2operand(double& left, double& right);//��ջ��ȡ����������
	int PRI1(char ch);     //���������ջ�����ȼ�
	int PRI2(char ch);     //���������ջ�����ȼ�
	bool do_operator(char op);//�Ե�ǰ�������������,��������ĳɹ���ʧ���ź�
public:
	calculate() { clear(); } //���캯��������clear����������������ջ�����ݳ�Ա��գ�tag��Ϊ0
	~calculate() { clear(); }//�����������������ʱջ���ͷſռ�
	void clear() { Operand.empty(); Operator.empty(); tag = 0; }//���˽�г�Աջ
	void run();            //��������������ʽ������
};
