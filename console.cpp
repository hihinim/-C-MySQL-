#include"console.h"
//Console构造函数
Console::Console() {
    system("title 教务管理系统");
    string path = R"(C:\edu)";
    if (access(path.data(), 0) == -1)
    {
        system(("mkdir " + path).data());
    }
    else
    {
        string path = R"(C:\edu\record.txt)";
        ifstream i(path, ios::in);
        if (i.is_open())
        {
            getline(i, account);
            getline(i, password);
            getline(i, server);
            getline(i, user);
            getline(i, Dpassword);
            getline(i, database);
            getline(i, charset);
        }
        i.close();
    }
    if (ConnectDatabase()) {
        de = data.GetDepartmentTb();
        Control();
    }
}
//写出记录
void Console::WriteRecord() {
    ofstream o("C:/edu/record.txt", ios::out);
    if (o.is_open())
    {
        o << account << "\n" << password << "\n" << server << "\n" << user << "\n" << Dpassword << "\n" << database << "\n" << charset;
    }
    o.close();
}
//连接数据库
bool Console::ConnectDatabase() {
    if (data.Connect(server.c_str(), user.c_str(), Dpassword.c_str(), database.c_str(), charset.c_str())) {
        //cout << "连接数据库成功!" << endl;
        data.InitializeTbs();
        return true;
    }
    else
    {
        if (Alert("连接数据库失败!\n\t\t是否打开数据库配置信息")) {
            Config();
            ConnectDatabase();
        }
        else {
            exit(1);
        }
    }
}
//设置光标位置和隐藏状态
void Console::SetCursor(int x, int y, bool visible)
{
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    cci.dwSize = sizeof(cci);
    cci.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}
