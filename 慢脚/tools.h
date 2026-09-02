#pragma execution_character_set("utf-8")
#include <iomanip>   
#include <vector>
#include <thread>
#include <iostream> 
#include <fstream>
#include <ctime>
#include <sstream>
#include <mutex>
#include "user.h"
#include "creatNewAcount.h"
using namespace std;
bool validateAccount(string acount, string name, string password);//检验账号，用户名，密码是否合法
bool isHRAcount(string account);//风险词检查
string encryptPassword( string password );//加密密码
string decryptPassword(string encrypted);//解密密码
void buildWelcomeMessage(string name);//欢迎
bool isActiveUser(const User& u);//检验是否可以登录
void printBigWelcome();// 超大欢迎
void saveAcount(const User& u, string codedPassword);//save
void  greatLine();//必不可少的华丽的分割线
string trim(const string& str);//去掉前后空格
string checkUserName(string name, const string& sensitive); //检查用户名是否包含敏感词
std::vector<string> split(string line, char delimiter);//拆分
void readFileLineByLine(const string& filename);//读取并输出
std::vector<string> creatAcountI(int* pGlobalId);//输入创建账号
//无输入创建
User creatAcountI(string account, string name, string password, int* pGlobalId);
