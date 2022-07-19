#include <iostream>
#include <conio.h>
#include <string>
#include <vector>

using namespace std;

int person_number(int);

//حساب
class account
{
private:
    int num_account;
    unsigned long long c_nationalcode;
    string a_date;
    unsigned long long bankroll;

    bool activity;

public:
    account()
    {
        num_account = 0;
        bankroll = 0;
    }
    account(int x, unsigned long long y, string a_date_, unsigned long long z)
    {
        num_account = x;
        c_nationalcode = y;
        a_date = a_date_;
        bankroll = z;
    }

    void active_information()
    {
        if (activity == true)
        {
            cout << "\nThis account is active.\n";
        }
        else
        {
            cout << "\nThis account is inactive.\n";
        }
    }

    friend class client;
};

//شخص
class person
{
private:
    string name;
    string family;
    string date;

    string username;
    string password;

public:
    person(string name_, string family_, string date_, string username_, string password_);

    string get_name() { return name; }
    string get_family() { return family; }
    string get_date() { return date; }

    string get_username() { return username; }
    string get_password() { return password; }
};

person::person(string name_, string family_, string date_, string username_, string password_)
{
    name = name_;
    family = family_;
    date = date_;
    username = username_;
    password = password_;
}

//مشتری
class client : public person
{
private:
    unsigned long long c_nationalcode;
    vector<account> accounts;

public:
    client(string name_, string family_, string date_, string username_, string password_, unsigned long long c_nationalcode_) : person(name_, family_, date_, username_, password_)
    {
        c_nationalcode = c_nationalcode_;
    }

    void add_account(int number, unsigned long long national, string date, unsigned long long amount)
    {
        account a(number, national, date, amount);
        a.activity = true;
        accounts.push_back(a);
    }

    int remove_account(int number)
    {
        for (int i = 0; i < accounts.size(); i++)
        {
            if (number == accounts[i].num_account)
            {
                accounts.erase(accounts.begin() + i);
                return accounts.size();
            }
        }
        return -1;
    }

    void activate(int i) { accounts[i].activity = true; }
    void inactive(int i) { accounts[i].activity = false; }

    void increse(unsigned long long money, int i);
    void reduce(unsigned long long cash, int i);

    int get_num_account(int i) { return accounts[i].num_account; }
    int get_size() { return accounts.size(); }

    unsigned long long get_national() { return c_nationalcode; }

    void show_client();
    void show_accounts();
};

void client::show_client()
{
    cout << "\n\nName:  " << person::get_name();
    cout << "\nFamily:  " << person::get_family();
    cout << "\nBirthday;  " << person::get_date();

    cout << "\nUsername:  " << person::get_username();
    cout << "\nPassword:  " << person::get_password();

    cout << "\nNationalcode:  " << c_nationalcode;

    for (int i = 0; i < accounts.size(); i++)
    {
        cout << "\nAccount" << i << " :  " << accounts[i].bankroll;
    }

    cout << "\n___________\n";
}

void client::show_accounts()
{
    for (int i = 0; i < accounts.size(); i++)
    {
        cout << "*" << i + 1 << "*\nnumber:    " << accounts[i].num_account;
        cout << "\ntha date of caret:    " << accounts[i].a_date;
        cout << "\nbankroll:    " << accounts[i].bankroll;

        accounts[i].active_information();

        cout << "~~~~~~~~";
    }
}

void client::increse(unsigned long long money, int i)
{
    for (int j = 0; j < accounts.size(); j++)
    {
        if (i == accounts[j].num_account)
        {
            accounts[i].bankroll += money;
            return;
        }
    }

    cout << "error!";
}

void client::reduce(unsigned long long cash, int i)
{
    for (int j = 0; j < accounts.size(); j++)
    {
        if (i == accounts[i].num_account)
        {
            if (accounts[i].activity == true)
            {
                accounts[i].bankroll -= cash;
            }
            return;
        }
    }

    cout << "error!";
}

