#include<iostream>
using namespace std;

class aggregate;
class element     //节点类定义
{
	friend aggregate;
private:
	int ele;      //序列中的元素
	element* next;//指向下一个节点
public:
	element()     //构造函数
	{
		ele = -1; //初始化元素的值为-1
		next = NULL;
	}
	friend istream& operator >>(istream& in, element& s);
	friend ostream& operator <<(ostream& out, element& s);
};

istream& operator >>(istream& in, element& s)
{
	in >> s.ele;
	return in;
}

ostream& operator <<(ostream& out, element& s)
{
	out << s.ele;
	return out;
}

class aggregate
{
private:
	int sum;         //统计当前序列元素个数
	element* first, * tail;
public:
	aggregate()      //构造函数，初始化数据成员
	{
		first = NULL;
		tail = NULL;
		sum=0;
	}
	~aggregate() { empty(); }//析构函数，清空链表
	void create();           //创建链表、开始输入元素
	void output();           //输出链表里的元素
	void empty();            //清空链表，释放内存
	void sort();             //排序，防止输入的数据不是非降序
	void intersection(aggregate& s1, aggregate& s2);//求交集
};

void aggregate::create()
{
	cout << "请输入一组非降序正整数序列，-1作为序列的结束标志：\n";
	element* newnode = new element;
	element* front=NULL;
	cin >> *newnode;
	while (cin.fail()||newnode->ele<-1 || (newnode->ele > -1 && newnode->ele < 0) ||newnode->ele==0) //判断输入的数字是否为合法
	{
		cout << "输入的数据格式不合法，请输入一组正整数！" << endl;
		cin.clear();
		cin.ignore(100, '\n');
		cin >> *newnode;
	}
	while (newnode->ele != -1)
	{
		if (first == NULL)
		{
			first = newnode;
		}
		else
		{
			front = tail;   //front指针每次都是指向倒数第二个数据
			tail->next = newnode;
		}
		tail = newnode;
		sum += 1;          //链表节点数加一
		newnode = new element;
		cin >> *newnode;
		while (cin.fail() || newnode->ele < -1 || (newnode->ele > -1 && newnode->ele < 0) || newnode->ele == 0) //判断输入的数字是否为合法
		{
			cout << "输入的数据格式不合法，请从第一次不合法的地方继续输入正整数！" << endl;
			cin.clear();
			char c = getchar();
			if (c == '.')        //根据出错点是否是‘ .’来选择性删除倒数第一个节点
			{
				if (tail == first)
				{
					delete first;
					first = tail = NULL;
				}
				else
				{
					delete tail;
					tail = front; //此时倒数第二个数值变成倒数第一个
					tail->next = NULL;
				}
				sum -= 1;    //链表节点减一
			}
			cin.ignore(100, '\n');
			output();        //打印已经输入的合法的数据，方便用户从出错点处接着输入
			cout << ' ';
			cin >> *newnode;
		}
	}
	if (tail != NULL)//这里必须是非空链表才能将tail->next=NULL,否则会自动出问题，因为空节点不存在next元素一说
	{
		tail->next = NULL;
	}
	delete newnode;  //清除-1所占空间
}

void aggregate::output()
{
	if (first == NULL)
	{
		cout << "NULL";
	}
	else
	{
		element* current = first;
		while (current != tail)
		{
			cout << *current << ' ';
			current = current->next;
		}
		cout << *current;
	}
}

void aggregate::empty()
{
	element* p;
	while (first != NULL)
	{
		p = first;
		first = first->next;
		delete p;
	}
}

void aggregate::sort()
{
	element* front, * behind;
	int temp;
	for (int i = 0; i < sum - 1; i++)
	{
		front = first;
		behind = first->next;
		for (int j = 0; j < sum - i - 1; j++)
		{
			if (front->ele > behind->ele)//交换序号
			{
				temp = front->ele;
				front->ele = behind->ele;
				behind->ele = temp;
			}
			front = behind;
			behind = behind->next;
		}
	}
}

void aggregate::intersection(aggregate& s1, aggregate& s2)
{
	element* list1=s1.first, * list2=s2.first; //定义两个指针分别指向两个链表的首元节点
	element* newnode;                          //用来存储相同的元素
	while (list1 != NULL && list2 != NULL)     //一旦有一个集合遍历完毕就停止求交集的过程
	{
		//元素相同，加入到交集集合中
		if (list1->ele == list2->ele)         
		{
			newnode = new element;
			newnode->ele = list1->ele;
			if (first == NULL)                
			{
				first = newnode;
			}
			else
			{
				tail->next = newnode;
			}
			tail = newnode;
			list1 = list1->next;
			list2 = list2->next;
		}

		//不同时，较小元素的指针向后移动
		else if (list1->ele < list2->ele)     
		{
			list1 = list1->next;
		}
		else
		{
			list2 = list2->next;
		}
	}

	//释放s1和s2的内存
	s1.empty();
	s2.empty();

	if (first != NULL)
	{
		tail->next = NULL;
	}
}

int main()
{
	aggregate s1, s2, s3;       //创建三个集合链表

	//输入集合s1 、s2
	s1.create();                
	s2.create();      

	//集合s1、s2内元素排序
	s1.sort();
	s2.sort();

	//s3是s1、s2的交集
	s3.intersection(s1, s2);
	cout << "两序列的交集为：\n";
	s3.output(); //输出集合s3的元素
	return 0;
}