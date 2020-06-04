#include<iostream>
#include"identity.h"
#include<fstream>
#include<string>
#include"globalFile.h"
#include"manager.h"
#include"student.h"
#include"teacher.h"
using namespace std;

//进入学生子菜单界面
void studentMenu(Identity * student)
{
	while (true)
	{
		//调用学生子菜单
		student->operMenu();

		Student *stu = (Student *)student;
		int select = 0;
		cin >> select; //接受用户选择

		if (select == 1) //申请预约
		{
			stu->applyOrder();
		}
		else if (select == 2)  //查看自身预约
		{
			stu->showMyOrder();
		}
		else if (select == 3)
		{
			stu->showAllOrder();
		}
		else if (select == 4)
		{
			stu->cancelOrder();
		}
		else
		{
			delete student;
			cout << "退出登录！" << endl;
			system("pause");
			system("cls");
			return;
		}
	
	}
}

//进入教师子菜单界面
void teacherMenu(Identity * teacher)
{
	while (true)
	{
		//调用教师子菜单
		teacher->operMenu();

		Teacher *stu = (Teacher *)teacher;
		int select = 0;
		cin >> select; //接受用户选择

		if (select == 1) //申请预约
		{
			stu->showAllOrder();
		}
		else if (select == 2)  //查看自身预约
		{
			stu->validOrder();
		}
		else
		{
			delete teacher;
			cout << "退出登录！" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

//进入管理员子菜单界面
void managerMenu(Identity * manager)
{
	while (true)
	{
		//调用管理员子菜单
		manager->operMenu();
		//将父类指针 转为子类指针，调用子类里其他接口
		Manager * man = (Manager*)manager;

		int select = 0;
		cin >> select;
		if (select == 1) //添加账号
		{
			man->addPerson();
		}
		else if (select == 2)//查看账号
		{
			man->showPerson();
		}
		else if (select == 3) //查看机房
		{
			man->showComputer();
		}
		else if (select == 4) //清空预约
		{
			man->cleanFile();
		}
		else
		{
			delete manager;  //销毁掉堆区对象
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

//登录功能 参数1 操作文件名 参数2 操作身份类型
void LoginIn(string fileName, int type)
{
	//父类指针，用于指向子类对象
	Identity *person = NULL;
	//读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//准备接受用户的信息
	int id = 0;
	string name;
	string pwd;

	//判断身份
	if (type == 1)
	{
		cout << "请输入你的学号：" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入您的职工号：" << endl;
		cin >> id;
	}
	cout << "请输入用户名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	if (type == 1)
	{
		//学生身份验证
		int fId; //从文件中读取的id号
		string fName; //从文件中获取的姓名
		string fPwd; //从文件中获取密码
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "学生验证登录成功！" << endl;
				system("cls");

				person = new Student(id, name, pwd);
				//进去学生身份的子菜单
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//教师身份验证
		int fId; //从文件中读取的id号
		string fName; //从文件中获取的姓名
		string fPwd; //从文件中获取密码
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "教师验证登录成功！" << endl;
				system("cls");

				person = new Teacher(id, name, pwd);
				//进去教师身份的子菜单
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员
		string fName; //从文件中获取的姓名
		string fPwd; //从文件中获取密码
		while (ifs >> fName && ifs >> fPwd)
		{
			if (fName == name && fPwd == pwd)
			{
				cout << "管理员验证登录成功！" << endl;
				system("cls");

				person = new Manager(name, pwd);
				//进去管理员身份的子菜单

				managerMenu(person);
				return;
			}
		}
	}
	cout << "验证登录失败！" << endl;
	system("pause");
	system("cls");
	return;
}


int main()
{
	int select = 0;
	while (true)
	{
		cout << "\t\t\t\t==================================" << endl;
		cout << "\t\t\t\t|    欢迎使用机房预约管理系统    |" << endl;
		cout << "\t\t\t\t----------------------------------" << endl;
		cout << "\t\t\t\t|                                |" << endl;
		cout << "\t\t\t\t|            1.学生代表          |" << endl;
		cout << "\t\t\t\t|            2.老师              |" << endl;
		cout << "\t\t\t\t|            3.管理员            |" << endl;
		cout << "\t\t\t\t|            0.退出              |" << endl;
		cout << "\t\t\t\t|                                |" << endl;
		cout << "\t\t\t\t----------------------------------" << endl;
		cout << "请输入您的选择：" << endl;

		cin >> select;//接受用户选择

		switch (select)
		{
		case 1: //学生身份
			LoginIn(STUDENT_FILE, 1);
			break;

		case 2: //老师身份
			LoginIn(TEACHER_FILE, 2);
			break;

		case 3: //管理员身份
			LoginIn(ADMIN_FILE, 3);
			break;

		case 0:
			cout << "欢迎下一次使用" << endl;
			system("pause");
			exit(0);
			break;

		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}