//کارمند
class employee : public person
{
private:
    unsigned int e_personnum;
    unsigned int e_salary;
    unsigned int e_offhour;
    unsigned int e_overtime;

public:
    employee(string name_, string family_, string date_, string username_, string password_, unsigned int e_personnum_, unsigned int e_salary_) : person(name_, family_, date_, username_, password_)
    {
        e_personnum = person_number(e_personnum_);
        e_salary = e_salary_;
        e_offhour = 0;
        e_overtime = 0;
    }
    void offhour(int asked_hour);
    void overtime(int overtime_hour);

    unsigned int get_e_num() { return e_personnum; }
    unsigned int get_e_salary() { return e_salary; }
    unsigned int get_e_off() { return e_offhour; }
    unsigned int get_e_over() { return e_overtime; }
};

void employee::offhour(int asked_hour)
{
    int salary = e_salary;
    if (e_offhour + asked_hour > 15)
    {
        if (e_offhour >= 15)
        {
            salary -= 100 * (asked_hour);
        }
        else if (e_offhour < 15)
        {
            salary -= 100 * ((e_offhour + asked_hour) - 15);
        }

        cout << "\nYou took more leave than allowed in a month, then your salary will be reduced. \nNow your salary in this month is:   " << salary << " thousand tooman. \n";
    }
    else
    {
        if (salary >= 0)
        {
            cout << "\nYou have " << (15 - (e_offhour + asked_hour)) << " hours off before completing 15 hours. \n";
        }
    }

    if (salary < 0)
    {
        cout << "\nYou can't get off.\n";
    }
    else
    {
        e_offhour += asked_hour;
        e_salary = salary;
    }
}

void employee ::overtime(int asked_overtime)
{
    if (e_overtime + asked_overtime <= 12)
    {
        e_salary += asked_overtime * 120;
        e_overtime += asked_overtime;

        cout << "\nNow your salary is   " << e_salary << " thousand tooman. \n";
    }
    else
    {
        cout << "\nYou can't get overtime.\n";
    }
}

int person_number(int x)
{
    int y;
    bool e = true;

    while (e)
    {
        if (x >= 100 && x <= 999)
        {
            y = x;
            e = false;
        }
        else
        {
            cout << "\nerror!please inter three digits person_number.\n";
            cin >> x;
        }
    }

    return y;
}

//مدیر

class manage : public employee
{
public:
    manage(string name_, string family_, string date_, string username_, string password_, unsigned int e_personnum_, unsigned int e_salary_) : employee(name_, family_, date_, username_, password_, e_personnum_, e_salary_) {}
};

//بانک

class bank
{
private:
    string b_name;
    string b_code;
    vector<employee> employees;
    vector<client> clients;

    vector<manage> manager;

public:
    bank()
    {
        b_name = "F BANK";
        b_code = "000";
        client c("F", "F", "73/6/6", "300", "300", 12);
        clients.push_back(c);

        employee e("a", "a", "52/8/6", "002", "002", 200, 900);
        employees.push_back(e);

        manage m("Faeze", "Alizade", "1381/11/17", "001", "001", 100, 100);
        manager.push_back(m);
    }

    void creat_account(string name_, string family_, string date_, string username_, string password_, unsigned long long c_nationalcode_);
    void remove_account(int number, unsigned long long i);

    void active_account(string username_, string password_);

    void client_information(unsigned long long c_national);
    void client_information(int i);
    void accounts_information(int i);

    void employee_information(unsigned int e_num);
    void employee_information(int i);

    void add_employee(string name_, string family_, string date_, string username_, string password_, unsigned int e_personnum_, unsigned int e_salary_);
    void remove_employee(unsigned int e_num);

    int login_e(string p, string u);
    int login_maneger(string p, string u);
    int login_client(string p, string u);

    void increse_account(unsigned long long money, int i, int j);
    void reduce_account(unsigned long long money, int i, int j);

    void offhour(int asked_hour, int i) { employees[i].offhour(asked_hour); }
    void overtime(int asked_overtime, int i) { employees[i].overtime(asked_overtime); }
};

