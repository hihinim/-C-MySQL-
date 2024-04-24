#include"databaseManager.h"
DatabaseManager::DatabaseManager() {

}
bool DatabaseManager::Connect(const char* server, const char* user, const char* password, const char* database, const char* charset) {
		//初始化数据库
	if (mysql_library_init(0, NULL, NULL) == 0) {
		//cout << "mysql_library_init() succeed" << endl;
	}		
	else {
		//cout << "mysql_library_init() failed" << endl;
		return false;
	}
	//初始化数据结构
	if (mysql_init(&mydata) != NULL) {
		//cout << "mysql_init() succeed" << endl;
	}	
	else {
		//cout << "mysql_init() failed" << endl;
		return false;
	}
	//在连接数据库之前，设置额外的连接选项
	//可以设置的选项很多，这里设置字符集，否则无法处理中文
	if (mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, charset) == 0){
		//cout << "mysql_options() succeed" << endl;
	}
	else
	{
		//cout << "mysql_options() failed" << endl;
		return false;
	}
	//连接数据库
	if (mysql_real_connect(&mydata, server, user, password, database, 3306, NULL, 0) != NULL)	//这里的地址，用户名，密码，端口可以根据自己本地的情况更改
	{
		//cout << "mysql_real_connect() succeed" << endl;
	}
	else
	{
		//cout << "mysql_real_connect() failed: " << mysql_error(&mydata) << endl;
		return false;
	}
	return true;
}
void DatabaseManager::log(string content) {
	SYSTEMTIME time;
	GetLocalTime(&time);
	char arr[128];
	sprintf_s(arr, "%04d/%02d/%02d %02d:%02d:%02d\n  ", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	string str = arr + content+"  [succeed]\n";
	ofstream o("C:/edu/log.txt", ios::out|ios::app);
	if (o.is_open())
	{
		o << str;
	}
	o.close();
}
bool DatabaseManager::ExeSql(string sql) {
	log(sql);
	if (mysql_query(&mydata, sql.c_str()) == 0)
	{
		//cout << sql<<" succeed" << endl;
		result=mysql_store_result(&mydata);
		//system("pause");
		return true;
	}
	else
	{
		//cout << sql<<" failed" << endl;
		mysql_close(&mydata);
		//system("pause");
		return false;
	}
}
map<string, bool> DatabaseManager::GetTables() {
	map<string, bool> m;
	m.insert(pair<string, bool>("teacher", false));
	m.insert(pair<string, bool>("student", false));
	m.insert(pair<string, bool>("department", false));
	m.insert(pair<string, bool>("course", false));
	m.insert(pair<string, bool>("sc", false));
	if (ExeSql("show tables")) {
		unsigned int fieldcount = mysql_num_fields(result);
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);		
		while (NULL != row)
		{		
			for (int i = 0; i < fieldcount; i++) {
				if (row[i] != NULL) {
					if (m[row[i]] == false) {
						m[row[i]] = true;
					}
				}
			}
			row = mysql_fetch_row(result);
		}	
	}
	return m;
}
//初始化所有表
void DatabaseManager::InitializeTbs() {
	map<string, bool> m = GetTables();
	if (m["department"] == false) {
		CreateDepartmentTb();
	}
	if (m["teacher"] == false) {
		CreatePersonTb(0);
	}
	if (m["student"] == false) {
		CreatePersonTb(1);
	}
	if (m["course"] == false) {
		CreateCourseTb();
	}
	if (m["sc"] == false) {
		CreateScTb();
	}
}
void DatabaseManager::CreateDepartmentTb() {
	string str = "create table department(dno varchar(10) primary key,name varchar(10) not null);";
	ExeSql(str);
	str = "insert into department values('1','计算机科学与技术'),('2','土木工程'),('3','市场营销'),('4','物流管理'),('5','人工智能');";
	ExeSql(str);
}
set<Department, Compare> DatabaseManager::GetDepartmentTb(string sqlStr) {
	set<Department, Compare> s;
	if (ExeSql(sqlStr)) {
		unsigned int fieldcount = mysql_num_fields(result);
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);		
		while (NULL != row)
		{
			string arr[4] = {};
			for (int i = 0; i < fieldcount; i++) {
				if (row[i] != NULL) {
					arr[i] = row[i];
				}
			}
			s.insert(Department(arr[0], arr[1]));
			row = mysql_fetch_row(result);
		}
	}
	return s;
}
void DatabaseManager::CreatePersonTb(int mode) {
	char temp[] = "create table %s(no varchar(20) primary key,name varchar(10) not null,sex char(1),age char(4),dno varchar(10) not null,password varchar(20) not null,foreign key(dno) references department(dno) on delete cascade on update cascade);";
	char str[1024];
	if (mode == 0) {
		sprintf_s(str, temp, "teacher");
	}
	else if (mode == 1) {
		sprintf_s(str, temp, "student");
	}
	ExeSql(str);
}
set<Person, Compare> DatabaseManager::GetPersonTb(string sqlStr) {
	set<Person, Compare> s;
	if (ExeSql(sqlStr)) {
		unsigned int fieldcount = mysql_num_fields(result);
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);		
		while (NULL != row)
		{
			string arr[6] = {};
			for (int i = 0; i < fieldcount; i++) {
				if (row[i] != NULL) {
					arr[i] = row[i];
				}
			}
			s.insert(Person(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]));
			row = mysql_fetch_row(result);
		}		
	}
	return s;
}
void DatabaseManager::CreateCourseTb() {
	string str = "create table course(cno varchar(10) primary key,name varchar(10) not null,tno varchar(10),foreign key(tno) references teacher(no) on delete cascade on update cascade);";
	ExeSql(str);
}
set<Course, Compare> DatabaseManager::GetCourseTb(string sqlStr) {
	set<Course, Compare> s;
	if (ExeSql(sqlStr)) {
		unsigned int fieldcount = mysql_num_fields(result);
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);
		while (NULL != row)
		{
			string arr[4] = {};
			for (int i = 0; i < fieldcount; i++) {
				if (row[i] != NULL) {
					arr[i] = row[i];
				}
			}
			s.insert(Course(arr[0], arr[1], arr[2]));
			row = mysql_fetch_row(result);
		}
	}
	return s;
}
void DatabaseManager::CreateScTb() {
	string str = "create table sc(sno varchar(10),cno varchar(10),score char(4),primary key(sno,cno),foreign key(sno) references student(no) on delete cascade on update cascade,foreign key(cno) references course(cno) on delete cascade on update cascade);";
	ExeSql(str);
}
set<Sc, Compare> DatabaseManager::GetScTb(string sqlStr) {
	set<Sc, Compare> s;
	if (ExeSql(sqlStr)) {
		unsigned int fieldcount = mysql_num_fields(result);
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);
		while (NULL != row)
		{
			string arr[3] = {};
			for (int i = 0; i < fieldcount; i++) {
				if (row[i] != NULL) {
					arr[i] = row[i];
				}
			}
			s.insert(Sc(arr[0], arr[1] ,arr[2]));
			row = mysql_fetch_row(result);
		}
	}
	return s;
}