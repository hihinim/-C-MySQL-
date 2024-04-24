#pragma once
#include<mysql.h>
#include<vector>
#include<set>
#include<map>
#include<fstream>
#include"table.h"
using namespace std;
/*
	by ��ӡ������HelloWorld
*/
class DatabaseManager {
public:
	DatabaseManager();
	//�������ݿ�
	bool Connect(const char* server, const char* user, const char* password, const char* database, const char* charset = "gbk");
	//log
	void log(string content);
	//ִ��SQL���
	bool ExeSql(string sql);
	//��ȡ���ݿ����б�
	map<string, bool> GetTables();
	//��ʼ����
	void InitializeTbs();
	//�������ű�
	void CreateDepartmentTb();
	set<Department, Compare> GetDepartmentTb(string sqlStr= "select * from department;");
	//������ʦ&ѧ����
	void CreatePersonTb(int mode);
	set<Person, Compare> GetPersonTb(string sqlStr);
	//�����γ̱�
	void CreateCourseTb();
	set<Course, Compare> GetCourseTb(string sqlStr="select *form course;");
	//����ѡ�α�
	void CreateScTb();
	set<Sc, Compare> GetScTb(string sqlStr);
	MYSQL mydata;
	MYSQL_RES* result;//�����
};