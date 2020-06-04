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

//�˵�����
void Manager::operMenu()
{
	cout << "��ӭ����Ա��" << this->m_Name << endl;
	cout << "\t\t-----------------------------------------" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|             1.����˺�                |" << endl;
	cout << "\t\t|             2.�鿴�˺�                |" << endl;
	cout << "\t\t|             3.�鿴����                |" << endl;
	cout << "\t\t|             4.���ԤԼ                |" << endl;
	cout << "\t\t|             0.ע����¼                |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t-----------------------------------------" << endl;
	cout << "���������ѡ��" << endl;
}

//����˺�
void Manager::addPerson()
{
	cout << "����������˺�����" << endl;
	cout << "1.���ѧ��" << endl;
	cout << "2.�����ʦ" << endl;
	cout << "0.�˳�" << endl;

	string fileName; //�����ļ���
	string tip;  //��ʾid��
	string errorTip;

	ofstream ofs; //�ļ���������

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		fileName = STUDENT_FILE;
		tip = "������ѧ�ţ�";
		errorTip = "��ѧ���Ѿ�ʹ�ã�";
	}
	else if (select == 2)
	{
		fileName = TEACHER_FILE;
		tip = "������ְ����ţ�";
		errorTip = "�˹����Ѿ�ʹ�ã�";
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
		if (ret) //���ظ�
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}

	cout << "������������" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << endl;
	cout << "��ӳɹ���" << endl;
	system("pause");
	system("cls");

	ofs.close();

	initVector();
}

//�鿴�˺�
void Manager::showPerson()
{
	initVector();
	cout << "��ѡ��Ҫ���ҵ�����" << endl;
	cout << "1.ѧ��" << endl;
	cout << "2.��ʦ" << endl;
	cout << "0.�˳�" << endl;
	cout << "���������ѡ��";
	int select = 0;

	cin >> select;
	if (select == 1)
	{
		cout << "ѧ����Ϣ���£�" << endl;
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			cout << "ѧ�ţ�" << it->m_Id << " ������" << it->m_Name << " ���룺"<<it->m_Pwd<<endl;
		}
	}
	else if (select == 2)
	{
		cout << "��ʦ��Ϣ���£�" << endl;
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			cout << "���ţ�" << it->m_EmpId << " ������" << it->m_Name <<" ���룺"<<it->m_Pwd<<endl;
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

//�鿴������Ϣ
void Manager::showComputer()
{
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "������ţ�" << it->m_ComId << " ����������" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

//���ԤԼ��¼
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "��ճɹ���" << endl;
	system("pause");
	system("cls");
}

//��֤ѧ�Ź����Ƿ��ظ�
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

//��ʼ������
void Manager::initVector()
{
	vStu.clear();
	vTea.clear();
	//��ȡ��Ϣ   ѧ������ʦ
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_Id&& ifs >> s.m_Name&&ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	//cout << "��ǰѧ������Ϊ��" << vStu.size() << endl;
	ifs.close();

	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_EmpId&& ifs >> t.m_Name&&ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	//cout << "��ǰ��ʦ����Ϊ��" << vStu.size() << endl;
	ifs.close();
}