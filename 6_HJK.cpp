#include<iostream>
using namespace std;

/*************************相关类的定义***************************/
class family_tree;     //家谱树类的声明  

class member           //member类的定义，member是家谱树的链表节点类
{
	friend family_tree;//家谱树类是member的友元类
private:
	string name;       //成员的姓名
	member* left_child;//左子女
	member* right_bro; //右兄弟
public:
	member()           //构造函数，初始化左子女和右兄弟为空
	{
		left_child = right_bro = NULL; 
	}
};

class family_tree         //家谱树类的定义
{
private:
	member* ancestor;     //指向家谱中祖先的指针
public:
	family_tree()         //调用create函数，创建家谱
	{
		create(); 
	}       
	~family_tree()        //调用empty函数，清空家谱
	{
		empty(ancestor);
	}
	void create();        //创建家谱
	void add_family();    //给某人创建一个家庭
	void add_member();    //给某人添加新的家庭成员
	void delete_family(); //解散某人的家庭成员
	void change_name();   //更改某个成员的姓名
	member* find(string name,member* start);//查找某个姓名对应家庭成员
	member* last_child(member* parent);     //查找某个成员最小的子女
	void output_child(member* parent);      //输出某个成员的第一代孩子
	void empty(member*& root);               //删除当前节点作为根节点的二叉树
};


/************************family_tree的成员函数定义****************************/
void family_tree::create()        //创建家谱
{
	cout << "首先建立一个家谱！\n";
	cout << "请输入祖先的姓名：";

	member* p = new member;      //创建一个节点用来作为祖先节点
	cin >> p->name;              //输入祖先的姓名
	ancestor = p;                //家谱中的祖先指针指向p

	cout << "此家谱的祖先是：" << ancestor->name;
	cout << endl << endl;
}

void family_tree::add_family()                  //给某人创建一个家庭
{
	cout << "请输入要建立家庭的人的姓名：";
	string parent_name;                         //parent_name是要组建家庭的人的名字
	cin >> parent_name;

	while (find(parent_name, ancestor) == NULL) //查找该姓名对应的家族成员，没有该家族成员时，提示出错，并重新输入
	{
		cout << parent_name<<"不存在，请重新输入：";
		cin >> parent_name;
	}

	member* current, * parent;                  //current是辅助指针，方便给parent添加后续子女
	current=parent= find(parent_name, ancestor);//两个指针都先指向用户输入的要建立家庭的成员

	cout << "请输入" << parent_name << "的儿女人数：";
	int number, current_number = 0;             //number是子女总人数，current_number是当前成功添加的子女人数
	cin >> number;
	while (number < 1)                          //保证输入的人数必须是正整数
	{
		cout << "儿女人数必须是正整数，请重新输入：";
		cin >> number;
	}

	cout << "轻依次输入" << parent_name << "的儿女的姓名：";
	member* child = new member;                 //第一个孩子
	cin >> child->name;
	while (find(child->name, ancestor) != NULL)   //新家庭成员已经存在时，提示错误，并重新输入
	{
		cout << child->name<<"已经存在，请从第1个儿女开始重新输入姓名：";
		cin.ignore(100, '\n');                    
		cin >> child->name;
	}
	current->left_child = child;                  //添加第一个孩子
	current_number += 1;                          //添加成功，current_number +1
	current = child;                              //current指向第一个的孩子
	for (int i = 1; i < number; i++)              //接着添加剩余的孩子
	{
		member* child = new member;
		cin >> child->name;
		while (find(child->name, ancestor) != NULL)//新家庭成员已经存在时，提示错误，并重新输入
		{
			cout << child->name << "已经存在，请从第"<<current_number+1<<"个儿女开始重新输入姓名：";
			cin.ignore(100, '\n');
			cin >> child->name;
		}
		current->right_bro = child;               //新孩子作为旧孩子的兄弟
		current = child;                          //current继续指向新孩子
		current_number += 1;                      //添加成功，current_number +1
	}
	output_child(parent);                         //输出第一代孩子
	cin.ignore(100,'\n');                         //清空输入流
}

