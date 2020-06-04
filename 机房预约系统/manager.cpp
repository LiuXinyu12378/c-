#include"manager.h"
#include<string>
#include<fstream>
#include"globalFile.h"

Manager::Manager()
{

}

Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;
	initVector();
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom com;

	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		vCom.push_back(com);
	}
	ifs.close();

}

//菜单界面
void Manager::operMenu()
{
	cout << "欢迎管理员：" << this->m_Name << endl;
	cout << "\t\t-----------------------------------------" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|             1.添加账号                |" << endl;
	cout << "\t\t|             2.查看账号                |" << endl;
	cout << "\t\t|             3.查看机房                |" << endl;
	cout << "\t\t|             4.清空预约                |" << endl;
	cout << "\t\t|             0.注销登录                |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t-----------------------------------------" << endl;
	cout << "请输入你的选择：" << endl;
}

//添加账号
void Manager::addPerson()
{
	cout << "请输入添加账号类型" << endl;
	cout << "1.添加学生" << endl;
	cout << "2.添加老师" << endl;
	cout << "0.退出" << endl;

	string fileName; //操作文件名
	string tip;  //提示id号
	string errorTip;

	ofstream ofs; //文件操作对象

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		fileName = STUDENT_FILE;
		tip = "请输入学号：";
		errorTip = "此学号已经使用！";
	}
	else if (select == 2)
	{
		fileName = TEACHER_FILE;
		tip = "请输入职工编号：";
		errorTip = "此工号已经使用！";
	}
	else
	{
		system("cls");
		return;
	}
	ofs.open(fileName, ios::out | ios::app);

	int id;
	string name;
	string pwd;

	while (true)
	{
		cout << tip << endl;
		cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret) //有重复
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}

	cout << "请输入姓名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << endl;
	cout << "添加成功！" << endl;
	system("pause");
	system("cls");

	ofs.close();

	initVector();
}

//查看账号
void Manager::showPerson()
{
	initVector();
	cout << "请选择要查找的类型" << endl;
	cout << "1.学生" << endl;
	cout << "2.老师" << endl;
	cout << "0.退出" << endl;
	cout << "请输入你的选择：";
	int select = 0;

	cin >> select;
	if (select == 1)
	{
		cout << "学生信息如下：" << endl;
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			cout << "学号：" << it->m_Id << " 姓名：" << it->m_Name << " 密码："<<it->m_Pwd<<endl;
		}
	}
	else if (select == 2)
	{
		cout << "教师信息如下：" << endl;
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			cout << "工号：" << it->m_EmpId << " 姓名：" << it->m_Name <<" 密码："<<it->m_Pwd<<endl;
		}
	}
	else
	{
		system("cls");
		return;
	}

	system("pause");
	system("cls");

}

//查看机房信息
void Manager::showComputer()
{
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "机房编号：" << it->m_ComId << " 机房容量：" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

//清空预约记录
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}

//验证学号工号是否重复
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}

	return false;
}

//初始化容器
void Manager::initVector()
{
	vStu.clear();
	vTea.clear();
	//读取信息   学生、老师
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_Id&& ifs >> s.m_Name&&ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	//cout << "当前学生数量为：" << vStu.size() << endl;
	ifs.close();

	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_EmpId&& ifs >> t.m_Name&&ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	//cout << "当前教师数量为：" << vStu.size() << endl;
	ifs.close();
}