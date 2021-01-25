#include"4_1952211_�ƽ���.h"

/***********************Stack<T>���ڵĳ�Ա��������*****************************/
template<class T>
bool Stack<T>::is_empty()         //�ж�ջ�Ƿ�Ϊ�գ�
{
	if (top == NULL)return true;
	return false;
}

template<class T>
void Stack<T>::push(const T& item)//��item����ֵ��ӵ�ջ���½ڵ���
{
	stacknode<T>* p= new stacknode<T>;
	p->data = item;
	p->next = top;
	top = p;
}

template<class T>
T Stack<T>::pop()                 //ջ��Ԫ�س�ջ������ջ��������
{
	stacknode<T>* p = top;
	top = top -> next;
	T item = p->data;
	delete p;
	return item;
}

template<class T>
void Stack<T>::empty()             //�������
{
	while (top != NULL)
	{
		stacknode<T>* p = top;
		top = top->next;
		delete p;
	}
}


/*********************calculate���ڵĴ�Ԫ��������******************************/
bool calculate::get2operand(double& left, double& right)//��ջ��ȡ����������
{
	//������ջ����ʱ���Ⱥ�ȡ����������������;ջ�վͷ���ȡֵʧ�ܵı�־
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

	//�ɹ�ȡ������������������ȡֵ�ɹ��ı�־
	return true;  
}

int calculate::PRI1(char ch)//�����������ջ�����ȼ�
{
	switch (ch)             //�����������Ƿ���ջ�����ȼ�
	{
	case '=':return 0; 
	case ')': return 1;
	case '+':case '-':return 2; 
	case 'x':case 'X':case '/':case '%':return 3;
	case '^':return 4;
	case '(':return 5;
	}
}

int calculate::PRI2(char ch)//�����������ջ�����ȼ�
{
	switch (ch)             //�����������Ƿ���ջ�����ȼ�
	{
	case '(':return 1;      //��(�������ȼ���ջ�����
	case '+':case '-':return 2; 
	case 'x':case 'X':case '/':case '%':return 3;
	case '^':return 4;
	}
}

bool calculate::do_operator(char op) //�Ե�ǰ�������������,��������ĳɹ���ʧ���ź�
{
	double value, left, right;       //value����������������������left�����������right���Ҳ�����
	bool result = get2operand(left, right);//result������¼�������Ƿ�ɹ�ȡ��

	//ȡ���ɹ�����������
	if (result)
	{
		switch (op)
		{
		case '+':value = left + right; Operand.push(value); tag = 1; break;
		case '-':value = left - right; Operand.push(value); tag = 1; break;
		case 'x':case 'X':value = left * right; Operand.push(value); tag = 1; break;
		case '/':
			if (right == 0.0)//����Ϊ��ʱ����ʾ������������
			{
				cout << "����������0\n";
				return false;//�������
			}
			else             //������������
			{
				value = left / right; Operand.push(value); tag = 1; break;
			}
		case '%':
			if (left - (int)left == 0.0 && right - (int)right == 0.0)//��������int�Ͳſ�������
			{
				value = (int)left % (int)right; Operand.push(value); tag = 1; break;
			}
			else             //���������ܽ���ȡ������ʱ��ʾ�����������
			{
				cout << "ȡ����������߱���������\n";
				return false;
			}
		case '^':value = pow(left, right); Operand.push(value); tag = 1; break;
		}
		return true;
	}

	//ȡ��ʧ�ܣ����ʧ����Ϣ
	else
	{
		cout << "������Ͳ�����������ƥ��\n";
		return false;//�������
	}
}

void calculate::run()  //��������������ʽ������
{
	char ch;           //ch��������ַ�
	double new_operand;//new_operand������Ĳ�����

	//�����������+��-�Ƿ��ǵ�Ŀ�����
	//tag==0��ʾǰһ����ջ���ǲ���������ô��ǰ��+��-���ǵ�Ŀ�����
	tag = 0;          
	cin >> ch;
	while (ch != '=')  //���롮=����ʾ���ʽ�������
	{
		//ch�ǲ�����ʱ�����������ջ
		if (ch == '+' || ch == '-' || ch == 'x' || ch == 'X' || ch == '/' || ch == '^' || ch == '%' || ch == '(' || ch == ')')
		{
			//������ջ�ǿ�ʱ��Ҫ����ջ����������ջ�����ȼ��͵�ǰ��������ջ�����ȼ�
			if (!Operator.is_empty())
			{
				char top_op = Operator.get_top();//��ȡջ�������
				//ջ�����ȼ�������ջ
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
						tag = 0;          //��ʾ��ch�ǲ�������ջ
					}
				}
				//ջ�����ȼ��߻����ջ���������ջ
				else                            
				{
					if (ch == ')')
					{
						char op = Operator.pop();//��ȡջ�������
						while (op != '(')        //һֱȡ��������㣬ֱ��(
						{
							if (!do_operator(op))//�����쳣����ֹ���㣬��������ʧ��
							{
								return;
							}
							op = Operator.pop();
						}
					}
					else
					{
						//ջ�ڲ���ʱ��ջ����������ջ�����ȼ���>=ch��ջ�����ȼ���һֱ��ջ����
						//PRI2(Operator.get_top())��ջ����������ջ�����ȼ�
						while (!Operator.is_empty() && (PRI2(Operator.get_top()) > PRI1(ch) || PRI2(Operator.get_top()) == PRI1(ch)))
						{
							if (!do_operator(Operator.pop()))return;//��������쳣����ֹ���㣬��������ʧ��
						}
						Operator.push(ch);//�����꣬ch���������ջ
						tag = 0;          //��ʾ��ch�ǲ�������ջ
					}
				}
			}
			//�����ջ��ʱֱ������
			else                         
			{
				if (tag == 0)//˵������ʽ��ͷ�������
				{
					if (ch == '+'|| ch == '-')//��ʱ��+��-һ���ǵ�Ŀ�����
					{
						Operand.push(0);
						Operator.push(ch);
					}
					else if (ch == '(')
					{
						Operator.push(ch);
					}
					else                     //�ǵ�Ŀ�������Ϊ���ʽ��ͷһ���Ǵ��
					{
						cout << "����ʽ��ͷ�������\n";
						return;
					}
				}
				else         //˫Ŀ��������ջ
				{
					Operator.push(ch);
					tag = 0;
				}
			}
		}
		//��������������������ջ
		else if(ch-1<'9'&&ch+1>'0')
		{
			cin.putback(ch);
			cin >> new_operand;
			Operand.push(new_operand);
			tag = 1;    //������tag��1
		}
		//�����ķǷ��ַ�ʱ�˳����㣬�����ʾ��Ϣ
		else
		{
			cout << "�����˷Ƿ��ַ���\n";
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

/*****************************������main()**********************************/
int main()
{
	calculate problem;    //Ҫ������������ʽ����
	char choice = 'y';    //�Ƿ�������г���Ŀ��Ʒ���y��ʾ�������г���
	cout << "�ӷ�+������-���˷�x����Сд���ɣ�������/���˷�^������%��С����()�������Ӣ�����뷨����\n";

	while(choice=='y')
	{ 
		cout << "������ʽ��\n";
		problem.run();    //��problem�е��������ʽ��������
		problem.clear();  //�������ͷſռ�
		cin.ignore(100, '\n');//���������,�����û������choiceӰ�쵽���ʽ������

		do
		{
			cout << "�Ƿ����(y,n)����";
			cin >> choice;
			cin.ignore(100, '\n');//���������,�����û������choiceӰ�쵽���ʽ������
		} while (choice != 'y' && choice != 'n');
	}
}