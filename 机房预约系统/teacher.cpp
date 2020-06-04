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

//菜单界面
void Teacher::operMenu()
{
	cout << "欢迎教师：" << this->m_Name << endl;
	cout << "\t\t-------------------------------------------" << endl;
	cout << "\t\t|                                         |" << endl;
	cout << "\t\t|           1.查看所有预约                |" << endl;
	cout << "\t\t|                                         |" << endl;
	cout << "\t\t|           2.审核预约                    |" << endl;
	cout << "\t\t|                                         |" << endl;
	cout << "\t\t|           0.注销登录                    |" << endl;
	cout << "\t\t|                                         |" << endl;
	cout << "\t\t-------------------------------------------" << endl;
	cout << "请输入您的选择：" << endl;
}

//查看所有预约
void Teacher::showAllOrder()
{
	Student stu;
	stu.showAllOrder();
}

//审核预约
void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "审核中的预约：" << endl;
	vector<int>v;
	int index = 1;

	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_OrderData[i]["status"] == "1" )
		{
			v.push_back(i);
			cout << index++ << " ";
			cout << "预约日期：周" << of.m_OrderData[i]["date"] << " ";
			cout << "姓名：" << of.m_OrderData[i]["stuName"] << " ";
			cout << "学号：" << of.m_OrderData[i]["stuId"] << " ";
			cout << (of.m_OrderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房：" << of.m_OrderData[i]["roomId"];
			string status = "状态：";
			if (of.m_OrderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			cout << status << endl;
		}
	}

	cout << "请输入通过审核的编号，0代表返回" << endl;
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
				cout << "请输入审核结果:" << endl;
				cout << "1.通过" << endl;
				cout << "2.不通过" << endl;
				cout << "0.退出" << endl;
				cin >> ret;

				if (ret == 1)
				{
					of.m_OrderData[v[select - 1]]["status"] = "2";
					of.updateOrder();
					cout << "已通过" << endl;
				}
				else
				{
					of.m_OrderData[v[select - 1]]["status"] = "-1";
					of.updateOrder();
					cout << "未通过" << endl;
				}
				break;
			}
		}
		cout << "输入有误，请重新输入:" << endl;
	}
	system("pause");
	system("cls");
}
