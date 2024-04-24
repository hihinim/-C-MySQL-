#pragma once
#include<mysql.h>
#include<vector>
#include<set>
#include<map>
#include<fstream>
#include"table.h"
using namespace std;
/*
	by 打印两年半的HelloWorld
*/
class DatabaseManager {
public:
	DatabaseManager();
	//连接数据库
	bool Connect(const char* server, const char* user, const char* password, const char* database, const char* charset = "gbk");
	//log
	void log(string content);
	//执行SQL语句
	bool ExeSql(string sql);
	//获取数据库所有表
	map<string, bool> GetTables();
	//初始化表
	void InitializeTbs();
	//创建部门表
	void CreateDepartmentTb();
	set<Department, Compare> GetDepartmentTb(string sqlStr= "select * from department;");
	//创建教师&学生表
	void CreatePersonTb(int mode);
	set<Person, Compare> GetPersonTb(string sqlStr);
	//创建课程表
	void CreateCourseTb();
	set<Course, Compare> GetCourseTb(string sqlStr="select *form course;");
	//创建选课表
	void CreateScTb();
	set<Sc, Compare> GetScTb(string sqlStr);
	MYSQL mydata;
	MYSQL_RES* result;//结果集
};