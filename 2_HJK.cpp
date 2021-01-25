#include<iostream>
using namespace std;

class aggregate;
class element     //�ڵ��ඨ��
{
	friend aggregate;
private:
	int ele;      //�����е�Ԫ��
	element* next;//ָ����һ���ڵ�
public:
	element()     //���캯��
	{
		ele = -1; //��ʼ��Ԫ�ص�ֵΪ-1
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
	int sum;         //ͳ�Ƶ�ǰ����Ԫ�ظ���
	element* first, * tail;
public:
	aggregate()      //���캯������ʼ�����ݳ�Ա
	{
		first = NULL;
		tail = NULL;
		sum=0;
	}
	~aggregate() { empty(); }//�����������������
	void create();           //����������ʼ����Ԫ��
	void output();           //����������Ԫ��
	void empty();            //��������ͷ��ڴ�
	void sort();             //���򣬷�ֹ��������ݲ��Ƿǽ���
	void intersection(aggregate& s1, aggregate& s2);//�󽻼�
};

void aggregate::create()
{
	cout << "������һ��ǽ������������У�-1��Ϊ���еĽ�����־��\n";
	element* newnode = new element;
	element* front=NULL;
	cin >> *newnode;
	while (cin.fail()||newnode->ele<-1 || (newnode->ele > -1 && newnode->ele < 0) ||newnode->ele==0) //�ж�����������Ƿ�Ϊ�Ϸ�
	{
		cout << "��������ݸ�ʽ���Ϸ���������һ����������" << endl;
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
			front = tail;   //frontָ��ÿ�ζ���ָ�����ڶ�������
			tail->next = newnode;
		}
		tail = newnode;
		sum += 1;          //����ڵ�����һ
		newnode = new element;
		cin >> *newnode;
		while (cin.fail() || newnode->ele < -1 || (newnode->ele > -1 && newnode->ele < 0) || newnode->ele == 0) //�ж�����������Ƿ�Ϊ�Ϸ�
		{
			cout << "��������ݸ�ʽ���Ϸ�����ӵ�һ�β��Ϸ��ĵط�����������������" << endl;
			cin.clear();
			char c = getchar();
			if (c == '.')        //���ݳ�����Ƿ��ǡ� .����ѡ����ɾ��������һ���ڵ�
			{
				if (tail == first)
				{
					delete first;
					first = tail = NULL;
				}
				else
				{
					delete tail;
					tail = front; //��ʱ�����ڶ�����ֵ��ɵ�����һ��
					tail->next = NULL;
				}
				sum -= 1;    //����ڵ��һ
			}
			cin.ignore(100, '\n');
			output();        //��ӡ�Ѿ�����ĺϷ������ݣ������û��ӳ���㴦��������
			cout << ' ';
			cin >> *newnode;
		}
	}
	if (tail != NULL)//��������Ƿǿ�������ܽ�tail->next=NULL,������Զ������⣬��Ϊ�սڵ㲻����nextԪ��һ˵
	{
		tail->next = NULL;
	}
	delete newnode;  //���-1��ռ�ռ�
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
			if (front->ele > behind->ele)//�������
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
	element* list1=s1.first, * list2=s2.first; //��������ָ��ֱ�ָ�������������Ԫ�ڵ�
	element* newnode;                          //�����洢��ͬ��Ԫ��
	while (list1 != NULL && list2 != NULL)     //һ����һ�����ϱ�����Ͼ�ֹͣ�󽻼��Ĺ���
	{
		//Ԫ����ͬ�����뵽����������
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

		//��ͬʱ����СԪ�ص�ָ������ƶ�
		else if (list1->ele < list2->ele)     
		{
			list1 = list1->next;
		}
		else
		{
			list2 = list2->next;
		}
	}

	//�ͷ�s1��s2���ڴ�
	s1.empty();
	s2.empty();

	if (first != NULL)
	{
		tail->next = NULL;
	}
}

int main()
{
	aggregate s1, s2, s3;       //����������������

	//���뼯��s1 ��s2
	s1.create();                
	s2.create();      

	//����s1��s2��Ԫ������
	s1.sort();
	s2.sort();

	//s3��s1��s2�Ľ���
	s3.intersection(s1, s2);
	cout << "�����еĽ���Ϊ��\n";
	s3.output(); //�������s3��Ԫ��
	return 0;
}