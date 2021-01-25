#include<iostream>
using namespace std;
class line;
class person
{
	friend line;      //声明line是person的友元
private:
	int number;       //数据成员，记录每个人的编号
	person* next;     //指向下一个节点的指针
public:
	person()          //构造函数，初始化变量
	{ 
		number = -1;
		next = NULL;
	}
	friend istream& operator >> (istream& in, person& per);//重载输入
	friend ostream& operator << (ostream& out, person& per);//重载输出
};

istream& operator >> (istream& in, person& per)
{
	in >> per.number;
	return in;
}

ostream& operator << (ostream& out, person& per)
{
	out << per.number;
	return out;
}

class line
{
private:
	person* first, * tail, * Current;
	int sum;      //记录链表内节点的个数
public:           
	line()        //构造函数，初始链表内的个数  
	{
		sum = 0;
		first =tail = Current = NULL;
	}
	~line()       //析构函数，清空链表
	{
		empty();
	}
	void create(int SUM);  //创建链表
	void sort();           //给人员排序
	void add(int number);  //添加排队人员
	void divide(line& odd, line& even);//将人员按序号分成奇偶两队
	void output();         //打印该队人员
	int DeQueue();         //出队操作
	void EnQueue(line &odd,line& even);//把两队合一
	int isempty()          //判空
	{
		if (first == NULL)return 1;
		else return 0;
	}
	void empty();          //清空链表
};

void line::create(int SUM)   
{
	person* per=new person;
	person* front = NULL;//指向倒数第二个节点

	for (int i = 0; i < SUM; i++)
	{
		cin >> *per;     //输入排队人员的编号

		//判断编号格式是否合理
		while (cin.fail() || per->number < 0 || per->number == 0)
		{
			cout << "输入格式不正确，请从第一次出错的地方继续输入正整数！" << endl;
			cin.clear();
			char c = getchar();//用c从出错的地方读取一位
			if (c == '.')      //c是小数点，代表输入了小数
			{
				if (first == tail)
				{
					delete first;
					first = tail = NULL;
				}
				else
				{ 
					delete tail;   //删除最后一个
					tail = front;  //尾节点前移
					tail->next = NULL;
				}
				sum--;             //链表节点数-1
				i--;               //删除了最后一个节点，因此计数减一
			}
			cin.ignore(100, '\n');
			output();
			cin >> *per;
		}

		//编号格式正确，进入队列
		front = tail;        //原先的最后一个变成了倒数第二个
		add(per->number);    

		if (i == SUM - 1)    //为了判断最后一个数据是否输入了小数
		{
			char c = getchar();
			if (c == '.')   //代表输入了小数
			{
				if (first == tail)
				{
					delete first;
					first = tail = NULL;
				}
				else
				{
					delete tail;
					tail = front;
				}
				sum--;      //链表节点数-1
				i--;        //删除最后一个，因此需要重新多输一个正整数
				cin.ignore(100, '\n');
				cout << "输入格式不正确，请从第一次出错的地方继续输入正整数！" << endl;
				output();
			}
		}
	}
}

void line::sort()
{
	person* front, * behind;
	int temp;
	for (int i = 0; i < sum - 1; i++) //冒泡法从小到大排序
	{
		front = first;
		behind = first->next;
		for (int j = 0; j < sum - i - 1; j++)
		{
			if (front->number > behind->number)//交换序号
			{
				temp = front->number;
				front->number = behind->number;
				behind->number = temp;
			}
			front = behind;
			behind = behind->next;
		}
	}
}

void line::add(int number)//增添新序号
{
	person* newnode = new person;
	newnode->number = number;
	if (first == NULL)
	{
		first = newnode;
	}
	else
	{
		tail->next = newnode;
	}
	tail = newnode;
	sum++;               //链表内节点个数计数+1
}

void line::divide(line& odd, line& even)
{
	Current = first;
	for (int i = 0; i < sum; i++)
	{
		if (Current->number % 2 == 1)
		{
			odd.add(Current->number);//奇数序号进奇数队
		}
		else
		{
			even.add(Current->number);//偶数序号进偶数队
		}
		Current = Current->next;
	}
}

void line::output()
{
	person* p = first;
	while (p != NULL)
	{
		cout << p->number << ' ';
		p = p->next;
	}
}

int line::DeQueue()
{
	if (first != NULL)
	{
		person*p=first;
		int item = p->number;
		first = first->next;
		delete p;
		sum--;
		return item; //队内不为空时，返回首元节点数据成员
	}
	return -1;       //为空时返回-1
}

void line::EnQueue(line& odd, line& even)
{
	while (!odd.isempty() || !even.isempty())
	{
		int i = 0;
		while (!odd.isempty() && i < 2)//先进两个奇数人员
		{
			add(odd.DeQueue());
			i++;
			sum++;
		}
		if (!even.isempty())//再进一个偶数人员
		{
			add(even.DeQueue());
			sum++;
		}
	}
}

void line::empty()
{
	person* p ;
	if (first != NULL)
	{
		p = first;
		first = first->next;
		delete p;
	}
}

int main()
{
	line allpeople; //用户输入的所有人的编号
	line odd;       //奇数编号放入一组
	line even;      //偶数编号放入一组

	cout << "请先输入队列的总人数：";
	int SUM;
	cin >> SUM;
	while (SUM < 1)
	{
		cout << "总人数至少是1，请重新输入总人数：" ;
		cin.clear();
		cin.ignore(100, '\n');
		cin >> SUM;
	}

	cout << "再依次输入每个人的编号（正整数）：";
	allpeople.create(SUM);      //输入所有人的序号

	allpeople.sort();           //给所有序号从小到大排序
	allpeople.divide(odd, even);//奇偶分开
	line queue;                 //最终的编号处理顺序
	queue.EnQueue(odd, even);   //按出队顺序进队

	cout << "业务处理完成的顺序为：";
	for (int i = 0; i < SUM; i++)//出队
	{
		cout << queue.DeQueue();
		if (i != SUM)cout << ' ';
	}
	return 0;
}