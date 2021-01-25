#include<iostream>
#include<string>
#include<iomanip>

using namespace std;
class information_system;
class Student
{
	friend class information_system;//信息系统为其友元类
private:
	int number;
	int age;
	string name;
	string sex;
	string category; //报考类别
	Student* next;
public:
	Student() { next = NULL; }   //next指针置为NULL
	friend istream& operator >> (istream& in, Student& stu);//重载输入
	friend ostream& operator << (ostream& out, Student& stu);//重载输出
};

istream& operator >> (istream& in, Student& stu)
{
	in >> stu.number >> stu.name >> stu.sex >> stu.age >> stu.category;
	return in;
}

ostream& operator << (ostream& out, Student& stu)
{
	out << setiosflags(ios::left)
		<< setw(8) << stu.number
		<< setw(8) << stu.name
		<< setw(8) << stu.sex
		<< setw(8) << stu.age
		<< setw(8) << stu.category
		<< endl;
	return out;
}

class information_system
{
private:
	Student* first, * tail;
public:
	information_system() { first = tail = NULL; }
	~information_system() { empty(); }//程序结束清空链表
	void create();//建立链表
	void output();//打印链表（统计）
	void find();  //查找
	void insert();//插入
	void alter(); //修改
	void remove();//删除
	void empty() //清空链表
	{
		Student* p ;
		while (first != NULL)
		{
			p = first;
			first = first->next;
			delete p;
		}
	}
};

void information_system::create()
{
	cout << "首先请建立考生信息系统！" << endl;
	cout << "请输入考生人数：";

	//输入考生人数
	int amount;     
	cin >> amount;

	//检验输入的人数是否合理
	while (amount < 1)   
	{
		cout << "请输入一个正整数人数：";
		cin >> amount;
	}

	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别!" << endl;
	Student* newnode;
	bool SEX;           //判定新学生信息输入是否合理的标志

	for (int i = 0; i < amount; i++)
	{
		newnode = new Student;
		cin >> *newnode;

		//判断学号、年龄等信息输入类型是否正确
		while (cin.fail()) 
		{
			cout << "输入不合法，请重新输入该学生信息！" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cin >> *newnode;
		}

		//判断性别是否合理
		do
		{
			SEX = true;    //SEX初始化认为是合理的
			if (newnode->sex != "男" && newnode->sex != "女")
			{
				cout << "学生的性别有误，请重新输入该学生信息！" << endl;
				cin >> *newnode;
				SEX = false;
			}
		} while (SEX == false);

		if (first == NULL)
		{
			first = newnode;
		}
		else
		{
			tail->next = newnode;
		}
		tail = newnode;
	}
	cout << endl;
}

void information_system::output()
{
	if (first == NULL)               //信息系统为空时的输出操作
	{
		cout << "当前考生信息系统为空！" << endl;
		return;
	}

	cout << setiosflags(ios::left)  //信息系统不空时的输出操作
		<< setw(8) << "考号"
		<< setw(8) << "姓名"
		<< setw(8) << "年龄"
		<< setw(8) << "报考类别"
		<< endl;

	Student* current = first; 
	while (current != NULL)        //逐个输出
	{
		cout << *current;
		current = current->next;
	}
}

void information_system::insert()
{
	cout << "请输入你要插入的考生的位置：";
	int position;
	cin >> position;
	while (position < 1)             //若插入的位置不合法，则重新插入
	{
		cout << "插入位置不合法！" << endl;
		cout<< "请重新输入你要插入的考生的位置：";
		cin >> position;
	}

	Student* insert_student = new Student;
	while (1)                        //判断插入的学生考号是否已存在，存在则重新输入
	{
		cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别!" << endl;
		cin >> *insert_student;
		Student* p = first;
		for (; p != NULL; p = p->next)//遍历链表，查找是否考号已经存在
		{
			if (p->number == insert_student->number)
			{
				cout << "该考号的学生已存在，无需再插入。"<<endl;
				break;
			}
		}
		if (p == NULL)break;
	}
	cout << endl;

	Student* front = NULL, * behind = first;  //插入位置的直接前驱、直接后继
	if (first == NULL)             //插入时链表为空的操作
	{
		first = tail = insert_student;
		first->next = tail->next = NULL;
		output();
		cout << endl;
		cout << "当前信息系统为空，故将该学生信息放至第一位" << endl;
	}
	else if (position == 1)         //插入时链表不空的操作（插入位置是第一个）
	{
		insert_student->next = first;
		first = insert_student;
		output();
	}
	else                            //插入时链表不空的操作，且插入其他位置（非第一位）
	{
		int i;
		for (i = 1; i < position && behind != NULL; i++)//考虑了position超出当前考生总数的情况
		{
			front = behind;
			behind = behind->next;
		}
		front->next = insert_student;
		insert_student->next = behind;
		output();
		if (i != position)
		{
			tail = insert_student;     //将尾指针指向新插入的学生
			cout << "插入位置已经超过最后一个学生，故将该学生信息放至最后一位"<<endl;
		}
	}
}

