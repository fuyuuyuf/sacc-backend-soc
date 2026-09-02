#pragma execution_character_set("utf-8")
#include <mutex>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <cstring>
#include <thread>
#include <iomanip>
#include <vector>
#include <iostream>
#include "tools.h"
#include <fstream>
#include <ctime>
#include <sstream>
#include <string>
#include "user.h"
#include "display.h"
#include "creatNewAcount.h"
#pragma comment(lib, "ws2_32.lib")
using	namespace std;
//有参创建
extern std::mutex mtx;
int main() {
	system("chcp 65001 > nul");
	//创建一个全局变量存储id
	int globalId = 1;
	int* pGlobalId = &globalId;
	/*
   //账户，用户名， 密码
   user qizao;
   try {
	   qizao = creatNewAcount("qizao", "Qizao", "pa11111111", pGlobalId);

   }
   catch (const exception& e) {
	   // 使用 what() 获取错误信息
	   cout << "错误内容：" << e.what() << endl;
	   return 0;
   }

   greatLine();
   //登录几次
   cout << "day1登录次数：" << qizao.last7daysL[0] << endl;
   cout << "day7登录次数：" << qizao.last7daysL[6] << endl;

   //修改输出第三天
   qizao.setLast7Days(2, 9999);
   cout << "day3登录次数：" << qizao.last7daysL[2] << endl;
   greatLine();
   //输出账号信息
   cout << "账号：" << qizao.acount << endl;
   displayUserInfo(qizao);

   greatLine();

   //循环批量创建账号
   std::vector<user> numbers;
   string acountName[10] = { "gunmu","root","","qizao","qizao1","qizao2","qizao3","qizao4","risk_user","qizao5" };
   int n = 0;
   int validAccount = 0;
   while (acountName[n] != "risk_user") {
	   try {
		   user newUser = creatNewAcount(acountName[n], "全都是qizao", "password", pGlobalId);
		   numbers.push_back(newUser);
		   cout << "成功创建账号：" << newUser.acount << endl;
		   validAccount++;
	   }
	   catch (const exception& e) {
		   cout << "创建账号失败：" << acountName[n] << "，错误内容：" << e.what() << endl;
	   }
	   n++;
   }
   cout << "成功创建个数：" << validAccount << endl;

   cout << "加密密码：" << encryptPassword("password") << endl;
   cout << "解密密码：" << decryptPassword(encryptPassword("password")) << endl;
   greatLine();
 */
 /*
 //准备信息
 cout<< "请输入账户 ：" ;
 string account;
 cin >> account;
 cout << "请输入用户名：";
 string name;
 cin >> name;
 cout << "请输入密码 ：";
 string password;
 cin >> password;
 //检验信息
 cout << "正在检验信息..." << endl;
 validateAccount(account, name, password);
 //加密
 string codedPassword = encryptPassword(password);
 //创建
 user newQizao = creatNewAcount(account, name, password, pGlobalId);
 //保存到savedInfo.txt
 std::ofstream outFile("savedInfo.txt");

 if (outFile.is_open()) {
	 outFile << "账号：" << newQizao.acount << std::endl;
	 outFile << "用户名: " << newQizao.name << std::endl;
	 outFile << "加密密码: " << codedPassword << std::endl;
	 outFile << "创建时间: " << newQizao.createTime << std::endl;
	 outFile << "id " << newQizao.id << std::endl;

	 outFile.close();
	 std::cout << "文件保存成功！" << std::endl;
 }
 else {
	 std::cerr << "无法打开文件！" << std::endl;
 }
 buildWelcomeMessage(name);
 //输出信息
 cout << "账号：" << newQizao.acount << endl;
 cout << "用户名：" << newQizao.name << endl;
 cout << "加密密码：" << codedPassword << endl;
 cout << "创建时间：" << newQizao.createTime << endl;
 cout << "id：" << newQizao.id << endl;
 */
 /*
 std::vector<User> numbers1;//存放批量创建账号
 for (int i = 0;i < 4;i++) {
	 string account = "newQizao" + to_string(i);
	 string name = "Qizao" + to_string(i);
	 string password = "woshiqizao";

	 validateAccount(account, name, password);
	 //加密
	 string codedPassword = encryptPassword(password);
	 //创建
	 User newQizao = creatNewAcount(account, name, password, pGlobalId);
	 numbers1.push_back(newQizao);
 }
 numbers1[1].state ="active";//状态更改
 for (const User& u : numbers1)
 {
	 cout << "账号：" << u.acount << "，状态：" << u.state << endl;
 }
 */
 //主流程
/*
printBigWelcome();
	std::ofstream("savedInfo.txt").close();//清空
	greatLine();
	// 创建账户方法
	 //无参输入创建creatAcountI(pGlobalId);

	std::vector<std::thread> threads;
	creatAcountI("qizao","qizao111","qizao123",pGlobalId);
	//记录初始个数
	int temp = *pGlobalId;
	for (size_t i = 0; i < 6; i++)
	{
		threads.emplace_back([=]() {
			creatAcountI(std::string("qizao") + std::to_string(i), "qizao" + std::to_string(i), "qizao123", pGlobalId);
			});
	}
	for (auto& t : threads) {
		if (t.joinable()) {
			t.join();  // 阻塞等待每个线程结束
		}
	}
	cout << "创建个数：" << *pGlobalId - temp << endl;
	temp = 0;
	greatLine();

	//读取测试
	readFileLineByLine("savedInfo.txt");
*/
	User test = creatAcountI("qizao123","qizao123","321qizao",pGlobalId);
	WSADATA wsaData;
	// 初始化 Winsock 2.2
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "WSAStartup failed" << std::endl;
		return 1;
	}
	// 创建 socket
	SOCKET clientFd = socket(AF_INET, SOCK_STREAM, 0);
	if (clientFd == INVALID_SOCKET) {
		std::cout << "创建 socket 失败" << std::endl;
		WSACleanup();
		return 1;
	}
	sockaddr_in serverAddress{};
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);

	// 转换 IP 地址（Windows 中 inet_pton 需要 ws2tcpip.h）
	if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
		std::cout << "IP 地址无效" << std::endl;
		closesocket(clientFd);
		WSACleanup();
		return 1;
	}
	// 连接服务器
	if (connect(clientFd, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
		std::cout << "连接服务端失败" << std::endl;
		closesocket(clientFd);
		WSACleanup();
		return 1;
	}
	// 发送消息
	std::string message = test.name;
	send(clientFd, message.c_str(), message.size(), 0);

	// 接收响应
	char buffer[1024]{};
	int bytes = recv(clientFd, buffer, sizeof(buffer) - 1, 0);

	if (bytes > 0) {
		std::cout << "收到服务端响应：" << buffer << std::endl;
	}

	// 清理
	closesocket(clientFd);
	WSACleanup();


	system("pause");
 
	return 0;
}