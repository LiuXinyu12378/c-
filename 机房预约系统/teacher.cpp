#include "teacher.h"
#include<string>
#include"student.h"
#include"orderFile.h"
Teacher::Teacher()
{
	
}

Teacher::Teacher(int empId, string name, string pwd)
{
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//�˵�����
void Teacher::operMenu()
{
	cout << "��ӭ��ʦ��" << this->m_Name << endl;
	cout << "\t\t-------------------------------------------" << endl;
	cout << "\t\t|                                         |" << endl;
	cout << "\t\t|           1.�鿴����ԤԼ                |" << endl;
	cout << "\t\t|                                         |" << endl;
	cout << "\t\t|           2.���ԤԼ                    |" << endl;
	cout << "\t\t|                                         |" << endl;
	cout << "\t\t|           0.ע����¼                    |" << endl;
	cout << "\t\t|                                         |" << endl;
	cout << "\t\t-------------------------------------------" << endl;
	cout << "����������ѡ��" << endl;
}

//�鿴����ԤԼ
void Teacher::showAllOrder()
{
	Student stu;
	stu.showAllOrder();
}

//���ԤԼ
void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "����е�ԤԼ��" << endl;
	vector<int>v;
	int index = 1;

	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_OrderData[i]["status"] == "1" )
		{
			v.push_back(i);
			cout << index++ << " ";
			cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["date"] << " ";
			cout << "������" << of.m_OrderData[i]["stuName"] << " ";
			cout << "ѧ�ţ�" << of.m_OrderData[i]["stuId"] << " ";
			cout << (of.m_OrderData[i]["interval"] == "1" ? "����" : "����");
			cout << " ������" << of.m_OrderData[i]["roomId"];
			string status = "״̬��";
			if (of.m_OrderData[i]["status"] == "1")
			{
				status += "�����";
			}
			cout << status << endl;
		}
	}

	cout << "������ͨ����˵ı�ţ�0������" << endl;
	int select = 0;
	int ret = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "��������˽��:" << endl;
				cout << "1.ͨ��" << endl;
				cout << "2.��ͨ��" << endl;
				cout << "0.�˳�" << endl;
				cin >> ret;

				if (ret == 1)
				{
					of.m_OrderData[v[select - 1]]["status"] = "2";
					of.updateOrder();
					cout << "��ͨ��" << endl;
				}
				else
				{
					of.m_OrderData[v[select - 1]]["status"] = "-1";
					of.updateOrder();
					cout << "δͨ��" << endl;
				}
				break;
			}
		}
		cout << "������������������:" << endl;
	}
	system("pause");
	system("cls");
}