void family_tree::add_member()
{
	cout << "请输入要添加儿子（或女儿）的人的名字：";
	string parent_name;
	cin >> parent_name;
	while (find(parent_name, ancestor) == NULL)   //没有该家族成员时，提示出错，并重新输入
	{
		cout << parent_name<<"不存在，请重新输入：";
		cin >> parent_name;
	}

	member* parent = find(parent_name, ancestor);

	cout << "请输入" << parent_name << "新添加的儿子（或女儿）的姓名：";
	member* child=new member;
	cin >> child->name;
	while (find(child->name, ancestor) != NULL)   //新家庭成员已经存在时，提示错误，并重新输入
	{
		cout << child->name<<"已经存在，请重新输入姓名：";
		cin >> child->name;
	}

	//插入新子女
	if (last_child(parent) != NULL)               //把新子女加在原先最后一个子女的后面 
	{
		last_child(parent)->right_bro = child;        
	}
	else                                          //若是parent原先没有孩子，则加入到第一个孩子
	{
		parent->left_child = child;               
	}
	output_child(parent);                         //输出第一代子女            
}

void family_tree::delete_family()
{
	cout << "请输入要解散家庭的人的姓名：";
	string parent_name;
	cin >> parent_name;

	while (find(parent_name, ancestor) == NULL) //没有该家族成员时，提示出错，并重新输入
	{
		cout << parent_name <<"不存在，请重新输入：";
		cin >> parent_name;
	}
	member* parent = find(parent_name, ancestor);

	output_child(parent);                   //先输出parent的第一代的子女
	empty(parent->left_child);              //删除parent的所有子孙
}

void family_tree::change_name()
{
	cout << "请输入要更改姓名的人的目前姓名：";
	string old_name;
	cin >> old_name;
	while (find(old_name, ancestor) == NULL) //没有该家族成员时，提示出错，并重新输入
	{
		cout << old_name << "不存在，请重新输入：";
		cin >> old_name;
	}
	member* person = find(old_name, ancestor);//存下这个家族成员的位置

	cout << "请输入更改后的姓名：";
	string new_name;
	cin >> new_name;
	while (find(new_name, ancestor) != NULL) //新名字已经存在时，提示出错，并重新输入
	{
		cout << new_name << "已存在，请重新输入：";
		cin >> new_name;
	}
	person->name = new_name;                 //更改姓名
	cout << old_name << "已更名为" << person->name;
}

member* family_tree::find(string name,member* start)
{
	member* p = start;
	if (p == NULL)return NULL;        //当前节点为空
	else if (p->name == name)return p;//找到该成员
	else                              //继续在孩子和兄弟中寻找
	{
		member* q = find(name, p->left_child);
		if (q != NULL)return q;
		else return find(name, p->right_bro);
	}
}

member* family_tree::last_child(member* parent)
{
	member* child = parent->left_child;
	if (child != NULL)     //有孩子时，找到最后一个孩子
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
	cout << parent->name << "的第一代子孙是：";
	if (p == NULL)
	{
		cout << "无\n\n";
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


/***************************主函数main（）*******************************/

int main()
{
	cout << "**              家谱管理系统                     **\n"
		<< "===================================================\n"
		<< "**           请选择要执行的操作：                **\n"
		<< "**             A ---完善家谱                     **\n"
		<< "**             B ---添加家庭成员                 **\n"
		<< "**             C ---解散局部家庭                 **\n"
		<< "**             D ---更改家庭成员姓名             **\n"
		<< "**             E ---退出程序                     **\n"
		<< "===================================================\n";

	family_tree Family;               //创建家谱

	cout << "请选择要执行的操作：";
	char operation;
	cin >> operation;
	while (operation < 'A' || operation>'E')//当选择的操作不存在时重新输入，并提示
	{
		cin.ignore(100, '\n');
		cout << "选择的操作不存在，请重新输入A~E之间的操作：";
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
		cout << "请选择要执行的操作：";
		cin >> operation;
		while (operation < 'A' || operation>'E')
		{
			cin.ignore(100, '\n');
			cout << "选择的操作不存在，请重新输入A~E之间的操作：";
			cin >> operation;
		}
	}
	cout << "Press any key to continue.";
}