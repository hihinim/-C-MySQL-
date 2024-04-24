#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<conio.h>
#include<windows.h>
#include<io.h>
#include"databaseManager.h"
using namespace std;
/*
	by 打印两年半的HelloWorld
*/
class Console {
public:
	Console();
	bool ConnectDatabase();
	void WriteRecord();
	void SetCursor(int x, int y, bool visible=false);
	void ArrowsMove(int x, int y, int low, int high, vector<char> operand = {});
	void Input(string& str);
	bool Alert(string content);
	void LoadinPage();
	void Control();
	bool SignIn();
	void MainPage();
	void InfoPage(string title, string no="", string name="", string sex="", string age="", string dname="", string password="");
	Department ChoiceDepartment();
	void AddTeacherInfo();
	void DeleteTeacherInfo();
	void Config();
	void ManageStudent();
	void ManageCourse();
	void ChoiceCourse();
	void AddStudentInfo();
	void SearchStudentInfo();
	void ModifyStudentInfo(Person& p);
	void DeleteStudentInfo(Person& p);
	Person ChoiceTeacher();
	void CourseInfoPage(string title,string cno="",string name="",string tname="");
	void AddCourseInfo();
	void ShowCourseAllStudent(Course& c);
	void DeleteStudentCourse(Person& p, Course& c);
	void DeleteCourse(Course& c);
	COORD pos;
	CONSOLE_CURSOR_INFO cci;
	char operand;//操作符
	string account;
	string password;
	int mode=1;
	DatabaseManager data;
	string server= "localhost";
	string user = "root";
	string Dpassword = "123456";
	string database = "edu";
	string charset = "GBK";
	char sqlStr[1024];
	string type[2] = { "教职工","学生" };
	set<Person, Compare> st;
	set<Person, Compare> te;
	set<Department, Compare> de;
	set<Course, Compare> co;
	set<Sc, Compare> sc;
};