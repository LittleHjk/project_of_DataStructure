#include<iostream>
using namespace std;

/*************************�����Ķ���***************************/
class family_tree;     //�������������  

class member           //member��Ķ��壬member�Ǽ�����������ڵ���
{
	friend family_tree;//����������member����Ԫ��
private:
	string name;       //��Ա������
	member* left_child;//����Ů
	member* right_bro; //���ֵ�
public:
	member()           //���캯������ʼ������Ů�����ֵ�Ϊ��
	{
		left_child = right_bro = NULL; 
	}
};

class family_tree         //��������Ķ���
{
private:
	member* ancestor;     //ָ����������ȵ�ָ��
public:
	family_tree()         //����create��������������
	{
		create(); 
	}       
	~family_tree()        //����empty��������ռ���
	{
		empty(ancestor);
	}
	void create();        //��������
	void add_family();    //��ĳ�˴���һ����ͥ
	void add_member();    //��ĳ������µļ�ͥ��Ա
	void delete_family(); //��ɢĳ�˵ļ�ͥ��Ա
	void change_name();   //����ĳ����Ա������
	member* find(string name,member* start);//����ĳ��������Ӧ��ͥ��Ա
	member* last_child(member* parent);     //����ĳ����Ա��С����Ů
	void output_child(member* parent);      //���ĳ����Ա�ĵ�һ������
	void empty(member*& root);               //ɾ����ǰ�ڵ���Ϊ���ڵ�Ķ�����
};


/************************family_tree�ĳ�Ա��������****************************/
void family_tree::create()        //��������
{
	cout << "���Ƚ���һ�����ף�\n";
	cout << "���������ȵ�������";

	member* p = new member;      //����һ���ڵ�������Ϊ���Ƚڵ�
	cin >> p->name;              //�������ȵ�����
	ancestor = p;                //�����е�����ָ��ָ��p

	cout << "�˼��׵������ǣ�" << ancestor->name;
	cout << endl << endl;
}

void family_tree::add_family()                  //��ĳ�˴���һ����ͥ
{
	cout << "������Ҫ������ͥ���˵�������";
	string parent_name;                         //parent_name��Ҫ�齨��ͥ���˵�����
	cin >> parent_name;

	while (find(parent_name, ancestor) == NULL) //���Ҹ�������Ӧ�ļ����Ա��û�иü����Աʱ����ʾ��������������
	{
		cout << parent_name<<"�����ڣ����������룺";
		cin >> parent_name;
	}

	member* current, * parent;                  //current�Ǹ���ָ�룬�����parent��Ӻ�����Ů
	current=parent= find(parent_name, ancestor);//����ָ�붼��ָ���û������Ҫ������ͥ�ĳ�Ա

	cout << "������" << parent_name << "�Ķ�Ů������";
	int number, current_number = 0;             //number����Ů��������current_number�ǵ�ǰ�ɹ���ӵ���Ů����
	cin >> number;
	while (number < 1)                          //��֤���������������������
	{
		cout << "��Ů���������������������������룺";
		cin >> number;
	}

	cout << "����������" << parent_name << "�Ķ�Ů��������";
	member* child = new member;                 //��һ������
	cin >> child->name;
	while (find(child->name, ancestor) != NULL)   //�¼�ͥ��Ա�Ѿ�����ʱ����ʾ���󣬲���������
	{
		cout << child->name<<"�Ѿ����ڣ���ӵ�1����Ů��ʼ��������������";
		cin.ignore(100, '\n');                    
		cin >> child->name;
	}
	current->left_child = child;                  //��ӵ�һ������
	current_number += 1;                          //��ӳɹ���current_number +1
	current = child;                              //currentָ���һ���ĺ���
	for (int i = 1; i < number; i++)              //�������ʣ��ĺ���
	{
		member* child = new member;
		cin >> child->name;
		while (find(child->name, ancestor) != NULL)//�¼�ͥ��Ա�Ѿ�����ʱ����ʾ���󣬲���������
		{
			cout << child->name << "�Ѿ����ڣ���ӵ�"<<current_number+1<<"����Ů��ʼ��������������";
			cin.ignore(100, '\n');
			cin >> child->name;
		}
		current->right_bro = child;               //�º�����Ϊ�ɺ��ӵ��ֵ�
		current = child;                          //current����ָ���º���
		current_number += 1;                      //��ӳɹ���current_number +1
	}
	output_child(parent);                         //�����һ������
	cin.ignore(100,'\n');                         //���������
}