void information_system::remove()
{
	if (first == NULL)    //当系统为空，没有可删除内容时的操作
	{
		cout << "当前考生信息系统为空，没有可删除内容！" << endl;
		return;
	}
	cout << "请输入要删除的考生的考号:";
	int the_number;
	cin >> the_number;

	Student* front = NULL, * current = first;  //front用于标记要删除结点的前驱，current指向要删除节点
	while (current != NULL && current->number != the_number)
	{
		front = current;
		current = current->next;
	}

	if (current == first)    //要删除的学生是第一个
	{
		cout << "你删除的考生信息是：";
		cout << *first;
		first = first->next;
		delete current;
		cout << endl; 
		output();            //打印考生系统
	}
	else if (current != NULL)//找到了，但不是第一个
	{
		cout << "你删除的考生信息是：";
		cout << *current;
		front->next = current->next;
		delete current;
		cout << endl;
		output();      
	}
	else               //没有找到对应的考号学生       
	{
		cout << "未找到要删除的考生信息!" << endl;
		remove();      //再次调用删除函数
	}
}

void information_system::find()
{
	if (first == NULL)                   //链表为空，输出提示，结束查找
	{
		cout << "当前系统为空，没有可查询信息。" << endl;
		return;
	}
	 
	cout << "请输入要查找的考生考号：";    //链表非空，往下进行
	int the_number;                      //要查找的考号
	cin >> the_number;
	Student* current = first;            //current最终指向查找的结点
	while (current != NULL && current->number != the_number)
	{
		current = current->next;
	}

	if (current == NULL)                //查找的考号不存在时
	{
		cout << "该考号对应的学生信息不存在" << endl;
		find();
	}
	else
	{
		cout << setiosflags(ios::left)
			<< setw(8) << "考号"
			<< setw(8) << "姓名"
			<< setw(8) << "年龄"
			<< setw(8) << "报考类别"
			<< endl;
		cout << *current << endl;
	}
}

void information_system::alter()
{
	if (first == NULL)                      //当系统为空，没有可修改内容时的操作
	{
		cout << "当前考生信息系统为空，没有可修改内容！" << endl;
		return;
	}

	cout << "请输入要修改的考生信息的考号："; //系统不为空时继续
	int the_number;
	cin >> the_number;

	Student* old_information = first;
	while (old_information != NULL && old_information->number != the_number)//查找该考号的考生
	{
		old_information = old_information->next;
	}
	if (old_information != NULL)          //查找成功
	{
		cout << "请依次输入新的学生信息：";
		cin >> *old_information;
		output();
	}
	else                                  //查找失败
	{
		cout << "该学号对应的学生信息不存在！" << endl;
		alter();
	}
}

int main()
{
	information_system examinees;
	examinees.create();                 //创建考生系统
	examinees.output();                 //向用户打印一遍考生系统
	cout << "请输入你想要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）"
		<< endl
		<< endl;

	int order = 1;                      //开始执行操作，初始化为1
	while (order != 0)                  //输入0表示结束程序
	{
		cout << "请选择您要进行的操作：";
		cin >> order;
		while (order > 5 || order < 0)
		{
			cout << "该指令不存在，请重新输入正确的指令！" << endl;
			cin >> order;
		}
		switch (order)
		{
		case 0:continue; break;
		case 1:examinees.insert(); break; //插入
		case 2:examinees.remove(); break; //删除
		case 3:examinees.find(); break;   //查找
		case 4:examinees.alter(); break;  //修改
		case 5:examinees.output(); break; //打印考生列表
		}
	}
	return 0;
}