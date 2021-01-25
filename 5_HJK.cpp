#include<iostream>
using namespace std;
class line;
class person
{
	friend line;      //����line��person����Ԫ
private:
	int number;       //���ݳ�Ա����¼ÿ���˵ı��
	person* next;     //ָ����һ���ڵ��ָ��
public:
	person()          //���캯������ʼ������
	{ 
		number = -1;
		next = NULL;
	}
	friend istream& operator >> (istream& in, person& per);//��������
	friend ostream& operator << (ostream& out, person& per);//�������
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
	int sum;      //��¼�����ڽڵ�ĸ���
public:           
	line()        //���캯������ʼ�����ڵĸ���  
	{
		sum = 0;
		first =tail = Current = NULL;
	}
	~line()       //�����������������
	{
		empty();
	}
	void create(int SUM);  //��������
	void sort();           //����Ա����
	void add(int number);  //����Ŷ���Ա
	void divide(line& odd, line& even);//����Ա����ŷֳ���ż����
	void output();         //��ӡ�ö���Ա
	int DeQueue();         //���Ӳ���
	void EnQueue(line &odd,line& even);//�����Ӻ�һ
	int isempty()          //�п�
	{
		if (first == NULL)return 1;
		else return 0;
	}
	void empty();          //�������
};

void line::create(int SUM)   
{
	person* per=new person;
	person* front = NULL;//ָ�����ڶ����ڵ�

	for (int i = 0; i < SUM; i++)
	{
		cin >> *per;     //�����Ŷ���Ա�ı��

		//�жϱ�Ÿ�ʽ�Ƿ����
		while (cin.fail() || per->number < 0 || per->number == 0)
		{
			cout << "�����ʽ����ȷ����ӵ�һ�γ���ĵط�����������������" << endl;
			cin.clear();
			char c = getchar();//��c�ӳ���ĵط���ȡһλ
			if (c == '.')      //c��С���㣬����������С��
			{
				if (first == tail)
				{
					delete first;
					first = tail = NULL;
				}
				else
				{ 
					delete tail;   //ɾ�����һ��
					tail = front;  //β�ڵ�ǰ��
					tail->next = NULL;
				}
				sum--;             //����ڵ���-1
				i--;               //ɾ�������һ���ڵ㣬��˼�����һ
			}
			cin.ignore(100, '\n');
			output();
			cin >> *per;
		}

		//��Ÿ�ʽ��ȷ���������
		front = tail;        //ԭ�ȵ����һ������˵����ڶ���
		add(per->number);    

		if (i == SUM - 1)    //Ϊ���ж����һ�������Ƿ�������С��
		{
			char c = getchar();
			if (c == '.')   //����������С��
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
				sum--;      //����ڵ���-1
				i--;        //ɾ�����һ���������Ҫ���¶���һ��������
				cin.ignore(100, '\n');
				cout << "�����ʽ����ȷ����ӵ�һ�γ���ĵط�����������������" << endl;
				output();
			}
		}
	}
}

void line::sort()
{
	person* front, * behind;
	int temp;
	for (int i = 0; i < sum - 1; i++) //ð�ݷ���С��������
	{
		front = first;
		behind = first->next;
		for (int j = 0; j < sum - i - 1; j++)
		{
			if (front->number > behind->number)//�������
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

void line::add(int number)//���������
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
	sum++;               //�����ڽڵ��������+1
}

void line::divide(line& odd, line& even)
{
	Current = first;
	for (int i = 0; i < sum; i++)
	{
		if (Current->number % 2 == 1)
		{
			odd.add(Current->number);//������Ž�������
		}
		else
		{
			even.add(Current->number);//ż����Ž�ż����
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
		return item; //���ڲ�Ϊ��ʱ��������Ԫ�ڵ����ݳ�Ա
	}
	return -1;       //Ϊ��ʱ����-1
}

void line::EnQueue(line& odd, line& even)
{
	while (!odd.isempty() || !even.isempty())
	{
		int i = 0;
		while (!odd.isempty() && i < 2)//�Ƚ�����������Ա
		{
			add(odd.DeQueue());
			i++;
			sum++;
		}
		if (!even.isempty())//�ٽ�һ��ż����Ա
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
	line allpeople; //�û�����������˵ı��
	line odd;       //������ŷ���һ��
	line even;      //ż����ŷ���һ��

	cout << "����������е���������";
	int SUM;
	cin >> SUM;
	while (SUM < 1)
	{
		cout << "������������1��������������������" ;
		cin.clear();
		cin.ignore(100, '\n');
		cin >> SUM;
	}

	cout << "����������ÿ���˵ı�ţ�����������";
	allpeople.create(SUM);      //���������˵����

	allpeople.sort();           //��������Ŵ�С��������
	allpeople.divide(odd, even);//��ż�ֿ�
	line queue;                 //���յı�Ŵ���˳��
	queue.EnQueue(odd, even);   //������˳�����

	cout << "ҵ������ɵ�˳��Ϊ��";
	for (int i = 0; i < SUM; i++)//����
	{
		cout << queue.DeQueue();
		if (i != SUM)cout << ' ';
	}
	return 0;
}