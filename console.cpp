#include"console.h"
//Console���캯��
Console::Console() {
    system("title �������ϵͳ");
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
//д����¼
void Console::WriteRecord() {
    ofstream o("C:/edu/record.txt", ios::out);
    if (o.is_open())
    {
        o << account << "\n" << password << "\n" << server << "\n" << user << "\n" << Dpassword << "\n" << database << "\n" << charset;
    }
    o.close();
}
//�������ݿ�
bool Console::ConnectDatabase() {
    if (data.Connect(server.c_str(), user.c_str(), Dpassword.c_str(), database.c_str(), charset.c_str())) {
        //cout << "�������ݿ�ɹ�!" << endl;
        data.InitializeTbs();
        return true;
    }
    else
    {
        if (Alert("�������ݿ�ʧ��!\n\t\t�Ƿ�����ݿ�������Ϣ")) {
            Config();
            ConnectDatabase();
        }
        else {
            exit(1);
        }
    }
}
//���ù��λ�ú�����״̬
void Console::SetCursor(int x, int y, bool visible)
{
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    cci.dwSize = sizeof(cci);
    cci.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}
//�ƶ���ͷ
void Console::ArrowsMove(int x, int y, int low, int high, vector<char> operand)
{
    SetCursor(x, y);
    cout << "->";//�ڹ�괦���
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
//��������
void Console::Input(string&str) {
    SetCursor(25, pos.Y, true);
    cout << "                                           ";
    SetCursor(25, pos.Y, true);
    cin >> str;
}
//����ҳ��
bool Console::Alert(string content)
{
    system("cls");
    cout << endl;
    cout << "        ******************************************" << endl;
    cout << "                " << endl << endl;
    cout << "                " << content << endl;
    cout << endl << endl;
    cout << "        ******************************************" << endl;
    cout << "            " << "����˵����" << endl;
    cout << "              " << "ESC:����" << endl;
    cout << "              " << "ENTER:ȷ��" << endl;
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
//��¼ҳ��
void Console::LoadinPage() {
    system("cls");
    cout << endl;
    cout << "        ******************************************" << endl;
    cout << "                   ���������ϵͳ��" << endl;
    cout << "                      $��¼ҳ��$" << endl;
    cout << "        ------------------------------------------" << endl;
    cout << "                   �˺ţ�"+account  << endl;
    cout << "                   ���룺"+password  << endl;
    cout << "                       <��¼>" << endl;
    cout << "                     <��ְ��ע��>" << endl;
    cout << "                     <���ݿ�����>" << endl;
    cout << "                      <�˳�����>" << endl;
    cout << "        ******************************************" << endl;
    cout << "            " << "����˵����" << endl;
    cout << "\t\t" << "w:����" << endl;
    cout << "\t\t" << "s:����" << endl;
    cout << "\t\t" << "ESC:�˳�" << endl;
    cout << "\t\t" << "ENTER:ȷ��" << endl;
    SetCursor(16, 5);
}
//����̨
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
//��¼�ж�
bool Console::SignIn() {
    char temp[]="select * from %s where no='%s' and password='%s';";
    sprintf_s(sqlStr, temp, "teacher", account.c_str(), password.c_str());
    //cout << sqlStr << endl;
    //system("pause");
    if (data.ExeSql(sqlStr) && mysql_num_rows(data.result) == 1) {
        Alert(type[0]+" ��¼�ɹ���");
        mode = 0;
        return true;
    }
    else
    {
        sprintf_s(sqlStr, temp, "student", account.c_str(), password.c_str());
        //cout << sqlStr << endl;
        //system("pause");
        if (data.ExeSql(sqlStr) && mysql_num_rows(data.result) == 1) {
            Alert(type[1]+" ��¼�ɹ���");
            mode = 1;
            return true;
        }
        else {
            Alert("�˺Ų����ڻ��������");
            return false;
        }
    }
    return false;
}
//��ҳ��
void Console::MainPage() {
    if (mode == 0) {
        int last = 4;
        while (true)
        {
            system("cls");
            cout << "        ��ӭ��" + type[mode] + "��" << account << endl;
            cout << "      ********************************************" << endl;
            cout << "                   ���������ϵͳ��" << endl;
            cout << "      ********************************************" << endl;
            cout << "                      ����γ�" << endl;
            cout << "                      ����ѧ��" << endl;
            cout << "                      ע����ǰְ��" << endl;
            cout << "      ********************************************" << endl;
            cout << "            " << "����˵����" << endl;
            cout << "\t\t" << "w:����" << endl;
            cout << "\t\t" << "s:����" << endl;
            cout << "\t\t" << "ESC:�˳���¼" << endl;
            cout << "\t\t" << "ENTER:ȷ��" << endl;
            ArrowsMove(18, last, 4, 6);
            last = pos.Y;
            if (operand == 27) {
                if (Alert("�Ƿ��˳���¼��")) {
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
//�û���Ϣҳ��
void Console::InfoPage(string title, string no, string name, string sex, string age, string dname, string password) {
    system("cls");
    string label = (mode == 0) ? "ѧ" : "��";
    cout << endl;
    cout << "        ******************************************" << endl;
    cout << "                   ���������ϵͳ��" << endl;
    cout << "                   $" + title + "��Ϣ$" << endl;
    cout << "        ------------------------------------------" << endl;
    cout << "                   " + label + "�ţ�" + no << endl;
    cout << "                   ������" + name << endl;
    cout << "                   �Ա�" + sex << endl;
    cout << "                   ���䣺" + age << endl;
    cout << "                   ���ţ�" + dname << endl;
    cout << "                   ���룺" + password << endl;
    cout << "                      <" + title + ">" << endl;
    cout << "        ******************************************" << endl;
    cout << "            " << "����˵����" << endl;
    cout << "\t\t" << "w:����" << endl;
    cout << "\t\t" << "s:����" << endl;
    cout << "\t\t" << "ESC:����" << endl;
    cout << "\t\t" << "ENTER:ȷ��" << endl;
    SetCursor(pos.X, 5);
}
//ѡ����
Department Console::ChoiceDepartment() {
    vector<Department> v;
    system("cls");
    cout << endl;
    cout << "        ******************************************" << endl;
    cout << "                   ���������ϵͳ��" << endl;
    cout << "                      $ѡ����$" << endl;
    cout << "        ------------------------------------------" << endl;
    for (set<Department, Compare>::iterator it = de.begin(); it != de.end(); it++) {
        Department d(*it);
        v.push_back(d);
        cout << "\t\t  " + d.GetName() << endl;
    }
    cout << "        ******************************************" << endl;
    cout << "            " << "����˵����" << endl;
    cout << "\t\t" << "w:����" << endl;
    cout << "\t\t" << "s:����" << endl;
    cout << "\t\t" << "ESC:����" << endl;
    cout << "\t\t" << "ENTER:ȷ��" << endl;
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
//���ְ����Ϣ
void Console::AddTeacherInfo() {
    string no, name, sex, age, dno, dname, password;
    InfoPage("���ְ��");
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
            InfoPage("���ְ��", no, name, sex, age, dname, password);
        }
        else if (pos.Y == 10)
        {
            Input(password);
        }
        else if (pos.Y == 11) {
            if (no == "") {
                Alert("���Ų���Ϊ��");
            }
            else if (name == "") {
                Alert("��������Ϊ��");
            }
            else if (dname == "") {
                Alert("���Ų���Ϊ��");
            }
            else if (password == "") {
                Alert("���벻��Ϊ��");
            }
            else {
                char str[] = "insert into teacher values('%s','%s','%s','%s','%s','%s');";
                sprintf_s(sqlStr, str, no.c_str(), name.c_str(), sex.c_str(), age.c_str(), dno.c_str(), password.c_str());
                //cout << sqlStr << endl;
                //system("pause");
                if (data.ExeSql(sqlStr)) {
                    te.insert(Person(no, name, sex, age, dname, password));
                    Alert("��ӳɹ���");
                    return;
                }
                else {
                    Alert("�����ظ�");
                }
            }
            InfoPage("���ְ��", no, name, sex, age, dname, password);
        }
    }
}
//ɾ��ְ����Ϣ
void Console::DeleteTeacherInfo() {
    if (Alert("ȷ��ע�����š�" + account + "����ְ����")) {
        char str[] = "delete from teacher where no='%s';";
        sprintf_s(sqlStr, str, account);
        if (data.ExeSql(sqlStr)) {
            Alert("ע���ɹ�!");
        }
    }
}
//���ݿ�����
void Console::Config() {
    system("cls");
    cout << endl;
    cout << "        ******************************************" << endl;
    cout << "                   ���������ϵͳ��" << endl;
    cout << "                     $���ݿ�����$" << endl;
    cout << "        ------------------------------------------" << endl;
    cout << "                  server:" + server << endl;
    cout << "                    user:" + user << endl;
    cout << "                password:" + Dpassword << endl;
    cout << "                database:" + database << endl;
    cout << "                 charset:" + charset << endl;
    cout << "                       <ȷ��>" << endl;
    cout << "        ******************************************" << endl;
    cout << "            " << "����˵����" << endl;
    cout << "\t\t" << "w:����" << endl;
    cout << "\t\t" << "s:����" << endl;
    cout << "\t\t" << "ESC:����" << endl;
    cout << "\t\t" << "ENTER:ȷ��" << endl;
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
//����γ�ҳ��
void Console::ManageCourse() {
    vector<char> vc = { 'a','d' };
    int last = 6;
    te = data.GetPersonTb("select no,t.name,sex,age,d.name,password from teacher t,department d where t.dno=d.dno;");
    co = data.GetCourseTb("select cno,c.name,t.name from course c,teacher t where c.tno=t.no;");
    while (true)
    {
        vector<Course> v;
        system("cls");
        cout << "        ��ӭ��" + type[mode] + "��" << account << endl;
        cout << "      ********************************************" << endl;
        cout << "                   ���������ϵͳ��" << endl;
        cout << "      ********************************************" << endl;
        cout << "\t�γ̺�\t�γ���\t�ον�ʦ" << endl;
        cout << "      --------------------------------------------" << endl;
        if (co.size() == 0) {
            cout << "\t���޿γ�" << endl;
        }
        else {
            for (set<Course, Compare>::iterator it = co.begin(); it != co.end(); it++) {
                Course c(*it);
                v.push_back(c);
                cout << "\t" + c.GetNumber() + "\t" + c.GetName() + "\t" + c.GetTname() << endl;
            }
        }       
        cout << "      ********************************************" << endl;
        cout << "            " << "����˵����" << endl;
        cout << "\t\t" << "w:����" << endl;
        cout << "\t\t" << "s:����" << endl;
        cout << "\t\t" << "ESC:�˳���¼" << endl;
        cout << "\t\t" << "ENTER:�鿴ѡ������ѧ��" << endl;
        cout << "\t\t" << "a:��ӿγ�" << endl;
        cout << "\t\t" << "d:ɾ���γ�" << endl;
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
//�γ���Ϣҳ��
void Console::CourseInfoPage(string title,string cno,string name,string tname) {
    system("cls");
    cout << endl;
    cout << "        ******************************************" << endl;
    cout << "                   ���������ϵͳ��" << endl;
    cout << "                   $" + title + "��Ϣ$" << endl;
    cout << "        ------------------------------------------" << endl;
    cout << "                 �γ̺ţ�" + cno << endl;
    cout << "                 �γ�����" + name << endl;
    cout << "               �ον�ʦ��" + tname << endl;
    cout << "                      <" + title + ">" << endl;
    cout << "        ******************************************" << endl;
    cout << "            " << "����˵����" << endl;
    cout << "\t\t" << "w:����" << endl;
    cout << "\t\t" << "s:����" << endl;
    cout << "\t\t" << "ESC:����" << endl;
    cout << "\t\t" << "ENTER:ȷ��" << endl;
    SetCursor(pos.X, 5);
}
//ѡ���ον�ʦ
Person Console::ChoiceTeacher() {
    vector<Person> v;
    system("cls");
    cout << endl;
    cout << "        ******************************************" << endl;
    cout << "                   ���������ϵͳ��" << endl;
    cout << "                    $ѡ���ον�ʦ$" << endl;
    cout << "        ------------------------------------------" << endl;
    for (set<Person, Compare>::iterator it = te.begin(); it != te.end(); it++) {
        Person p(*it);
        v.push_back(p);
        cout << "\t\t\t" + p.GetName() << endl;
    }
    cout << "        ******************************************" << endl;
    cout << "            " << "����˵����" << endl;
    cout << "\t\t" << "w:����" << endl;
    cout << "\t\t" << "s:����" << endl;
    cout << "\t\t" << "ESC:����" << endl;
    cout << "\t\t" << "ENTER:ȷ��" << endl;
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
//��ӿγ���Ϣ
void Console::AddCourseInfo() {
    string cno, name, tno,tname;
    CourseInfoPage("��ӿγ�");
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
            CourseInfoPage("��ӿγ�", cno, name, tname);
        }
        else if (pos.Y == 8) {
            if (cno == "") {
                Alert("�γ̺Ų���Ϊ��");
            }
            else if (name == "") {
                Alert("�γ�������Ϊ��");
            }
            else if (tname == "") {
                Alert("�ον�ʦ����Ϊ��");
            }
            else {
                char str[] = "insert into course values('%s','%s','%s');";
                sprintf_s(sqlStr, str, cno.c_str(), name.c_str(), tno.c_str());
                //cout << sqlStr << endl;
                //system("pause");
                if (data.ExeSql(sqlStr)) {
                    co.insert(Course(cno, name, tname));
                    Alert("��ӳɹ���");
                    return;
                }
                else {
                    Alert("�γ̺��ظ�");
                }
            }
            CourseInfoPage("��ӿγ�", cno, name, tname);
        }
    }
}
//�鿴����ѡ�ε�ѧ��
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
        cout << "        ��ӭ��" + type[mode] + "��" << account << endl;
        cout << "      ********************************************" << endl;
        cout << "                   ���������ϵͳ��" << endl;
        cout << "      ********************************************" << endl;
        cout << "\tѧ��\t����\t�Ա�\t����\t����" << endl;
        cout << "      --------------------------------------------" << endl;
        if (st.size() == 0) {
            cout << "\t����ѧ��ѡ��" << endl;
        }
        else {
            for (set<Person, Compare>::iterator it = st.begin(); it != st.end(); it++) {
                Person p(*it);
                v.push_back(p);
                cout << "\t" + p.GetNumber() + "\t" + p.GetName() + "\t" + p.GetSex() + "\t" + p.GetAge() + "\t" + p.GetDname() << endl;
            }
        }
        cout << "      ********************************************" << endl;
        cout << "            " << "����˵����" << endl;
        cout << "\t\t" << "w:����" << endl;
        cout << "\t\t" << "s:����" << endl;
        cout << "\t\t" << "ESC:����" << endl;
        cout << "\t\t" << "d:ɾ��ѧ��ѡ��" << endl;
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
//ɾ��ѡ�ε�ѧ��
void Console::DeleteStudentCourse(Person& p, Course& c) {
    string no = p.GetNumber();
    if (Alert("ȷ��ɾ��ѡ��"+c.GetName()+"���γ̵�\n\t\t��" + no + "���ŵ�ѧ����")) {
        char str[] = "delete from sc where sno='%s';";
        sprintf_s(sqlStr, str, no.c_str());
        if (data.ExeSql(sqlStr)) {
            st.erase(p);
            Alert("ɾ���ɹ�!");
        }
    }
}
//ɾ���γ�
void Console::DeleteCourse(Course& c) {
    string cno = c.GetNumber();
    if (Alert("ȷ��ɾ���γ̺š�" + cno + "���Ŀγ̣�")) {
        char str[] = "delete from course where cno='%s';";
        sprintf_s(sqlStr, str, cno.c_str());
        //cout << sqlStr << endl;
        //system("pause");
        if (data.ExeSql(sqlStr)) {
            co.erase(c);
            Alert("ɾ���ɹ�!");
        }
    }
}
//����ѧ��ҳ��
void Console::ManageStudent() {
    vector<char> vc = { 'a','f','d' };
    int last = 6;
    st = data.GetPersonTb("select no,s.name,sex,age,d.name,password from student s,department d where s.dno=d.dno;");
    while (true)
    {
        vector<Person> v;
        system("cls");
        cout << "        ��ӭ��" + type[mode] + "��" << account << endl;
        cout << "      ********************************************" << endl;
        cout << "                   ���������ϵͳ��" << endl;
        cout << "      ********************************************" << endl;
        cout << "\tѧ��\t����\t�Ա�\t����\t����" << endl;
        cout << "      --------------------------------------------" << endl;
        if (st.size() == 0) {
            cout << "\t����ѧ��" << endl;
        }
        else {
            for (set<Person, Compare>::iterator it = st.begin(); it != st.end(); it++) {
                Person p(*it);
                v.push_back(p);
                cout << "\t" + p.GetNumber() + "\t" + p.GetName() + "\t" + p.GetSex() + "\t" + p.GetAge() + "\t" + p.GetDname() << endl;
            }
        }
        cout << "      ********************************************" << endl;
        cout << "            " << "����˵����" << endl;
        cout << "\t\t" << "w:����" << endl;
        cout << "\t\t" << "s:����" << endl;
        cout << "\t\t" << "ESC:����" << endl;
        cout << "\t\t" << "ENTER:�޸�ѧ����Ϣ" << endl;
        cout << "\t\t" << "a:���ѧ����Ϣ" << endl;
        cout << "\t\t" << "f:��ѯѧ����Ϣ" << endl;
        cout << "\t\t" << "d:ɾ��ѧ����Ϣ" << endl;
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
//���ѧ����Ϣ
void Console::AddStudentInfo() {
    string no, name, sex, age, dno,dname, password;
    InfoPage("���ѧ��");
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
            InfoPage("���ѧ��",no, name, sex, age, dname, password);
        }
        else if (pos.Y == 10)
        {
            Input(password);
        }
        else if (pos.Y == 11) {
            if (no == "") {
                Alert("ѧ�Ų���Ϊ��");
            }
            else if (name == "") {
                Alert("��������Ϊ��");
            }
            else if (dname == "") {
                Alert("���Ų���Ϊ��");
            }
            else if (password == "") {
                Alert("���벻��Ϊ��");
            }
            else {
                char str[] = "insert into student values('%s','%s','%s','%s','%s','%s');";
                sprintf_s(sqlStr, str, no.c_str(), name.c_str(), sex.c_str(), age.c_str(), dno.c_str(), password.c_str());
                //cout << sqlStr << endl;
                //system("pause");
                if (data.ExeSql(sqlStr)) {
                    st.insert(Person(no, name, sex, age, dname, password));
                    Alert("��ӳɹ���");
                    return;
                }
                else {
                    Alert("ѧ���ظ�");
                }
            }
            InfoPage("���ѧ��",no, name, sex, age, dname, password);
        }
    }
}
//��ѯѧ����Ϣ
void Console::SearchStudentInfo() {
    string no, name, sex, age, dno, dname, password;
    string str = "select no,s.name,sex,age,d.name from student s,department d where s.dno=d.dno";
    string strNo, strName, strSex, strAge, strDno, strPassword;
    InfoPage("��ѯѧ��");
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
            InfoPage("��ѯѧ��",no, name, sex, age, dname, password);
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
                Alert("��ѧ�������ڣ�");
                return;
            }
            else {
                st = s;
                Alert("��ѯ�ɹ���");
                return;
            }           
            InfoPage("��ѯѧ��",no, name, sex, age, dname, password);
        }
    }
}
//�޸�ѧ����Ϣ
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
            InfoPage("�޸�ѧ��", no, name, sex, age, dname, password);
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
            InfoPage("�޸�ѧ��",no, name, sex, age, dname, password);
        }
        else if (pos.Y == 10)
        {
            Input(password);
            strPassword = "password='" + password + "',";
        }
        else if (pos.Y == 11) {
            string set = strNo + strName + strSex + strAge + strDno + strPassword;
            if (no == "") {
                Alert("ѧ�Ų���Ϊ��");
            }
            else if (name == "") {
                Alert("��������Ϊ��");
            }
            else if (dname == "") {
                Alert("���Ų���Ϊ��");
            }
            else if (password == "") {
                Alert("���벻��Ϊ��");
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
                    Alert("�޸ĳɹ���");
                    return;
                }
                else
                {
                    Alert("ѧ���ظ�");
                }
            }
            reset = true;
        }
    }
}
//ɾ��ѧ����Ϣ
void Console::DeleteStudentInfo(Person& p) {
    string no = p.GetNumber();
    if (Alert("ȷ��ɾ��ѧ�š�" + no + "����ѧ����")) {
        char str[] = "delete from student where no='%s';";
        sprintf_s(sqlStr, str, no.c_str());
        if (data.ExeSql(sqlStr)) {
            st.erase(p);
            Alert("ɾ���ɹ�!");
        }
    }
}
//ѧ��ѡ��ҳ��
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
        cout << "        ��ӭ��" + type[mode] + "��" << account << endl;
        cout << "      ************************************************************" << endl;
        cout << "                          ���������ϵͳ��" << endl;
        cout << "      ------------------------------------------------------------" << endl;
        for (set<Person, Compare>::iterator it = st.begin(); it != st.end(); it++) {
            p = *it;
            cout << "\tѧ�ţ�" + p.GetNumber() + " ������" + p.GetName() + " �Ա�" + p.GetSex() + " ���䣺" + p.GetAge() + " ���ţ�" + p.GetDname() << endl;
        }
        cout << "      ************************************************************" << endl;
        cout << "                            $ѡ����Ϣ$" << endl;
        cout << "\t�γ̺�\t�γ���\t�ον�ʦ\tѡ��״̬\t�γ̳ɼ�" << endl;
        cout << "      ------------------------------------------------------------" << endl;
        if (co.size() == 0) {
            cout << "\t���޿γ�" << endl;
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
                    cout << "\t��ѡ" << "\t" + s.GetScore() << endl;
                }
                else {
                    cout << "\tδѡ" << endl;
                }
            }
        }
        cout << "      ************************************************************" << endl;
        cout << "            " << "����˵����" << endl;
        cout << "\t\t" << "w:����" << endl;
        cout << "\t\t" << "s:����" << endl;
        cout << "\t\t" << "ESC:�˳���¼" << endl;
        cout << "\t\t" << "ENTER:ѡ��/ȡ��ѡ��" << endl;
        ArrowsMove(6, last, 9, 8 + (co.size() ? co.size() : 1));
        last = pos.Y;
        if (operand == 27) {
            if (Alert("�Ƿ��˳���¼��")) {
                system("cls");
                return;
            }
        }
        else if (co.size() > 0) {
            if (operand == 13) {
                if (v[pos.Y - 9].status) {
                    if (Alert("�Ƿ�ȡ��ѡ�Σ�" + v[pos.Y - 9].GetName() + "?")) {
                        char str[] = "delete from sc where sno='%s' and cno='%s';";
                        sprintf_s(sqlStr, str, p.GetNumber().c_str(), v[pos.Y - 9].GetNumber().c_str());
                        if (data.ExeSql(sqlStr)) {
                            v[pos.Y - 9].status = false;
                            Alert("ȡ���ɹ�");
                        }
                    }
                }
                else {
                    char str[] = "insert into sc values('%s','%s',NULL);";
                    sprintf_s(sqlStr, str, p.GetNumber().c_str(), v[pos.Y - 9].GetNumber().c_str());
                    if (data.ExeSql(sqlStr)) {
                        v[pos.Y - 9].status = true;
                        Alert("ѡ�γɹ�");
                    }
                }
            }
        }
    }
}