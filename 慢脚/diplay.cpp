#include "display.h"
#include "user.h"
//输出信息
void displayUserInfo(const User& u) {
	// 设置统一的边框宽度
	const int WIDTH = 50;
	const string BORDER_TOP = "+" + string(WIDTH - 2, '-') + "+";
	const string EMPTY_LINE = "|" + string(WIDTH - 2, ' ') + "|";

	// 顶 框
	cout << BORDER_TOP << endl;
	cout << "|" << string(18, ' ') << " 账号信息" << string(21, ' ') << "|" << endl;
	cout << BORDER_TOP << endl;

	// 账号信息 
	cout << "| 账号 (Account)  : " << left << setw(29) << u.acount << "|" << endl;
	cout << "| 用户名 (Name)   : " << left << setw(29) << u.name << "|" << endl;
	cout << "| 新用户          : " << left << setw(30) << (u.isNewUser ? "是" : "否") << "|" << endl;
	cout << "| 登录天数        : " << left << setw(29) << u.loginDays << "|" << endl;
	cout << BORDER_TOP << endl;

	// 最近7天登录统计 
	cout << "| 最近7天登录统计:" << string(31, ' ') << "|" << endl;

	// 第一行 
	cout << "|   Day1: " << setw(4) << u.last7daysL[0]
		<< "   Day2: " << setw(4) << u.last7daysL[1]
		<< "   Day3: " << setw(4) << u.last7daysL[2]
		<< string(9, ' ') << "|" << endl;

	//  第二行 
	cout << "|   Day4: " << setw(4) << u.last7daysL[3]
		<< "   Day5: " << setw(4) << u.last7daysL[4]
		<< "   Day6: " << setw(4) << u.last7daysL[5]
		<< string(9, ' ') << "|" << endl;

	cout << "|   Day7: " << setw(4) << u.last7daysL[6]
		<< string(35, ' ') << "|" << endl;

	// 底部边框
	cout << BORDER_TOP << endl;
}