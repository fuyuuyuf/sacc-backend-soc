#include "user.h"
using namespace std;
//有无参构造函数
User::User() {
    loginDays = 0;
    isNewUser = true;
    id = 0;
    state = "disactive";
}
User::User(const string& acount, const string& name, const string& createTime) {
    this->acount = acount;
    this->name = name;
    this->createTime = createTime;
    loginDays = 0;
    isNewUser = true;
    id = 0;
    state = "disactive";
}

void User::setPassword(const string& password) {
    this->password = password;
}

bool User::setLast7Days(int days, int d) {
    last7daysL[days] = d;
    return true;
}

  