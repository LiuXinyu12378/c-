#include"orderFile.h"

//构造函数
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date;
	string interval;
	string stuId;
	string stuName;
	string roomId;
	string status;

	this->m_Size = 0;

	while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId &&ifs>> status)
	{
		string key;
		string value;
		map<string, string>m;

		int pos = date.find(":");
		key = date.substr(0, pos);
		value = date.substr(pos + 1, date.size()-pos-1);
		m.insert(make_pair(key, value));

		pos = interval.find(":");
		key = interval.substr(0, pos);
		value = interval.substr(pos + 1, interval.size() - pos - 1);
		m.insert(make_pair(key, value));

		pos = stuId.find(":");
		key = stuId.substr(0, pos);
		value = stuId.substr(pos + 1, stuId.size() - pos - 1);
		m.insert(make_pair(key, value));

		pos = stuName.find(":");
		key = stuName.substr(0, pos);
		value = stuName.substr(pos + 1, stuName.size() - pos - 1);
		m.insert(make_pair(key, value));

		pos = roomId.find(":");
		key = roomId.substr(0, pos);
		value = roomId.substr(pos + 1, roomId.size() - pos - 1);
		m.insert(make_pair(key, value));

		pos = status.find(":");
		key = status.substr(0, pos);
		value = status.substr(pos + 1, status.size() - pos - 1);
		m.insert(make_pair(key, value));

		this->m_OrderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;
	}
	ifs.close();
}

//更新预约记录
void OrderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		return; //预约记录0条，直接return
	}

	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < this->m_Size; i++)
	{
		ofs << "data:" << this->m_OrderData[i]["date"] << " ";
		ofs << "interval:" << this->m_OrderData[i]["interval"] << " ";
		ofs << "stuId:" << this->m_OrderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_OrderData[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_OrderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_OrderData[i]["status"] << endl;
	}
	ofs.close();
}