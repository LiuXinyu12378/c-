#pragma once
#include<iostream>
using namespace std;
#include"identity.h"


//教师类设计
class Teacher :public Identity
{
public:

	Teacher();

	Teacher(int empId, string name, string pwd);

	//菜单界面
	void operMenu();

	//查看所有预约
	void showAllOrder();

	//审核预约
	void validOrder();

	//职工号
	int m_EmpId;


};