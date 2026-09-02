#include <string>
#include <iostream>
#pragma once//只加载一次
using namespace std;

class User {
public:
    // 有无参构造函数
    User();
    User(const string& acount, const string& name, const string& createTime);
 
    void setPassword(const string& password);

    // 检验天数是否合法
    bool setLast7Days(int days, int d);

    // 打印用户信息 
    void displayInfo() const;

public:  
    string acount;
    string name;
    int loginDays = 0;
    bool isNewUser = true;
    int last7daysL[7] = { 0 };
    string createTime;
    int id = 0;
    string state = "disactive";

private:
    string password;  
};