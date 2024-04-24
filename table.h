#pragma once
#include<iostream>
#include<string>
using namespace std;
/*
	by 打印两年半的HelloWorld
*/
class Base {
public:
	Base();
	Base(string number,string name);
	void SetNumber(string number);
	string GetNumber();
	void SetName(string name);
	string GetName();
protected:
	string number;
	string name;
};

class Person:public Base{
public:
	Person();
	Person(string number, string name, string sex, string age, string dname, string password);
	void SetSex(string sex);
	string GetSex();
	void SetAge(string age);
	string GetAge();
	void SetDname(string dname);
	string GetDname();
	void SetPassword(string password);
	string GetPassword();
protected:	
	string sex;
	string age;
	string dname;
	string password;
};

class Course:public Base{
public:
	Course();
	Course(string number, string cname, string tname);
	void SetTname(string tname);
	string GetTname();
	bool status;//选课状态
private:
	string tname;
	
};

class Department:public Base {
public:
	Department();
	Department(string number, string name);
};

class Sc {
public:
	Sc();
	Sc(string sno, string cno, string score);
	void SetSno(string sno);
	string GetSno();
	void SetCno(string cno);
	string GetCno();
	void SetScore(string score);
	string GetScore();
protected:
	string sno;
	string cno;
	string score;
};

class Compare {
public:
	bool operator()(Department t1, Department t2) const{
		return t1.GetNumber().compare(t2.GetNumber()) < 0;
	}
	bool operator()(Person t1, Person t2) const {
		return t1.GetNumber().compare(t2.GetNumber()) < 0;
	}
	bool operator()(Course t1, Course t2) const {
		return t1.GetNumber().compare(t2.GetNumber()) < 0;
	}
	bool operator()(Sc t1, Sc t2) const {
		return t1.GetCno().compare(t2.GetCno()) < 0;
	}
};