void family_tree::add_member()
{
	cout << "������Ҫ��Ӷ��ӣ���Ů�������˵����֣�";
	string parent_name;
	cin >> parent_name;
	while (find(parent_name, ancestor) == NULL)   //û�иü����Աʱ����ʾ��������������
	{
		cout << parent_name<<"�����ڣ����������룺";
		cin >> parent_name;
	}

	member* parent = find(parent_name, ancestor);

	cout << "������" << parent_name << "����ӵĶ��ӣ���Ů������������";
	member* child=new member;
	cin >> child->name;
	while (find(child->name, ancestor) != NULL)   //�¼�ͥ��Ա�Ѿ�����ʱ����ʾ���󣬲���������
	{
		cout << child->name<<"�Ѿ����ڣ�����������������";
		cin >> child->name;
	}

	//��������Ů
	if (last_child(parent) != NULL)               //������Ů����ԭ�����һ����Ů�ĺ��� 
	{
		last_child(parent)->right_bro = child;        
	}
	else                                          //����parentԭ��û�к��ӣ�����뵽��һ������
	{
		parent->left_child = child;               
	}
	output_child(parent);                         //�����һ����Ů            
}

void family_tree::delete_family()
{
	cout << "������Ҫ��ɢ��ͥ���˵�������";
	string parent_name;
	cin >> parent_name;

	while (find(parent_name, ancestor) == NULL) //û�иü����Աʱ����ʾ��������������
	{
		cout << parent_name <<"�����ڣ����������룺";
		cin >> parent_name;
	}
	member* parent = find(parent_name, ancestor);

	output_child(parent);                   //�����parent�ĵ�һ������Ů
	empty(parent->left_child);              //ɾ��parent����������
}

void family_tree::change_name()
{
	cout << "������Ҫ�����������˵�Ŀǰ������";
	string old_name;
	cin >> old_name;
	while (find(old_name, ancestor) == NULL) //û�иü����Աʱ����ʾ��������������
	{
		cout << old_name << "�����ڣ����������룺";
		cin >> old_name;
	}
	member* person = find(old_name, ancestor);//������������Ա��λ��

	cout << "��������ĺ��������";
	string new_name;
	cin >> new_name;
	while (find(new_name, ancestor) != NULL) //�������Ѿ�����ʱ����ʾ��������������
	{
		cout << new_name << "�Ѵ��ڣ����������룺";
		cin >> new_name;
	}
	person->name = new_name;                 //��������
	cout << old_name << "�Ѹ���Ϊ" << person->name;
}

member* family_tree::find(string name,member* start)
{
	member* p = start;
	if (p == NULL)return NULL;        //��ǰ�ڵ�Ϊ��
	else if (p->name == name)return p;//�ҵ��ó�Ա
	else                              //�����ں��Ӻ��ֵ���Ѱ��
	{
		member* q = find(name, p->left_child);
		if (q != NULL)return q;
		else return find(name, p->right_bro);
	}
}

member* family_tree::last_child(member* parent)
{
	member* child = parent->left_child;
	if (child != NULL)     //�к���ʱ���ҵ����һ������
	{
		while (child->right_bro != NULL)
		{
			child = child->right_bro;
		}
	}
	return child;
}

void family_tree::output_child(member* parent)
{
	member* p = parent->left_child;
	cout << parent->name << "�ĵ�һ�������ǣ�";
	if (p == NULL)
	{
		cout << "��\n\n";
		return;
	}
	while (p != NULL)
	{
		cout << p->name<<"   ";
		p = p->right_bro;
	}
}

void family_tree::empty(member*& root)
{
	if (root == NULL)
	{
		return;
	}
	if (root->left_child == NULL && root->right_bro == NULL)
	{
		delete root;
		root = NULL;
	}
	else 
	{
		if (root->left_child != NULL)empty(root->left_child);
		if (root->right_bro != NULL)empty(root->right_bro);
	}
}


/***************************������main����*******************************/

int main()
{
	cout << "**              ���׹���ϵͳ                     **\n"
		<< "===================================================\n"
		<< "**           ��ѡ��Ҫִ�еĲ�����                **\n"
		<< "**             A ---���Ƽ���                     **\n"
		<< "**             B ---��Ӽ�ͥ��Ա                 **\n"
		<< "**             C ---��ɢ�ֲ���ͥ                 **\n"
		<< "**             D ---���ļ�ͥ��Ա����             **\n"
		<< "**             E ---�˳�����                     **\n"
		<< "===================================================\n";

	family_tree Family;               //��������

	cout << "��ѡ��Ҫִ�еĲ�����";
	char operation;
	cin >> operation;
	while (operation < 'A' || operation>'E')//��ѡ��Ĳ���������ʱ�������룬����ʾ
	{
		cin.ignore(100, '\n');
		cout << "ѡ��Ĳ��������ڣ�����������A~E֮��Ĳ�����";
		cin >> operation;
	}

	while (operation != 'E')
	{
		switch (operation)
		{
		case'A':Family.add_family(); break;
		case'B':Family.add_member(); break;
		case'C':Family.delete_family(); break;
		case'D':Family.change_name(); break;
		}
		cout << endl << endl;
		cout << "��ѡ��Ҫִ�еĲ�����";
		cin >> operation;
		while (operation < 'A' || operation>'E')
		{
			cin.ignore(100, '\n');
			cout << "ѡ��Ĳ��������ڣ�����������A~E֮��Ĳ�����";
			cin >> operation;
		}
	}
	cout << "Press any key to continue.";
}