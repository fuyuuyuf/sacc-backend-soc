#pragma execution_character_set("utf-8")
#include "tools.h"//单独拎出来
std::mutex mtx;
//风险识别
bool isHRAcount(string account) {
	string riskWords[] = { "gunmu","root","test" };//风险
	for (int i = 0; i < size(riskWords); i++) {
		if (account.find(riskWords[i]) != string::npos) {
			return true;
		}
	}
	return false;
}
//账号检测
bool validateAccount(string acount, string name, string password) {
	if (name.empty()) {
		throw runtime_error("账号名不能为空");
		return false;
	}
	else if (acount.empty() || acount.length() == 0)
	{
		throw runtime_error("账号不能为空");
		return false;
	}
	else if (password.length() < 6) {
		throw runtime_error("密码长度不足");
		return false;
	}
	else if (isHRAcount(acount)) {
		//是检测风险词还是说意思时要给用户加一个属性是否blocked？
		//但现在不是才创建账号吗
		throw runtime_error("账号风险拦截");
		return false;
	}
	else {
		return true;
	}
}
//密码加密
string encryptPassword(string password) {
	// 1. 字符串反转
	reverse(password.begin(), password.end());

	// 2. 加固定前缀
	string prefix = "QIZAO_";//qizao
	password = prefix + password;

	// 3. 移位
	for (char& c : password) {
		if (isalpha(c)) {
			char base = isupper(c) ? 'A' : 'a';
			c = static_cast<char>((c - base + 3) % 26 + base);
		}
	}

	// 4.字符的ASCII值加3
	string encrypted = "";
	for (char c : password) {
		encrypted += static_cast<char>(c + 3);
	}

	return encrypted;
}
// 对应解密 
string decryptPassword(string encrypted) {
	// 字符的ASCII值减3 
	string password = "";
	for (char c : encrypted) {
		password += static_cast<char>(c - 3);
	}
	for (char& c : password) {
		if (isalpha(c)) {
			char base = isupper(c) ? 'A' : 'a';
			c = static_cast<char>((c - base - 3 + 26) % 26 + base);
		}
	}
	string prefix = "QIZAO_";//qizao
	if (password.substr(0, prefix.length()) == prefix) {
		password = password.substr(prefix.length());
	}
	reverse(password.begin(), password.end());

	return password;
}
// 欢迎信息
void buildWelcomeMessage(string name) {
	cout << "Hello World!   " << name << " 诞生了！" << endl;
};
// 检验是否可以登录
bool isActiveUser(const User& u) {
	return (u.state == "active") ? true : false;
}
//超大欢迎
void printBigWelcome() {
	std::cout << R"(
╔═══════════════════════════════════════════════════════════════╗
║                                                               ║
║   ██╗    ██╗███████╗██╗      ██████╗ ███████╗███╗   ███╗      ║
║   ██║    ██║██╔════╝██║     ██╔════╝ ██╔════╝████╗ ████║      ║
║   ██║ █╗ ██║█████╗  ██║     ██║  ███╗█████╗  ██╔████╔██║      ║
║   ██║███╗██║██╔══╝  ██║     ██║   ██║██╔══╝  ██║╚██╔╝██║      ║
║   ╚███╔███╔╝███████╗███████╗╚██████╔╝███████╗██║ ╚═╝ ██║      ║
║    ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚══════╝╚═╝     ╚═╝      ║
║                                                               ║
╚═══════════════════════════════════════════════════════════════╝
    )" << std::endl;
}
//保存账号信息
void saveAcount(const User& u, string codedPassword) {
	//保存到savedInfo.txt
	std::lock_guard<std::mutex> lock(mtx);
	std::ofstream outFile("savedInfo.txt", std::ios::app);

	if (outFile.is_open()) {
		outFile << "账号：" << u.acount << ",";
		outFile << "用户名：" << u.name << ",";
		outFile << "加密密码：" << codedPassword << ",";
		outFile << "创建时间：" << u.createTime << ",";
		outFile << "id：" << u.id << std::endl;

		outFile.close();
		//std::cout << "文件保存成功！" << std::endl;
	}
	else {
		std::cerr << "无法打开文件！" << std::endl;
	}
}
//必不可少的华丽的分割线
void  greatLine() {
	cout << "-----------------------------华丽分割线------------------------" << endl;
}
//去掉前后空格
string trim(const string& str) {
	// 找到第一个非空格字符索引
	size_t start = str.find_first_not_of(" ");
	if (start == string::npos) {
		return "";
	}
	// 找到最后一个非空格字符索引
	size_t end = str.find_last_not_of(" ");
	return str.substr(start, end - start + 1);
}
//检查用户名是否包含敏感词
string checkUserName(string name, const string& sensitive) {
	size_t index = name.find(sensitive);
	if (index != string::npos)
	{

		return	name.replace(index, sensitive.length(), string(sensitive.length() / 3, '*'));//中文单字长度3
	}
	return name;
}
//拆分方法
std::vector<string> split(string line, char delimiter) {
	std::vector<string> lines;
	std::string card;
	for (size_t i = 0; i < line.length(); i++)//遍历找到，断开，弹入lines
	{
		if (line[i] == delimiter)
		{
			lines.push_back(card);
			card = "";
		}
		else {
			card += line[i];
		}
	}
	lines.push_back(card);//结尾也加上
	return lines;
}
//读取并输出
void readFileLineByLine(const string& filename) {
	try {
	
		ifstream file(filename);
		if (!file.is_open()) {
			cerr << "无法打开文件: " << filename << endl;
			return;
		}
		string line;
		int lineNum = 0;

		while (getline(file, line)) {//循环读行
			lineNum++;
			std::vector<string> lines = split(line, ',');
			std::vector<string> info;
			for (string c : lines)
			{
				info.push_back(split(c, '：')[1]);//二次分割

			}
			//输出信息
			cout << "账号：" << info[0] << endl;
			cout << "用户名：" << info[1] << endl;
			cout << "加密密码：" << info[2] << endl;
			cout << "创建时间：" << info[3] << endl;
			cout << "id：" << info[4] << endl;

		}
		//通过lines再输出
		file.close();
	}
	catch (const exception& e) {
		cout << "出现错误" << e.what();
	}
}
//获取输入，单独放出来好看一点
std::vector<string> getI() {
	std::vector<string> info;
	cout << "请输入账户 ：";
	string account;
	getline(cin, account);
	account = trim(account);//去掉前后空格
	if (account.length() == 0)
	{
		cout << "错误：账号不能为空！" << endl;
		return info;
	}
	cout << "请输入用户名：";
	string name;
	getline(cin, name);
	cout << "请输入密码 ：";
	string password;
	cin >> password;
	info.push_back(account);
	info.push_back(name);
	info.push_back(password);
}
//获取输入的创建，返回关键信息，账户用户名，密码
std::vector<string> creatAcountI(int* pGlobalId) {
	//准备信息
	std::vector<string> info;
	info = getI();
	string account = info[0];
	string name = info[1];
	string password = info[2];
	//判断是否包含账号
	password = trim(password);
	if (password.find(account) != string::npos)
	{
		cout << "密码包含账号，高风险！" << endl;

	}
	//检验信息
	cout << "正在检验信息..." << endl;
	validateAccount(account, name, password);//有问题直接终止
	//创建
	User newQizao = creatNewAcount(account, name, password, pGlobalId);
	//保存到savedInfo.txt
	saveAcount(newQizao, encryptPassword(password));
	//欢迎
	buildWelcomeMessage(checkUserName(newQizao.name, "退款"));

	return info;
}
//有参创建
User creatAcountI(string account, string name, string password, int* pGlobalId) {
	
	//准备信息
	std::vector<string> info;
	//判断是否包含账号
	password = trim(password);
	if (password.find(account) != string::npos)
	{
		cout << "密码包含账号，高风险！" << endl;
	}
	//检验信息
	//cout << "正在检验信息..." << endl;
	validateAccount(account, name, password);//有问题直接终止
	//创建
	User newQizao = creatNewAcount(account, name, password, pGlobalId);
	//保存到savedInfo.txt
	saveAcount(newQizao, encryptPassword(password));
	//欢迎
	buildWelcomeMessage(checkUserName(newQizao.name, "退款"));

	return newQizao;
}