void bank::creat_account(string name_, string family_, string date_, string username_, string password_, unsigned long long c_nationalcode_)
{
    int num;
    string day;
    unsigned long long am;
    client c(name_, family_, date_, username_, password_, c_nationalcode_);

    for (int i = 0; i < clients.size(); i++)
    {
        if (password_ == clients[i].get_password() && username_ == clients[i].get_username())
        {
            cout << "\nThe number of account:\n";
            cin >> num;
            cout << "\nWhat is the date of today?\n";
            cin >> day;
            do
            {
                cout << "\nHow much money do you want to pay?\n";
                cin >> am;
            } while (am < 50);

            clients[i].add_account(num, c_nationalcode_, day, am);

            cout << "FINISH";

            return;
        }
    }

    cout << "\nThe number of account:\n";
    cin >> num;
    cout << "\nWhat is the date of today?\n";
    cin >> day;
    do
    {
        cout << "\nHow much money do you want to pay?\n";
        cin >> am;
    } while (am < 50);

    c.add_account(num, c_nationalcode_, day, am);

    clients.push_back(c);

    cout << "FINISH!";
}

void bank::remove_account(int number, unsigned long long nationalcode)
{
    int s;

    for (int i = 0; i < clients.size(); i++)
    {
        if (nationalcode == clients[i].get_national())
        {
            s = clients[i].remove_account(number);
            if (s == 0)
            {
                clients.erase(clients.begin() + i);
            }
            else if (s == -1)
            {
                cout << "\nThere isn't this account.\n";
            }
            return;
        }
    }
}

void bank::active_account(string username_, string password_)
{
    for (int i = 0; i < clients.size(); i++)
    {
        if ((password_ == clients[i].get_password()) && (username_ == clients[i].get_username()))
        {
            char n2;
            int code;
            cout << "\nDo you want to activate your account?y/n \n";
            cin >> n2;
            cout << "\nWhat's your account number?\n";
            cin >> code;

            for (int j = 0; j < clients[i].get_size(); j++)
            {
                if (clients[i].get_num_account(j) == code)
                {
                    if (n2 == 'y' || n2 == 'Y')
                    {
                        clients[i].activate(j);
                    }
                    else
                    {
                        clients[i].inactive(j);
                    }
                    return;
                }
            }
        }
    }
}

void bank::client_information(unsigned long long c_national)
{
    for (int i = 0; i < clients.size(); i++)
    {
        if (clients[i].get_national() == c_national)
        {
            clients[i].show_client();
            return;
        }
    }
}

void bank::client_information(int i)
{
    clients[i].show_client();
}

void bank::accounts_information(int i)
{
    clients[i].show_accounts();
}

void bank::employee_information(unsigned int e_num)
{
    for (int i = 0; i < employees.size(); i++)
    {
        if (employees[i].get_e_num() == e_num)
        {
            employee_information(i);
            return;
        }
    }
    cout << "error!";
}

void bank::employee_information(int i)
{
    cout << "\n_____________________";
    cout << "\nName: " << employees[i].get_name();
    cout << "\nFamily: " << employees[i].get_family();
    cout << "\nBirthday: " << employees[i].get_date();
    cout << "\nSalary: " << employees[i].get_e_salary();
    cout << "\nPersonal number: " << employees[i].get_e_num();
    cout << "\nOff hours: " << employees[i].get_e_off();
    cout << "\nOver time: " << employees[i].get_e_over();
    cout << "\nPassword: " << employees[i].get_password();
    cout << "\nUsername: " << employees[i].get_username();
    cout << "\n-------------------------\n";
}

void bank::add_employee(string name_, string family_, string date_, string username_, string password_, unsigned int e_personnum_, unsigned int e_salary_)
{
    employee e(name_, family_, date_, username_, password_, e_personnum_, e_salary_);
    employees.push_back(e);
}

void bank::remove_employee(unsigned int e_num)
{
    for (int i = 0; i < employees.size(); i++)
    {
        if (e_num == employees[i].get_e_num())
        {
            employees.erase(employees.begin() + i);
            cout << "FINISH!";
            return;
        }
    }
}

int bank::login_e(string p, string u)
{
    for (int i = 0; i < employees.size(); i++)
    {
        if (p == employees[i].get_password() && u == employees[i].get_username())
        {
            return i;
        }
    }

    return -1;
}

