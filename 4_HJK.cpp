#include"4_1952211_黄金坤.h"

/***********************Stack<T>类内的成员函数定义*****************************/
template<class T>
bool Stack<T>::is_empty()         //判断栈是否为空；
{
	if (top == NULL)return true;
	return false;
}

template<class T>
void Stack<T>::push(const T& item)//将item的数值添加到栈的新节点中
{
	stacknode<T>* p= new stacknode<T>;
	p->data = item;
	p->next = top;
	top = p;
}

template<class T>
T Stack<T>::pop()                 //栈顶元素出栈，返回栈顶的数据
{
	stacknode<T>* p = top;
	top = top -> next;
	T item = p->data;
	delete p;
	return item;
}

template<class T>
void Stack<T>::empty()             //清空链表
{
	while (top != NULL)
	{
		stacknode<T>* p = top;
		top = top->next;
		delete p;
	}
}


/*********************calculate类内的创元函数定义******************************/
bool calculate::get2operand(double& left, double& right)//从栈中取两个操作数
{
	//操作数栈不空时，先后取出两个操作数，中途栈空就返回取值失败的标志
	if (!Operand.is_empty())     
	{
		right = Operand.pop();
	}
	else return false;

	if (!Operand.is_empty())
	{
		left = Operand.pop();
	}
	else return false;

	//成功取出两个操作数，返回取值成功的标志
	return true;  
}

int calculate::PRI1(char ch)//返回运算符的栈外优先级
{
	switch (ch)             //定义各个运算非符的栈外优先级
	{
	case '=':return 0; 
	case ')': return 1;
	case '+':case '-':return 2; 
	case 'x':case 'X':case '/':case '%':return 3;
	case '^':return 4;
	case '(':return 5;
	}
}

int calculate::PRI2(char ch)//返回运算符的栈内优先级
{
	switch (ch)             //定义各个运算非符的栈内优先级
	{
	case '(':return 1;      //‘(’的优先级在栈内最低
	case '+':case '-':return 2; 
	case 'x':case 'X':case '/':case '%':return 3;
	case '^':return 4;
	}
}

bool calculate::do_operator(char op) //对当前运算符进行运算,返回运算的成功或失败信号
{
	double value, left, right;       //value是两个操作数的运算结果，left是左操作数，right是右操作数
	bool result = get2operand(left, right);//result用来记录操作数是否成功取出

	//取数成功，进行运算
	if (result)
	{
		switch (op)
		{
		case '+':value = left + right; Operand.push(value); tag = 1; break;
		case '-':value = left - right; Operand.push(value); tag = 1; break;
		case 'x':case 'X':value = left * right; Operand.push(value); tag = 1; break;
		case '/':
			if (right == 0.0)//除数为零时，提示出错，结束运算
			{
				cout << "除数不能是0\n";
				return false;//运算出错
			}
			else             //除法正常进行
			{
				value = left / right; Operand.push(value); tag = 1; break;
			}
		case '%':
			if (left - (int)left == 0.0 && right - (int)right == 0.0)//操作数是int型才可以运算
			{
				value = (int)left % (int)right; Operand.push(value); tag = 1; break;
			}
			else             //操作数不能进行取余运算时提示出错，运算结束
			{
				cout << "取余运算的两边必须是整数\n";
				return false;
			}
		case '^':value = pow(left, right); Operand.push(value); tag = 1; break;
		}
		return true;
	}

	//取数失败，输出失败信息
	else
	{
		cout << "运算符和操作数个数不匹配\n";
		return false;//运算出错
	}
}