//移动箭头
void Console::ArrowsMove(int x, int y, int low, int high, vector<char> operand)
{
    SetCursor(x, y);
    cout << "->";//在光标处输出
    while (true)
    {
        if (kbhit())
        {
            char c = getch();
            if (c == 13)
            {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                cout << "  ";
                this->operand = c;
                return;
            }
            else if (c == 'w')
            {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                cout << "  ";
                if (pos.Y > low)
                {
                    pos.Y--;
                }
                else
                {
                    if (low != high) {
                        pos.Y = high;
                    }                  
                }
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                cout << "->";
            }
            else if (c == 's')
            {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                cout << "  ";
                if (pos.Y < high)
                {
                    pos.Y++;
                }
                else
                {
                    if (low != high) {
                        pos.Y = low;
                    }
                }
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                cout << "->";
            }
            else if (c == 27)
            {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                cout << "  ";
                this->operand = c;
                return;
            }
            for (int i = 0; i < operand.size(); i++)
            {
                if (c == operand[i])
                {
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                    cout << "  ";
                    this->operand = operand[i];
                    return;
                }
            }
        }
    }
}
//输入数据
void Console::Input(string&str) {
    SetCursor(25, pos.Y, true);
    cout << "                                           ";
    SetCursor(25, pos.Y, true);
    cin >> str;
}
//弹窗页面
bool Console::Alert(string content)
{
    system("cls");
    cout << endl;
    cout << "        ******************************************" << endl;
    cout << "                " << endl << endl;
    cout << "                " << content << endl;
    cout << endl << endl;
    cout << "        ******************************************" << endl;
    cout << "            " << "操作说明：" << endl;
    cout << "              " << "ESC:返回" << endl;
    cout << "              " << "ENTER:确认" << endl;
    while (true)
    {
        if (kbhit())
        {
            char c = getch();
            if (c == 13)
            {
                system("cls");
                return true;
            }
            else if (c == 27)
            {
                system("cls");
                return false;
            }
        }
    }
}
//登录页面
void Console::LoadinPage() {
    system("cls");
    cout << endl;
    cout << "        ******************************************" << endl;
    cout << "                   【教务管理系统】" << endl;
    cout << "                      $登录页面$" << endl;
    cout << "        ------------------------------------------" << endl;
    cout << "                   账号："+account  << endl;
    cout << "                   密码："+password  << endl;
    cout << "                       <登录>" << endl;
    cout << "                     <教职工注册>" << endl;
    cout << "                     <数据库配置>" << endl;
    cout << "                      <退出程序>" << endl;
    cout << "        ******************************************" << endl;
    cout << "            " << "操作说明：" << endl;
    cout << "\t\t" << "w:上移" << endl;
    cout << "\t\t" << "s:下移" << endl;
    cout << "\t\t" << "ESC:退出" << endl;
    cout << "\t\t" << "ENTER:确认" << endl;
    SetCursor(16, 5);
}
//控制台
void Console::Control()
{
    LoadinPage();
    while (true)
    {
        ArrowsMove(16, pos.Y, 5, 10);
        if (operand == 27)
        {
            exit(1);
        }
        else if (pos.Y == 5)
        {
            Input(account);
        }
        else if (pos.Y == 6)
        {
            Input(password);
        }
        else if (pos.Y == 7)
        {
            if (SignIn())
            {
                WriteRecord();
                MainPage();
            }
            LoadinPage();
        }
        else if (pos.Y == 8)
        {
            AddTeacherInfo();
            LoadinPage();
        }
        else if (pos.Y == 9)
        {
            Config();
            ConnectDatabase();
            LoadinPage();
        }
        else if (pos.Y == 10)
        {
            exit(1);
        }
    }
}
//登录判断
bool Console::SignIn() {
    char temp[]="select * from %s where no='%s' and password='%s';";
    sprintf_s(sqlStr, temp, "teacher", account.c_str(), password.c_str());
    //cout << sqlStr << endl;
    //system("pause");
    if (data.ExeSql(sqlStr) && mysql_num_rows(data.result) == 1) {
        Alert(type[0]+" 登录成功！");
        mode = 0;
        return true;
    }
    else
    {
        sprintf_s(sqlStr, temp, "student", account.c_str(), password.c_str());
        //cout << sqlStr << endl;
        //system("pause");
        if (data.ExeSql(sqlStr) && mysql_num_rows(data.result) == 1) {
            Alert(type[1]+" 登录成功！");
            mode = 1;
            return true;
        }
        else {
            Alert("账号不存在或密码错误");
            return false;
        }
    }
    return false;
}
//主页面
void Console::MainPage() {
    if (mode == 0) {
        int last = 4;
        while (true)
        {
            system("cls");
            cout << "        欢迎！" + type[mode] + "：" << account << endl;
            cout << "      ********************************************" << endl;
            cout << "                   【教务管理系统】" << endl;
            cout << "      ********************************************" << endl;
            cout << "                      管理课程" << endl;
            cout << "                      管理学生" << endl;
            cout << "                      注销当前职工" << endl;
            cout << "      ********************************************" << endl;
            cout << "            " << "操作说明：" << endl;
            cout << "\t\t" << "w:上移" << endl;
            cout << "\t\t" << "s:下移" << endl;
            cout << "\t\t" << "ESC:退出登录" << endl;
            cout << "\t\t" << "ENTER:确认" << endl;
            ArrowsMove(18, last, 4, 6);
            last = pos.Y;
            if (operand == 27) {
                if (Alert("是否退出登录？")) {
                    system("cls");
                    return;
                }
            }
            else if (operand == 13) {
                if (pos.Y == 4) {
                    ManageCourse();
                }
                else if(pos.Y == 5) {
                    ManageStudent();
                }
                else if (pos.Y == 6) {
                    DeleteTeacherInfo();
                    account = "";
                    password = "";
                    return;
                }
            }
        }
    }
    else {
        ChoiceCourse();
    }
}
//用户信息页面
void Console::InfoPage(string title, string no, string name, string sex, string age, string dname, string password) {
    system("cls");
    string label = (mode == 0) ? "学" : "工";
    cout << endl;
    cout << "        ******************************************" << endl;
    cout << "                   【教务管理系统】" << endl;
    cout << "                   $" + title + "信息$" << endl;
    cout << "        ------------------------------------------" << endl;
    cout << "                   " + label + "号：" + no << endl;
    cout << "                   姓名：" + name << endl;
    cout << "                   性别：" + sex << endl;
    cout << "                   年龄：" + age << endl;
    cout << "                   部门：" + dname << endl;
    cout << "                   密码：" + password << endl;
    cout << "                      <" + title + ">" << endl;
    cout << "        ******************************************" << endl;
    cout << "            " << "操作说明：" << endl;
    cout << "\t\t" << "w:上移" << endl;
    cout << "\t\t" << "s:下移" << endl;
    cout << "\t\t" << "ESC:返回" << endl;
    cout << "\t\t" << "ENTER:确认" << endl;
    SetCursor(pos.X, 5);
}
//选择部门
Department Console::ChoiceDepartment() {
    vector<Department> v;
    system("cls");
    cout << endl;
    cout << "        ******************************************" << endl;
    cout << "                   【教务管理系统】" << endl;
    cout << "                      $选择部门$" << endl;
    cout << "        ------------------------------------------" << endl;
    for (set<Department, Compare>::iterator it = de.begin(); it != de.end(); it++) {
        Department d(*it);
        v.push_back(d);
        cout << "\t\t  " + d.GetName() << endl;
    }
    cout << "        ******************************************" << endl;
    cout << "            " << "操作说明：" << endl;
    cout << "\t\t" << "w:上移" << endl;
    cout << "\t\t" << "s:下移" << endl;
    cout << "\t\t" << "ESC:返回" << endl;
    cout << "\t\t" << "ENTER:确认" << endl;
    SetCursor(16, 5);
    while (true)
    {
        ArrowsMove(16, pos.Y, 5, 4 + de.size());
        if (operand == 27)
        {
            return Department();
        }
        else if (operand == 13)
        {
            return v[pos.Y - 5];
        }
    }
}
//添加职工信息
void Console::AddTeacherInfo() {
    string no, name, sex, age, dno, dname, password;
    InfoPage("添加职工");
    while (true)
    {
        ArrowsMove(16, pos.Y, 5, 11);
        if (operand == 27)
        {
            return;
        }
        else if (pos.Y == 5)
        {
            Input(no);
        }
        else if (pos.Y == 6)
        {
            Input(name);
        }
        else if (pos.Y == 7)
        {
            Input(sex);
        }
        else if (pos.Y == 8)
        {
            Input(age);
        }
        else if (pos.Y == 9)
        {
            Department d = ChoiceDepartment();
            dno = d.GetNumber();
            dname = d.GetName();
            InfoPage("添加职工", no, name, sex, age, dname, password);
        }
        else if (pos.Y == 10)
        {
            Input(password);
        }
        else if (pos.Y == 11) {
            if (no == "") {
                Alert("工号不能为空");
            }
            else if (name == "") {
                Alert("姓名不能为空");
            }
            else if (dname == "") {
                Alert("部门不能为空");
            }
            else if (password == "") {
                Alert("密码不能为空");
            }
            else {
                char str[] = "insert into teacher values('%s','%s','%s','%s','%s','%s');";
                sprintf_s(sqlStr, str, no.c_str(), name.c_str(), sex.c_str(), age.c_str(), dno.c_str(), password.c_str());
                //cout << sqlStr << endl;
                //system("pause");
                if (data.ExeSql(sqlStr)) {
                    te.insert(Person(no, name, sex, age, dname, password));
                    Alert("添加成功！");
                    return;
                }
                else {
                    Alert("工号重复");
                }
            }
            InfoPage("添加职工", no, name, sex, age, dname, password);
        }
    }
}
//删除职工信息
void Console::DeleteTeacherInfo() {
    if (Alert("确认注销工号‘" + account + "’的职工？")) {
        char str[] = "delete from teacher where no='%s';";
        sprintf_s(sqlStr, str, account);
        if (data.ExeSql(sqlStr)) {
            Alert("注销成功!");
        }
    }
}
//数据库配置
void Console::Config() {
    system("cls");
    cout << endl;
    cout << "        ******************************************" << endl;
    cout << "                   【教务管理系统】" << endl;
    cout << "                     $数据库设置$" << endl;
    cout << "        ------------------------------------------" << endl;
    cout << "                  server:" + server << endl;
    cout << "                    user:" + user << endl;
    cout << "                password:" + Dpassword << endl;
    cout << "                database:" + database << endl;
    cout << "                 charset:" + charset << endl;
    cout << "                       <确定>" << endl;
    cout << "        ******************************************" << endl;
    cout << "            " << "操作说明：" << endl;
    cout << "\t\t" << "w:上移" << endl;
    cout << "\t\t" << "s:下移" << endl;
    cout << "\t\t" << "ESC:返回" << endl;
    cout << "\t\t" << "ENTER:确认" << endl;
    SetCursor(16, 5);
    while (true)
    {
        ArrowsMove(14, pos.Y, 5, 10);
        if (operand == 27)
        {
            return;
        }
        else if (pos.Y == 5)
        {
            Input(server);
        }
        else if (pos.Y == 6)
        {
            Input(user);
        }
        else if (pos.Y == 7)
        {
            Input(Dpassword);
        }
        else if (pos.Y == 8)
        {
            Input(database);
        }
        else if (pos.Y == 9)
        {
            Input(charset);
        }
        else if (pos.Y==10){
            WriteRecord();
            return;
        }
    }
}
//管理课程页面
void Console::ManageCourse() {
    vector<char> vc = { 'a','d' };
    int last = 6;
    te = data.GetPersonTb("select no,t.name,sex,age,d.name,password from teacher t,department d where t.dno=d.dno;");
    co = data.GetCourseTb("select cno,c.name,t.name from course c,teacher t where c.tno=t.no;");
    while (true)
    {
        vector<Course> v;
        system("cls");
        cout << "        欢迎！" + type[mode] + "：" << account << endl;
        cout << "      ********************************************" << endl;
        cout << "                   【教务管理系统】" << endl;
        cout << "      ********************************************" << endl;
        cout << "\t课程号\t课程名\t任课教师" << endl;
        cout << "      --------------------------------------------" << endl;
        if (co.size() == 0) {
            cout << "\t暂无课程" << endl;
        }
        else {
            for (set<Course, Compare>::iterator it = co.begin(); it != co.end(); it++) {
                Course c(*it);
                v.push_back(c);
                cout << "\t" + c.GetNumber() + "\t" + c.GetName() + "\t" + c.GetTname() << endl;
            }
        }       
        cout << "      ********************************************" << endl;
        cout << "            " << "操作说明：" << endl;
        cout << "\t\t" << "w:上移" << endl;
        cout << "\t\t" << "s:下移" << endl;
        cout << "\t\t" << "ESC:退出登录" << endl;
        cout << "\t\t" << "ENTER:查看选课所有学生" << endl;
        cout << "\t\t" << "a:添加课程" << endl;
        cout << "\t\t" << "d:删除课程" << endl;
        ArrowsMove(6, last, 6, 5 + (co.size() ? co.size() : 1), vc);
        last = pos.Y;
        if (operand == 27) {
            return;
        }
        else if (operand == vc[0]) {
            AddCourseInfo();
            last = 6;
        }  
        else if (co.size() > 0) {
            if (operand == 13) {
                ShowCourseAllStudent(v[pos.Y - 6]);
            }
            else if (operand == vc[1]) {
                DeleteCourse(v[pos.Y - 6]);
            }
            last = 6;
        }
    }
}
//课程信息页面
void Console::CourseInfoPage(string title,string cno,string name,string tname) {
    system("cls");
    cout << endl;
    cout << "        ******************************************" << endl;
    cout << "                   【教务管理系统】" << endl;
    cout << "                   $" + title + "信息$" << endl;
    cout << "        ------------------------------------------" << endl;
    cout << "                 课程号：" + cno << endl;
    cout << "                 课程名：" + name << endl;
    cout << "               任课教师：" + tname << endl;
    cout << "                      <" + title + ">" << endl;
    cout << "        ******************************************" << endl;
    cout << "            " << "操作说明：" << endl;
    cout << "\t\t" << "w:上移" << endl;
    cout << "\t\t" << "s:下移" << endl;
    cout << "\t\t" << "ESC:返回" << endl;
    cout << "\t\t" << "ENTER:确认" << endl;
    SetCursor(pos.X, 5);
}
//选择任课教师
Person Console::ChoiceTeacher() {
    vector<Person> v;
    system("cls");
    cout << endl;
    cout << "        ******************************************" << endl;
    cout << "                   【教务管理系统】" << endl;
    cout << "                    $选择任课教师$" << endl;
    cout << "        ------------------------------------------" << endl;
    for (set<Person, Compare>::iterator it = te.begin(); it != te.end(); it++) {
        Person p(*it);
        v.push_back(p);
        cout << "\t\t\t" + p.GetName() << endl;
    }
    cout << "        ******************************************" << endl;
    cout << "            " << "操作说明：" << endl;
    cout << "\t\t" << "w:上移" << endl;
    cout << "\t\t" << "s:下移" << endl;
    cout << "\t\t" << "ESC:返回" << endl;
    cout << "\t\t" << "ENTER:确认" << endl;
    SetCursor(16, 5);
    while (true)
    {
        ArrowsMove(16, pos.Y, 5, 4 + te.size());
        if (operand == 27)
        {
            return Person();
        }
        else if (operand == 13)
        {
            return v[pos.Y - 5];
        }
    }
}
//添加课程信息
void Console::AddCourseInfo() {
    string cno, name, tno,tname;
    CourseInfoPage("添加课程");
    while (true)
    {
        ArrowsMove(13, pos.Y, 5, 8);
        if (operand == 27)
        {
            return;
        }
        else if (pos.Y == 5)
        {
            Input(cno);
        }
        else if (pos.Y == 6)
        {
            Input(name);
        }
        else if (pos.Y == 7)
        {
            Person p = ChoiceTeacher();
            tno = p.GetNumber();
            tname = p.GetName();
            CourseInfoPage("添加课程", cno, name, tname);
        }
        else if (pos.Y == 8) {
            if (cno == "") {
                Alert("课程号不能为空");
            }
            else if (name == "") {
                Alert("课程名不能为空");
            }
            else if (tname == "") {
                Alert("任课教师不能为空");
            }
            else {
                char str[] = "insert into course values('%s','%s','%s');";
                sprintf_s(sqlStr, str, cno.c_str(), name.c_str(), tno.c_str());
                //cout << sqlStr << endl;
                //system("pause");
                if (data.ExeSql(sqlStr)) {
                    co.insert(Course(cno, name, tname));
                    Alert("添加成功！");
                    return;
                }
                else {
                    Alert("课程号重复");
                }
            }
            CourseInfoPage("添加课程", cno, name, tname);
        }
    }
}
//查看所有选课的学生
void Console::ShowCourseAllStudent(Course& c) {
    vector<char> vc = {'d'};
    int last = 6;
    data.ExeSql("create view stc(no,name,sex,age,dno) as select no,s.name,sex,age,dno from student s,sc c where s.no=c.sno and cno='"+c.GetNumber()+"';");
    st = data.GetPersonTb("select no,s.name,sex,age,d.name from stc s,department d where s.dno=d.dno;");
    data.ExeSql("drop view stc;");
    while (true)
    {
        vector<Person> v;
        system("cls");
        cout << "        欢迎！" + type[mode] + "：" << account << endl;
        cout << "      ********************************************" << endl;
        cout << "                   【教务管理系统】" << endl;
        cout << "      ********************************************" << endl;
        cout << "\t学号\t姓名\t性别\t年龄\t部门" << endl;
        cout << "      --------------------------------------------" << endl;
        if (st.size() == 0) {
            cout << "\t暂无学生选课" << endl;
        }
        else {
            for (set<Person, Compare>::iterator it = st.begin(); it != st.end(); it++) {
                Person p(*it);
                v.push_back(p);
                cout << "\t" + p.GetNumber() + "\t" + p.GetName() + "\t" + p.GetSex() + "\t" + p.GetAge() + "\t" + p.GetDname() << endl;
            }
        }
        cout << "      ********************************************" << endl;
        cout << "            " << "操作说明：" << endl;
        cout << "\t\t" << "w:上移" << endl;
        cout << "\t\t" << "s:下移" << endl;
        cout << "\t\t" << "ESC:返回" << endl;
        cout << "\t\t" << "d:删除学生选课" << endl;
        ArrowsMove(6, last, 6, 5 + (st.size() ? st.size() : 1), vc);
        last = pos.Y;
        if (operand == 27) {
            return;
        }
        else if (st.size() > 0) {
            if (operand == vc[0]) {
                DeleteStudentCourse(v[pos.Y - 6], c);
            }
        }
    }
}
//删除选课的学生
void Console::DeleteStudentCourse(Person& p, Course& c) {
    string no = p.GetNumber();
    if (Alert("确认删除选择‘"+c.GetName()+"’课程的\n\t\t‘" + no + "’号的学生？")) {
        char str[] = "delete from sc where sno='%s';";
        sprintf_s(sqlStr, str, no.c_str());
        if (data.ExeSql(sqlStr)) {
            st.erase(p);
            Alert("删除成功!");
        }
    }
}
//删除课程
void Console::DeleteCourse(Course& c) {
    string cno = c.GetNumber();
    if (Alert("确认删除课程号‘" + cno + "’的课程？")) {
        char str[] = "delete from course where cno='%s';";
        sprintf_s(sqlStr, str, cno.c_str());
        //cout << sqlStr << endl;
        //system("pause");
        if (data.ExeSql(sqlStr)) {
            co.erase(c);
            Alert("删除成功!");
        }
    }
}
//管理学生页面
void Console::ManageStudent() {
    vector<char> vc = { 'a','f','d' };
    int last = 6;
    st = data.GetPersonTb("select no,s.name,sex,age,d.name,password from student s,department d where s.dno=d.dno;");
    while (true)
    {
        vector<Person> v;
        system("cls");
        cout << "        欢迎！" + type[mode] + "：" << account << endl;
        cout << "      ********************************************" << endl;
        cout << "                   【教务管理系统】" << endl;
        cout << "      ********************************************" << endl;
        cout << "\t学号\t姓名\t性别\t年龄\t部门" << endl;
        cout << "      --------------------------------------------" << endl;
        if (st.size() == 0) {
            cout << "\t暂无学生" << endl;
        }
        else {
            for (set<Person, Compare>::iterator it = st.begin(); it != st.end(); it++) {
                Person p(*it);
                v.push_back(p);
                cout << "\t" + p.GetNumber() + "\t" + p.GetName() + "\t" + p.GetSex() + "\t" + p.GetAge() + "\t" + p.GetDname() << endl;
            }
        }
        cout << "      ********************************************" << endl;
        cout << "            " << "操作说明：" << endl;
        cout << "\t\t" << "w:上移" << endl;
        cout << "\t\t" << "s:下移" << endl;
        cout << "\t\t" << "ESC:返回" << endl;
        cout << "\t\t" << "ENTER:修改学生信息" << endl;
        cout << "\t\t" << "a:添加学生信息" << endl;
        cout << "\t\t" << "f:查询学生信息" << endl;
        cout << "\t\t" << "d:删除学生信息" << endl;
        ArrowsMove(6, last, 6, 5 + (st.size() ? st.size() : 1), vc);
        last = pos.Y;
        if (operand == 27) {
            return;
        }
        else if (operand == vc[0]) {
            AddStudentInfo();
            last = 6;
        }
        else if (st.size() > 0) {
            if (operand == 13) {
                ModifyStudentInfo(v[pos.Y - 6]);
            }
            else if (operand == vc[1]) {
                SearchStudentInfo();
                last = 6;
            }
            else if (operand == vc[2]) {
                DeleteStudentInfo(v[pos.Y - 6]);
                last = 6;
            }
        }

    }
}
//添加学生信息
void Console::AddStudentInfo() {
    string no, name, sex, age, dno,dname, password;
    InfoPage("添加学生");
    while (true)
    {
        ArrowsMove(16, pos.Y, 5, 11);
        if (operand == 27)
        {
            return;
        }
        else if (pos.Y == 5)
        {
            Input(no);
        }
        else if (pos.Y == 6)
        {
            Input(name);
        }
        else if (pos.Y == 7)
        {
            Input(sex);
        }
        else if (pos.Y == 8)
        {
            Input(age);
        }
        else if (pos.Y == 9)
        {
            Department d=ChoiceDepartment();
            dno = d.GetNumber();
            dname = d.GetName();
            InfoPage("添加学生",no, name, sex, age, dname, password);
        }
        else if (pos.Y == 10)
        {
            Input(password);
        }
        else if (pos.Y == 11) {
            if (no == "") {
                Alert("学号不能为空");
            }
            else if (name == "") {
                Alert("姓名不能为空");
            }
            else if (dname == "") {
                Alert("部门不能为空");
            }
            else if (password == "") {
                Alert("密码不能为空");
            }
            else {
                char str[] = "insert into student values('%s','%s','%s','%s','%s','%s');";
                sprintf_s(sqlStr, str, no.c_str(), name.c_str(), sex.c_str(), age.c_str(), dno.c_str(), password.c_str());
                //cout << sqlStr << endl;
                //system("pause");
                if (data.ExeSql(sqlStr)) {
                    st.insert(Person(no, name, sex, age, dname, password));
                    Alert("添加成功！");
                    return;
                }
                else {
                    Alert("学号重复");
                }
            }
            InfoPage("添加学生",no, name, sex, age, dname, password);
        }
    }
}
//查询学生信息
void Console::SearchStudentInfo() {
    string no, name, sex, age, dno, dname, password;
    string str = "select no,s.name,sex,age,d.name from student s,department d where s.dno=d.dno";
    string strNo, strName, strSex, strAge, strDno, strPassword;
    InfoPage("查询学生");
    while (true)
    {
        ArrowsMove(16, pos.Y, 5, 11);
        if (operand == 27)
        {
            return;
        }
        else if (pos.Y == 5)
        {
            Input(no);
            strNo = " and s.no='" + no + "'";
        }
        else if (pos.Y == 6)
        {
            Input(name);
            strName = " and s.name='" + name + "'";
        }
        else if (pos.Y == 7)
        {
            Input(sex);
            strSex = " and s.sex='" + sex + "'";
        }
        else if (pos.Y == 8)
        {
            Input(age);
            strAge = " and s.age='" + age + "'";
        }
        else if (pos.Y == 9)
        {
            Department d = ChoiceDepartment();
            dno = d.GetNumber();
            dname = d.GetName();
            strDno = " and s.dno='" + dno + "'";
            InfoPage("查询学生",no, name, sex, age, dname, password);
        }
        else if (pos.Y == 10)
        {
            Input(password);
            strPassword = " and s.password='" + password + "'";
        }
        else if (pos.Y == 11) {
            str = str + strNo + strName + strSex + strAge + strDno + strPassword + ";";
            //cout << str << endl;
            //system("pause");
            set<Person, Compare> s = data.GetPersonTb(str.c_str());
            if (s.size() == 0) {
                Alert("该学生不存在！");
                return;
            }
            else {
                st = s;
                Alert("查询成功！");
                return;
            }           
            InfoPage("查询学生",no, name, sex, age, dname, password);
        }
    }
}
//修改学生信息
void Console::ModifyStudentInfo(Person& p) {
    Department d;
    for (set<Department, Compare>::iterator it = de.begin(); it != de.end();it++) {
        d = *it;
        if (d.GetName() == p.GetDname()) {           
            break;
        }
    }
    string no, name, sex, age, dno, dname, password;
    bool reset = true;
    char str[] = "update student set %s where no='%s';";
    string strNo, strName, strSex, strAge, strDno, strPassword;
    while (true)
    {
        if (reset) {
            no = p.GetNumber();
            name = p.GetName();
            sex = p.GetSex();
            age = p.GetAge();
            dname = p.GetDname();
            password = p.GetPassword();
            dno = d.GetNumber();
            strNo = "";
            strName = "";
            strSex = "";
            strAge = "";
            strDno = "";
            strPassword = "";
            InfoPage("修改学生", no, name, sex, age, dname, password);
            reset = false;
        }
        ArrowsMove(16, pos.Y, 5, 11);
        if (operand == 27)
        {
            return;
        }
        else if (pos.Y == 5)
        {
            Input(no);
            strNo = "no='" + no + "',";
        }
        else if (pos.Y == 6)
        {
            Input(name);
            strName = "name='" + name + "',";
        }
        else if (pos.Y == 7)
        {
            Input(sex);
            strSex = "sex='" + sex + "',";
        }
        else if (pos.Y == 8)
        {
            Input(age);
            strAge = "age='" + age + "',";
        }
        else if (pos.Y == 9)
        {
            Department d = ChoiceDepartment();
            dno = d.GetNumber();
            dname = d.GetName();
            strDno = "dno='" + dno + "',";
            InfoPage("修改学生",no, name, sex, age, dname, password);
        }
        else if (pos.Y == 10)
        {
            Input(password);
            strPassword = "password='" + password + "',";
        }
        else if (pos.Y == 11) {
            string set = strNo + strName + strSex + strAge + strDno + strPassword;
            if (no == "") {
                Alert("学号不能为空");
            }
            else if (name == "") {
                Alert("姓名不能为空");
            }
            else if (dname == "") {
                Alert("部门不能为空");
            }
            else if (password == "") {
                Alert("密码不能为空");
            }
            else if (set == "") {
                return;
            }
            else {
                set = set.replace(set.length()-1, 1, "");
                sprintf_s(sqlStr, str, set.c_str(), p.GetNumber().c_str());
                //cout << sqlStr << endl;
                //system("pause");
                if (data.ExeSql(sqlStr)) {
                    st.erase(p);
                    st.insert(Person (no, name, sex, age, dname, password));
                    Alert("修改成功！");
                    return;
                }
                else
                {
                    Alert("学号重复");
                }
            }
            reset = true;
        }
    }
}
//删除学生信息
void Console::DeleteStudentInfo(Person& p) {
    string no = p.GetNumber();
    if (Alert("确认删除学号‘" + no + "’的学生？")) {
        char str[] = "delete from student where no='%s';";
        sprintf_s(sqlStr, str, no.c_str());
        if (data.ExeSql(sqlStr)) {
            st.erase(p);
            Alert("删除成功!");
        }
    }
}
//学生选课页面
void Console::ChoiceCourse() {
    int last = 9;
    st = data.GetPersonTb("select no,s.name,sex,age,d.name,password from student s,department d where s.dno=d.dno and no=" + account + ";");  
    co = data.GetCourseTb("select cno,c.name,t.name from course c,teacher t where c.tno=t.no;");
    Person p;
    while (true)
    {
        vector<Course> v;
        system("cls");
        sc = data.GetScTb("select sno,cno,score from sc where sno='" + account + "';");
        cout << "        欢迎！" + type[mode] + "：" << account << endl;
        cout << "      ************************************************************" << endl;
        cout << "                          【教务管理系统】" << endl;
        cout << "      ------------------------------------------------------------" << endl;
        for (set<Person, Compare>::iterator it = st.begin(); it != st.end(); it++) {
            p = *it;
            cout << "\t学号：" + p.GetNumber() + " 姓名：" + p.GetName() + " 性别：" + p.GetSex() + " 年龄：" + p.GetAge() + " 部门：" + p.GetDname() << endl;
        }
        cout << "      ************************************************************" << endl;
        cout << "                            $选课信息$" << endl;
        cout << "\t课程号\t课程名\t任课教师\t选课状态\t课程成绩" << endl;
        cout << "      ------------------------------------------------------------" << endl;
        if (co.size() == 0) {
            cout << "\t暂无课程" << endl;
        }
        else {
            for (set<Course, Compare>::iterator it = co.begin(); it != co.end(); it++) {
                Course c = *it;
                v.push_back(c);
                v[v.size() - 1].status = false;
                Sc s;
                for (set<Sc, Compare>::iterator it2 = sc.begin(); it2 != sc.end(); it2++) {
                    s = *it2;
                    //cout << c.GetName() + " "+s.GetCno() << endl;
                    if (c.GetNumber() == s.GetCno()) {
                        v[v.size() - 1].status = true;
                        break;
                    }
                }
                cout << "\t" + c.GetNumber() << "\t" + c.GetName() << "\t" + c.GetTname();
                if (v[v.size() - 1].status) {
                    cout << "\t已选" << "\t" + s.GetScore() << endl;
                }
                else {
                    cout << "\t未选" << endl;
                }
            }
        }
        cout << "      ************************************************************" << endl;
        cout << "            " << "操作说明：" << endl;
        cout << "\t\t" << "w:上移" << endl;
        cout << "\t\t" << "s:下移" << endl;
        cout << "\t\t" << "ESC:退出登录" << endl;
        cout << "\t\t" << "ENTER:选课/取消选课" << endl;
        ArrowsMove(6, last, 9, 8 + (co.size() ? co.size() : 1));
        last = pos.Y;
        if (operand == 27) {
            if (Alert("是否退出登录？")) {
                system("cls");
                return;
            }
        }
        else if (co.size() > 0) {
            if (operand == 13) {
                if (v[pos.Y - 9].status) {
                    if (Alert("是否取消选课：" + v[pos.Y - 9].GetName() + "?")) {
                        char str[] = "delete from sc where sno='%s' and cno='%s';";
                        sprintf_s(sqlStr, str, p.GetNumber().c_str(), v[pos.Y - 9].GetNumber().c_str());
                        if (data.ExeSql(sqlStr)) {
                            v[pos.Y - 9].status = false;
                            Alert("取消成功");
                        }
                    }
                }
                else {
                    char str[] = "insert into sc values('%s','%s',NULL);";
                    sprintf_s(sqlStr, str, p.GetNumber().c_str(), v[pos.Y - 9].GetNumber().c_str());
                    if (data.ExeSql(sqlStr)) {
                        v[pos.Y - 9].status = true;
                        Alert("选课成功");
                    }
                }
            }
        }
    }
}