int bank::login_maneger(string p, string u)
{
    for (int i = 0; i < manager.size(); i++)
    {
        if (p == manager[i].get_password() && u == manager[i].get_username())
        {
            return i;
        }
    }

    return -1;
}

int bank::login_client(string p, string u)
{
    for (int i = 0; i < clients.size(); i++)
    {
        if (p == clients[i].get_password() && u == clients[i].get_username())
        {
            return i;
        }
    }

    return -1;
}

void bank::increse_account(unsigned long long money, int i, int j)
{
    clients[j].increse(money, i);
}

void bank::reduce_account(unsigned long long money, int i, int j)
{
    clients[j].reduce(money, i);
}

int main()
{
    bank m;

    char n1 = '0';

    while (n1 != 'q')
    {
        cout << "\n**MENU** \n\n";
        cout << "  1.employee \n  2.client \n\n  q-exit \n\n\n";

        cin >> n1;

        switch (n1)
        {

        case '1':
        {
            string p, u;
            cout << "\nEnter your password: \n";
            cin >> p;

            cout << "\nEnter your username: \n";
            cin >> u;

            int n3;
            n3 = m.login_e(p, u);
            if (n3 == -1)
            {
                int n4;
                n4 = m.login_maneger(p, u);
                if (n4 == -1)
                {
                    break;
                }
                else
                { // manager
                    char n6 = '0';
                    while (n6 != 'q')
                    {
                        cout << "\n**\nMENU OF MANAGER\n";
                        cout << "1.asking leave\n2.asking overtime\n3.show personal information\n4.show a client information by nationalcode\n5.creat an account for a client\n6.delete an account\n";
                        cout << "\n7.show an employee information by personalcod\n8.add an employee\n9.fire an employee\nq.exit\n";
                        cin >> n6;

                        switch (n6)
                        {
                        case '1':
                        {
                            int n14;
                            cout << "\nHow many hours off do you want?\n";
                            cin >> n14;

                            m.offhour(n14, n4);
                            break;
                        }
                        case '2':
                        {
                            int n15;
                            cout << "\nHow many hours of overtime do you want?\n";
                            cin >> n15;

                            m.overtime(n15, n4);

                            break;
                        }
                        case '3':
                        {
                            m.employee_information(n4);
                            break;
                        }
                        case '4':
                        {
                            unsigned long long n16;
                            cout << "\nEnter client's national code: \n";
                            cin >> n16;

                            m.client_information(n16);

                            break;
                        }
                        case '5':
                        {
                            string name, family, date, username, password;
                            unsigned long long nationalcode;

                            cout << "\n~~~~~~~\nACCOUNT FORM\n";
                            cout << "    name: ";
                            cin >> name;
                            cout << "\n    family: ";
                            cin >> family;
                            cout << "\n    birthday: ";
                            cin >> date;
                            cout << "\n    username: ";
                            cin >> username;
                            cout << "\n    password: ";
                            cin >> password;
                            cout << "\n    national code: ";
                            cin >> nationalcode;

                            m.creat_account(name, family, date, username, password, nationalcode);
                            break;
                        }
                        case '6':
                        {
                            int num;
                            unsigned long long nationalcode;
                            cout << "\nnational code: \n";
                            cin >> nationalcode;
                            cout << "\naccount number: \n";
                            cin >> num;

                            m.remove_account(num, nationalcode);

                            break;
                        }
                        case '7':
                        {
                            unsigned int p_code;
                            cout << "\nEnter personal code of an employee:\n";
                            cin >> p_code;

                            m.employee_information(p_code);

                            break;
                        }
                        case '8':
                        {
                            string name, family, date, username, password;
                            unsigned int e_num, e_salary;

                            cout << "\n~~~~~~~\n EMPLOYEE FORM\n";
                            cout << "    name: ";
                            cin >> name;
                            cout << "\n    family: ";
                            cin >> family;
                            cout << "\n    birthday: ";
                            cin >> date;
                            cout << "\n    username: ";
                            cin >> username;
                            cout << "\n    password: ";
                            cin >> password;
                            cout << "\n    person number: ";
                            cin >> e_num;
                            cout << "\n    salary: ";
                            cin >> e_salary;

                            m.add_employee(name, family, date, username, password, e_num, e_salary);
                            break;
                        }
                        case '9':
                        {
                            unsigned int number;

                            cout << "\n Enter employee's personal number: \n";
                            cin >> number;

                            m.remove_employee(number);
                            break;
                        }

                        case 'q':
                        {
                            break;
                        }

                        default:
                            break;
                        }
                    }
                }
            }
            else
            { // employee
                char n5 = '0';
                while (n5 != 'q')
                {
                    cout << "\n**\nMENU OF EMPLOYEE\n";
                    cout << "1.asking leave\n2.asking overtime\n3.show personal information\n4.show a client information by nationalcode\n5.creat an account for a client\n6.delete an account\nq.exit\n";
                    cin >> n5;

                    switch (n5)
                    {
                    case '1':
                    {
                        int n14;
                        cout << "\nHow many hours off do you want?\n";
                        cin >> n14;

                        m.offhour(n14, n3);
                        break;
                    }
                    case '2':
                    {
                        int n15;
                        cout << "\nHow many hours of overtime do you want?\n";
                        cin >> n15;

                        m.overtime(n15, n3);

                        break;
                    }
                    case '3':
                    {
                        m.employee_information(n3);
                        break;
                    }
                    case '4':
                    {
                        unsigned long long n16;
                        cout << "\nEnter client's national code: \n";
                        cin >> n16;

                        m.client_information(n16);

                        break;
                    }
                    case '5':
                    {
                        string name, family, date, username, password;
                        unsigned long long nationalcode;

                        cout << "\n~~~~~~~\nACCOUNT FORM\n";
                        cout << "    name: ";
                        cin >> name;
                        cout << "\n    family: ";
                        cin >> family;
                        cout << "\n    birthday: ";
                        cin >> date;
                        cout << "\n    username: ";
                        cin >> username;
                        cout << "\n    password: ";
                        cin >> password;
                        cout << "\n    national code: ";
                        cin >> nationalcode;

                        m.creat_account(name, family, date, username, password, nationalcode);
                        break;
                    }
                    case '6':
                    {
                        int num;
                        unsigned long long nationalcode;
                        cout << "\nnational code: \n";
                        cin >> nationalcode;
                        cout << "\naccount number: \n";
                        cin >> num;

                        m.remove_account(num, nationalcode);

                        break;
                    }
                    case 'q':
                    {
                        break;
                    }

                    default:
                        break;
                    }
                }
            }

            break;
        }

        case '2':
        {
            string p, u;
            cout << "\nEnter your password: \n";
            cin >> p;

            cout << "\nEnter your username: \n";
            cin >> u;

            int n7;
            n7 = m.login_client(p, u);
            if (n7 == -1)
            {
                break;
            }
            else
            { // client
                char n8 = 0;
                while (n8 != 'q')
                {
                    cout << "\n**\nMENU OF CLIENT\n";
                    cout << "1.increase account credit\n2.get money\n3.show information\nq.exit\n";
                    cin >> n8;

                    switch (n8)
                    {
                    case '1':
                    {
                        int n10, n11;
                        cout << "\nEnter account number\n";
                        cin >> n10;
                        cout << "\nEnter money\n";
                        cin >> n11;

                        m.increse_account(n11, n10, n7);

                        break;
                    }
                    case '2':
                    {
                        int n12, n13;
                        cout << "\nEnter account number\n";
                        cin >> n12;
                        cout << "\nEnter money\n";
                        cin >> n13;

                        m.reduce_account(n13, n12, n7);

                        break;
                    }
                    case '3':
                    {
                        int n9;
                        cout << "1.personal information\n2.accounts\n";
                        cin >> n9;

                        switch (n9)
                        {
                        case 1:
                        {
                            m.client_information(n7);
                            break;
                        }
                        case 2:
                        {
                            m.accounts_information(n7);
                            break;
                        }

                        default:
                            break;
                        }

                        break;
                    }
                    case 'q':
                    {
                        break;
                    }

                    default:
                        break;
                    }
                }
            }

            break;
        }

        case 'q':
        {
            return 0;
        }

        default:
            break;
        }
    }

    getch();
    return 0;
}