void calculate::run()  //完成整个算术表达式的运算
{
	char ch;           //ch是输入的字符
	double new_operand;//new_operand是输入的操作数

	//用来帮助辨别+、-是否是单目运算符
	//tag==0表示前一次入栈的是操作符，那么当前的+、-就是单目运算符
	tag = 0;          
	cin >> ch;
	while (ch != '=')  //输入‘=’表示表达式输入结束
	{
		//ch是操作符时，入操作符的栈
		if (ch == '+' || ch == '-' || ch == 'x' || ch == 'X' || ch == '/' || ch == '^' || ch == '%' || ch == '(' || ch == ')')
		{
			//操作符栈非空时，要分析栈顶操作符的栈内优先级和当前操作符的栈外优先级
			if (!Operator.is_empty())
			{
				char top_op = Operator.get_top();//读取栈顶运算符
				//栈外优先级高则入栈
				if (PRI1(ch) > PRI2(top_op))    
				{
					if (ch == '+' && tag == 0) 
					{
						Operand.push(0);
						Operator.push(ch);
					}
					else if (ch == '-' && tag == 0)
					{
						Operand.push(0);
						Operator.push(ch);
					}
					else
					{
						Operator.push(ch);
						tag = 0;          //表示是ch是操作符入栈
					}
				}
				//栈内优先级高或等则栈内运算符出栈
				else                            
				{
					if (ch == ')')
					{
						char op = Operator.pop();//读取栈顶运算符
						while (op != '(')        //一直取运算符运算，直到(
						{
							if (!do_operator(op))//运算异常则终止运算，报告运算失败
							{
								return;
							}
							op = Operator.pop();
						}
					}
					else
					{
						//栈内不空时，栈顶操作符的栈内优先级高>=ch的栈外优先级则一直出栈运算
						//PRI2(Operator.get_top())是栈顶操作符的栈内优先级
						while (!Operator.is_empty() && (PRI2(Operator.get_top()) > PRI1(ch) || PRI2(Operator.get_top()) == PRI1(ch)))
						{
							if (!do_operator(Operator.pop()))return;//如果运算异常则终止运算，报告运算失败
						}
						Operator.push(ch);//运算完，ch再入操作符栈
						tag = 0;          //表示是ch是操作符入栈
					}
				}
			}
			//运算符栈空时直接输入
			else                         
			{
				if (tag == 0)//说明计算式开头是运算符
				{
					if (ch == '+'|| ch == '-')//此时的+、-一定是单目运算符
					{
						Operand.push(0);
						Operator.push(ch);
					}
					else if (ch == '(')
					{
						Operator.push(ch);
					}
					else                     //非单目运算符作为表达式开头一定是错的
					{
						cout << "计算式开头输入错误\n";
						return;
					}
				}
				else         //双目操作符进栈
				{
					Operator.push(ch);
					tag = 0;
				}
			}
		}
		//输入的是数字则进操作数栈
		else if(ch-1<'9'&&ch+1>'0')
		{
			cin.putback(ch);
			cin >> new_operand;
			Operand.push(new_operand);
			tag = 1;    //进数则tag置1
		}
		//其他的非法字符时退出运算，输出提示信息
		else
		{
			cout << "输入了非法字符！\n";
			return;
		}
		cin >> ch;
	}
	while (!Operator.is_empty())
	{
		if (!do_operator(Operator.pop()))return;
	}
	cout << Operand.pop()<<endl;
}

/*****************************主函数main()**********************************/
int main()
{
	calculate problem;    //要计算的算术表达式对象
	char choice = 'y';    //是否继续进行程序的控制符，y表示继续进行程序
	cout << "加法+、减法-、乘法x（大小写均可）、除法/、乘方^、求余%、小括号()必须采用英文输入法输入\n";

	while(choice=='y')
	{ 
		cout << "输入表达式：\n";
		problem.run();    //对problem中的算术表达式进行运算
		problem.clear();  //计算完释放空间
		cin.ignore(100, '\n');//清空输入流,避免用户输入的choice影响到表达式的输入

		do
		{
			cout << "是否继续(y,n)？：";
			cin >> choice;
			cin.ignore(100, '\n');//清空输入流,避免用户输入的choice影响到表达式的输入
		} while (choice != 'y' && choice != 'n');
	}
}