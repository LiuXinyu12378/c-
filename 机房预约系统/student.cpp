#include"student.h"
#include<string>
#include<fstream>
#include"globalFile.h"
#include"orderFile.h"

Student::Student()
{

}
//有参构造 参数 ：学号 姓名 密码
Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	ifstream ifs;

	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		//将读取的信息放入到 容器中
		vCom.push_back(com);
	}
	ifs.close();

}

//菜单界面
void Student::operMenu()
{
	cout << "欢迎学生：" << this->m_Name << endl;
	cout << "\t\t-------------------------------------------" << endl;
	cout << "\t\t|                                         |" << endl;
	cout << "\t\t|           1.申请预约                    |" << endl;
	cout << "\t\t|                                         |" << endl;
	cout << "\t\t|           2.查看我的预约                |" << endl;
	cout << "\t\t|                                         |" << endl;
	cout << "\t\t|           3.查看所有预约                |" << endl;
	cout << "\t\t|                                         |" << endl;
	cout << "\t\t|           4.取消预约                    |" << endl;
	cout << "\t\t|                                         |" << endl;
	cout << "\t\t|           0.注销登录                    |" << endl;
	cout << "\t\t|                                         |" << endl;
	cout << "\t\t-------------------------------------------" << endl;
	cout << "请输入您的选择：" << endl;
}

//申请预约
void Student::applyOrder()
{
	cout << "机房开放的时间为周一至周五!" << endl;
	cout << "1.周一" << endl;
	cout << "2.周二" << endl;
	cout << "3.周三" << endl;
	cout << "4.周四" << endl;
	cout << "5.周五" << endl;
	cout << "0.退出" << endl;
	cout << "请选择你要预约的时间：" << endl;

	int select = 0;
	int date = 0;
	int interval = 0;
	int room = 0;

	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		system("cls");
		return;
	}
	cout << "请输入申请预约时间段：" << endl;
	cout << "1.上午" << endl;
	cout << "2.下午" << endl;
	cout << "0.退出" << endl;

	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		system("cls");
		return;
	}

	cout << "请选择机房：" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << it->m_ComId << "号机房容量为：" << it->m_MaxNum << endl;
	}
	cout << "0.退出" << endl;

	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= vCom.size())
		{
			break;
		}
		system("cls");
		return;
	}

	cout << "预约成功！审核中" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);

	ofs << "date:" << date << " ";
	ofs << " interval:" << interval << " ";
	ofs << " stuId:" << this->m_Id << " ";
	ofs << " stuName:" << this->m_Name << " ";
	ofs << " roomId:" << room << " ";
	ofs << " status:" << 1 << endl;

	ofs.close();
	system("pause");
	system("cls");
}

//查看自身预约
void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_OrderData[i]["stuId"].c_str()) == this->m_Id)
		{
			cout << "预约日期：周" << of.m_OrderData[i]["date"]<<" ";
			cout << (of.m_OrderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房：" << of.m_OrderData[i]["roomId"];
			string status = "状态：";
			if (of.m_OrderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			else if (of.m_OrderData[i]["status"] == "2")
			{
				status += "预约成功";
			}
			else if (of.m_OrderData[i]["status"] == "-1")
			{
				status += "预约失败";
			}
			else
			{
				status += "预约已取消";
			}
			cout << status << endl;
		}
	}
	system("pause");
	system("cls");
}

//查看所有预约
void Student::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		//if (atoi(of.m_OrderData[i]["stuId"].c_str()) == this->m_Id)
		{
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
			else if (of.m_OrderData[i]["status"] == "2")
			{
				status += "预约成功";
			}
			else if (of.m_OrderData[i]["status"] == "-1")
			{
				status += "预约失败";
			}
			else
			{
				status += "预约已取消";
			}
			cout << status << endl;
		}
	}
	system("pause");
	system("cls");
}

//取消预约
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;
	vector<int>v;
	int index = 1;

	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_OrderData[i]["stuId"].c_str()) == this->m_Id)
		{
			if (of.m_OrderData[i]["status"] == "1" || of.m_OrderData[i]["status"] == "0")
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
				else if (of.m_OrderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				cout << status << endl;
			}
		}
	}

	cout << "请输入取消的记录，0代表返回" << endl;
	int select = 0;

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
				of.m_OrderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入:" << endl;
	}
	system("pause");
	system("cls");
}

