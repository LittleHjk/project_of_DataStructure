#include<iostream>
#include<string>
#include<iomanip>

using namespace std;
class information_system;
class Student
{
	friend class information_system;//��ϢϵͳΪ����Ԫ��
private:
	int number;
	int age;
	string name;
	string sex;
	string category; //�������
	Student* next;
public:
	Student() { next = NULL; }   //nextָ����ΪNULL
	friend istream& operator >> (istream& in, Student& stu);//��������
	friend ostream& operator << (ostream& out, Student& stu);//�������
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
	~information_system() { empty(); }//��������������
	void create();//��������
	void output();//��ӡ����ͳ�ƣ�
	void find();  //����
	void insert();//����
	void alter(); //�޸�
	void remove();//ɾ��
	void empty() //�������
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
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	cout << "�����뿼��������";

	//���뿼������
	int amount;     
	cin >> amount;

	//��������������Ƿ����
	while (amount < 1)   
	{
		cout << "������һ��������������";
		cin >> amount;
	}

	cout << "���������뿼���Ŀ��ţ��������Ա����估�������!" << endl;
	Student* newnode;
	bool SEX;           //�ж���ѧ����Ϣ�����Ƿ����ı�־

	for (int i = 0; i < amount; i++)
	{
		newnode = new Student;
		cin >> *newnode;

		//�ж�ѧ�š��������Ϣ���������Ƿ���ȷ
		while (cin.fail()) 
		{
			cout << "���벻�Ϸ��������������ѧ����Ϣ��" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cin >> *newnode;
		}

		//�ж��Ա��Ƿ����
		do
		{
			SEX = true;    //SEX��ʼ����Ϊ�Ǻ����
			if (newnode->sex != "��" && newnode->sex != "Ů")
			{
				cout << "ѧ�����Ա����������������ѧ����Ϣ��" << endl;
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
	if (first == NULL)               //��ϢϵͳΪ��ʱ���������
	{
		cout << "��ǰ������ϢϵͳΪ�գ�" << endl;
		return;
	}

	cout << setiosflags(ios::left)  //��Ϣϵͳ����ʱ���������
		<< setw(8) << "����"
		<< setw(8) << "����"
		<< setw(8) << "����"
		<< setw(8) << "�������"
		<< endl;

	Student* current = first; 
	while (current != NULL)        //������
	{
		cout << *current;
		current = current->next;
	}
}

void information_system::insert()
{
	cout << "��������Ҫ����Ŀ�����λ�ã�";
	int position;
	cin >> position;
	while (position < 1)             //�������λ�ò��Ϸ��������²���
	{
		cout << "����λ�ò��Ϸ���" << endl;
		cout<< "������������Ҫ����Ŀ�����λ�ã�";
		cin >> position;
	}

	Student* insert_student = new Student;
	while (1)                        //�жϲ����ѧ�������Ƿ��Ѵ��ڣ���������������
	{
		cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������!" << endl;
		cin >> *insert_student;
		Student* p = first;
		for (; p != NULL; p = p->next)//�������������Ƿ񿼺��Ѿ�����
		{
			if (p->number == insert_student->number)
			{
				cout << "�ÿ��ŵ�ѧ���Ѵ��ڣ������ٲ��롣"<<endl;
				break;
			}
		}
		if (p == NULL)break;
	}
	cout << endl;

	Student* front = NULL, * behind = first;  //����λ�õ�ֱ��ǰ����ֱ�Ӻ��
	if (first == NULL)             //����ʱ����Ϊ�յĲ���
	{
		first = tail = insert_student;
		first->next = tail->next = NULL;
		output();
		cout << endl;
		cout << "��ǰ��ϢϵͳΪ�գ��ʽ���ѧ����Ϣ������һλ" << endl;
	}
	else if (position == 1)         //����ʱ�����յĲ���������λ���ǵ�һ����
	{
		insert_student->next = first;
		first = insert_student;
		output();
	}
	else                            //����ʱ�����յĲ������Ҳ�������λ�ã��ǵ�һλ��
	{
		int i;
		for (i = 1; i < position && behind != NULL; i++)//������position������ǰ�������������
		{
			front = behind;
			behind = behind->next;
		}
		front->next = insert_student;
		insert_student->next = behind;
		output();
		if (i != position)
		{
			tail = insert_student;     //��βָ��ָ���²����ѧ��
			cout << "����λ���Ѿ��������һ��ѧ�����ʽ���ѧ����Ϣ�������һλ"<<endl;
		}
	}
}

void information_system::remove()
{
	if (first == NULL)    //��ϵͳΪ�գ�û�п�ɾ������ʱ�Ĳ���
	{
		cout << "��ǰ������ϢϵͳΪ�գ�û�п�ɾ�����ݣ�" << endl;
		return;
	}
	cout << "������Ҫɾ���Ŀ����Ŀ���:";
	int the_number;
	cin >> the_number;

	Student* front = NULL, * current = first;  //front���ڱ��Ҫɾ������ǰ����currentָ��Ҫɾ���ڵ�
	while (current != NULL && current->number != the_number)
	{
		front = current;
		current = current->next;
	}

	if (current == first)    //Ҫɾ����ѧ���ǵ�һ��
	{
		cout << "��ɾ���Ŀ�����Ϣ�ǣ�";
		cout << *first;
		first = first->next;
		delete current;
		cout << endl; 
		output();            //��ӡ����ϵͳ
	}
	else if (current != NULL)//�ҵ��ˣ������ǵ�һ��
	{
		cout << "��ɾ���Ŀ�����Ϣ�ǣ�";
		cout << *current;
		front->next = current->next;
		delete current;
		cout << endl;
		output();      
	}
	else               //û���ҵ���Ӧ�Ŀ���ѧ��       
	{
		cout << "δ�ҵ�Ҫɾ���Ŀ�����Ϣ!" << endl;
		remove();      //�ٴε���ɾ������
	}
}

void information_system::find()
{
	if (first == NULL)                   //����Ϊ�գ������ʾ����������
	{
		cout << "��ǰϵͳΪ�գ�û�пɲ�ѯ��Ϣ��" << endl;
		return;
	}
	 
	cout << "������Ҫ���ҵĿ������ţ�";    //����ǿգ����½���
	int the_number;                      //Ҫ���ҵĿ���
	cin >> the_number;
	Student* current = first;            //current����ָ����ҵĽ��
	while (current != NULL && current->number != the_number)
	{
		current = current->next;
	}

	if (current == NULL)                //���ҵĿ��Ų�����ʱ
	{
		cout << "�ÿ��Ŷ�Ӧ��ѧ����Ϣ������" << endl;
		find();
	}
	else
	{
		cout << setiosflags(ios::left)
			<< setw(8) << "����"
			<< setw(8) << "����"
			<< setw(8) << "����"
			<< setw(8) << "�������"
			<< endl;
		cout << *current << endl;
	}
}

void information_system::alter()
{
	if (first == NULL)                      //��ϵͳΪ�գ�û�п��޸�����ʱ�Ĳ���
	{
		cout << "��ǰ������ϢϵͳΪ�գ�û�п��޸����ݣ�" << endl;
		return;
	}

	cout << "������Ҫ�޸ĵĿ�����Ϣ�Ŀ��ţ�"; //ϵͳ��Ϊ��ʱ����
	int the_number;
	cin >> the_number;

	Student* old_information = first;
	while (old_information != NULL && old_information->number != the_number)//���Ҹÿ��ŵĿ���
	{
		old_information = old_information->next;
	}
	if (old_information != NULL)          //���ҳɹ�
	{
		cout << "�����������µ�ѧ����Ϣ��";
		cin >> *old_information;
		output();
	}
	else                                  //����ʧ��
	{
		cout << "��ѧ�Ŷ�Ӧ��ѧ����Ϣ�����ڣ�" << endl;
		alter();
	}
}

int main()
{
	information_system examinees;
	examinees.create();                 //��������ϵͳ
	examinees.output();                 //���û���ӡһ�鿼��ϵͳ
	cout << "����������Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������"
		<< endl
		<< endl;

	int order = 1;                      //��ʼִ�в�������ʼ��Ϊ1
	while (order != 0)                  //����0��ʾ��������
	{
		cout << "��ѡ����Ҫ���еĲ�����";
		cin >> order;
		while (order > 5 || order < 0)
		{
			cout << "��ָ����ڣ�������������ȷ��ָ�" << endl;
			cin >> order;
		}
		switch (order)
		{
		case 0:continue; break;
		case 1:examinees.insert(); break; //����
		case 2:examinees.remove(); break; //ɾ��
		case 3:examinees.find(); break;   //����
		case 4:examinees.alter(); break;  //�޸�
		case 5:examinees.output(); break; //��ӡ�����б�
		}
	}
	return 0;
}