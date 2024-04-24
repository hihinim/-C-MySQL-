#include<iostream>
#include"table.h"
using namespace std;
Base::Base() {

}
Base::Base(string number,string name) {
	this->number = number;
	this->name = name;
}
void Base::SetNumber(string number) {
	this->number = number;
}
string Base::GetNumber() {
	return this->number;
}
void Base::SetName(string name) {
	this->name = name;
}
string Base::GetName() {
	return this->name;
}
Person::Person() {

}
Person::Person(string number, string name, string sex, string age, string dname, string password) :Base(number, name) {
	this->sex = sex;
	this->age = age;
	this->dname = dname;
	this->password = password;
}
void Person::SetSex(string sex) {
	this->sex = sex;
}
string Person::GetSex() {
	return this->sex;
}
void Person::SetAge(string age) {
	this->age = age;
}
string Person::GetAge() {
	return this->age;
}
void Person::SetDname(string dname) {
	this->dname = dname;
}
string Person::GetDname() {
	return this->dname;
}
void Person::SetPassword(string password) {
	this->password = password;
}
string Person::GetPassword() {
	return this->password;
}
Course::Course() {

}
Course::Course(string number, string cname, string tname) :Base(number, cname) {
	this->tname = tname;
}
void Course::SetTname(string tname) {
	this->tname = tname;
}
string Course::GetTname() {
	return this->tname;
}
Department::Department() {

}
Department::Department(string number, string name) :Base(number, name) {

}
Sc::Sc() {

}
Sc::Sc(string sno, string cno, string score) {
	this->sno = sno;
	this->cno = cno;
	this->score = score;
}
void Sc::SetSno(string sno) {
	this->sno = sno;
}
string Sc::GetSno() {
	return this->sno;
}
void Sc::SetCno(string cno) {
	this->cno = cno;
}
string Sc::GetCno() {
	return this->cno;
}
void Sc::SetScore(string score) {
	this->score = score;
}
string Sc::GetScore() {
	return this->score;
}