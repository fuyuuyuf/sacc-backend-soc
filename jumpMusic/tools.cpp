#include "tools.h"
//移动光标到指定位置
void gotoxy(int x, int y) {
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//输出彩色文字
void printColorfulText(string content, int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//获取控制台句柄
	SetConsoleTextAttribute(hConsole, color);//14浅黄6深 
	cout << content;
	SetConsoleTextAttribute(hConsole, 7);
}
//光标可视
void setCursorVisible(CONSOLE_CURSOR_INFO& cbi, bool visible) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cbi.bVisible = visible;
	SetConsoleCursorInfo(hConsole, &cbi);//设置
}
//标注输入
void colorOutput(CONSOLE_SCREEN_BUFFER_INFO& csbi, string input) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//调背景色 16b->取有用后8b的低4b(前景) +新的4背景 
	SetConsoleTextAttribute(hConsole, csbi.wAttributes & 0x0F | (8 << 4));
	cout << input << endl;
	SetConsoleTextAttribute(hConsole, csbi.wAttributes & 0x0F | (0 << 4));
}
//输入框
string inputBox(CONSOLE_SCREEN_BUFFER_INFO& csbi, CONSOLE_CURSOR_INFO& cbi) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD written;
	COORD writePos = { 0, (short)csbi.srWindow.Bottom };
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	COORD initCursorPos = csbi.dwCursorPosition;
	//  setCursorVisible(cbi, true);
	  //划线
	string clearLine(csbi.dwSize.X, ' ');
	string content(csbi.dwSize.X, '-');
	gotoxy(0, writePos.Y);
	//多加三行，后面直接覆盖
	checkLength(3, csbi);
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	writePos.Y--;//最后多endl ，--改个位置
	WriteConsoleOutputCharacterA(hConsole, content.c_str(), content.length(), writePos, &written);
	writePos.Y -= 1;
	gotoxy(3, writePos.Y);//移光标
	WriteConsoleOutputCharacterA(hConsole, "> ", 2, writePos, &written);
	writePos.Y -= 1;
	WriteConsoleOutputCharacterA(hConsole, content.c_str(), content.length(), writePos, &written);
	string input;
	getline(cin, input);
	//获取完清楚输入框
	for (size_t i = 0; i < 3; i++)
	{
		WriteConsoleOutputCharacterA(hConsole, clearLine.c_str(), clearLine.length(), writePos, &written);
		writePos.Y++;
	}
	//回到最初的位置
//	initCursorPos.Y -= 3;
	SetConsoleCursorPosition(hConsole, initCursorPos);

	colorOutput(csbi, input);
	setCursorVisible(cbi, false);
	return input;
}
//数据锁，保证不超范围
void numberLock(int& target, int min, int max) {
	if (target < min)
	{
		target = max;
	}
	else if (target > max) {
		target = min;
	}
}
//滚动菜单
//上下左右 72 80 75 77 enter 13
int menu(CONSOLE_CURSOR_INFO& cbi, CONSOLE_SCREEN_BUFFER_INFO& csbi, std::vector<string> enmuList, bool isS) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD written;
	COORD writePos = { 0, (short)csbi.srWindow.Bottom };
	string clearLine(csbi.dwSize.X, ' ');
	string greatLine(csbi.dwSize.X, '-');
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);//刷新，记录初始位置

	int page = (enmuList.size() + 3) / 4;

	vector< vector< string>> showList(page, std::vector<std::string>(0));
	checkLength(9, csbi);

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);//刷新，记录初始位置
	COORD initCursorPos = csbi.dwCursorPosition;
	//分页
	for (size_t i = 0; i < page; i++)
	{
		for (size_t j = i * 4; j < (enmuList.size() > 4 * (i + 1) ? 4 * (i + 1) : enmuList.size()); j++)
		{
			//保证覆盖
			string a(csbi.dwSize.X - enmuList[j].length(), ' ');
			showList[i].push_back(enmuList[j] + a);
		}
	}
	int pageNow = -1;
	int optionNow = 0;
	int getInput = 0;
	//刷新位置
	writePos = { 0, (short)csbi.srWindow.Bottom };
	writePos.Y -= 5;
	SetConsoleTextAttribute(hConsole, 7);//14浅黄6深 
	//采用颜色输入，不知道为什么不用颜色会变
	string tips = "方向键 左右切换页面 ；上下切换选项";
	gotoxy(0, writePos.Y);
	printColorfulText(tips, 7);
	gotoxy(0, writePos.Y + 1);
	printColorfulText(greatLine, 7);
	writePos.Y++;
	writePos.Y += 4;
	//循环开始，直到enter
	getInput = 77;//获取的输入
	WORD yellow = 6;
	WORD bright_yellow = 14;

	do
	{//对应操作

		if (getInput == 75 || getInput == 77)
		{
			pageNow += getInput == 77 ? 1 : -1;
			optionNow = 0;
			numberLock(pageNow, 0, page - 1);


		}
		else if (getInput == 72 || getInput == 80)
		{
			optionNow += getInput == 80 ? 1 : -1;
			numberLock(optionNow, 0, showList[pageNow].size() - 1);
		}
		//补足未满四项
		if (showList[pageNow].size() != 4)
		{
			for (int i = 0; i < 4 - showList[pageNow].size(); i++)
			{
				WriteConsoleOutputCharacterA(hConsole, clearLine.c_str(), clearLine.length(), writePos, &written);
				writePos.Y--;
			}

		}

		//开始显示，从下到上
		for (int i = showList[pageNow].size() - 1; i > -1; i--)
		{
			gotoxy(0, writePos.Y);
			if (i != optionNow)
			{
				printColorfulText(showList[pageNow][i], 6);
			}
			else
			{
				printColorfulText(showList[pageNow][i], 14);
			}

			writePos.Y--;
		}
		writePos.Y += 4;
		getInput = _getch();
	} while (getInput != 13);

	//特化
	if (isS) {
		for (size_t i = 0; i < 3; i++)
		{
			initCursorPos.Y--;
			WriteConsoleOutputCharacterA(hConsole, clearLine.c_str(), (short)clearLine.length(), initCursorPos, &written);

		}
	}

	SetConsoleCursorPosition(hConsole, initCursorPos);//复位
	// 清空内容
	for (size_t i = 0; i < 6; i++)
	{
		WriteConsoleOutputCharacterA(hConsole, clearLine.c_str(), (short)clearLine.length(), writePos, &written);
		writePos.Y--;
	}
	string str = showList[pageNow][optionNow];
	str.erase(remove(str.begin(), str.end(), ' '), str.end());//去掉多余空格 
	colorOutput(csbi, str);

	return  pageNow * 4 + optionNow;
}
void greatLine() {
	cout << "-------------------------------------------------" << endl;
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
// 检测最下面x行是否有空间，没有则扩至x
void checkLength(int max, CONSOLE_SCREEN_BUFFER_INFO& csbi) {
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	COORD initCursorPos = csbi.dwCursorPosition;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int botton = csbi.srWindow.Bottom;
	COORD writePos = { 0, (short)botton };
	COORD readPos = { (SHORT)0, (SHORT)botton };
	DWORD charsRead = 0;
	wchar_t* buffer = new wchar_t[csbi.dwSize.X + 1];
	//从下向上读取，出现非空开始扩展
	//  用宽字 。窄字竟然存不了
	int a = 0;//加行会向上滚动，位置是相对可视零点，后续复位要偏移
	for (int i = 0; i < max; i++)
	{
		ReadConsoleOutputCharacterW(hConsole, buffer, csbi.dwSize.X, readPos, &charsRead);
		buffer[charsRead] = L'\0';

		if (wcsspn(buffer, L" ") != csbi.dwSize.X)
		{
			gotoxy(0, botton);
			for (size_t j = 0; j < max - i; j++) {
				cout << " " << endl;
				readPos.Y++;
				a++;
			}

			gotoxy(0, initCursorPos.Y - a);
			delete[] buffer;//清理内存
			return;

		}
		readPos.Y--;
		initCursorPos.Y -= a;
		SetConsoleCursorPosition(hConsole, initCursorPos);//复位
		//writeLog("扩展行数："+a);
	}
	delete[] buffer;



}
 //接受int的输入框
int inputBoxInt(CONSOLE_SCREEN_BUFFER_INFO& csbi, CONSOLE_CURSOR_INFO& cbi) {
	string before;
	while (true) {
		try {
			return std::stoi(inputBox(csbi, cbi));
		}
		catch (exception e) {
			writeLog(e.what());
			cout << e.what() << "请重新输入" << endl;
			writeLog(e.what());
		}
	}

}
//输入创建
Videos createViedos(CONSOLE_SCREEN_BUFFER_INFO& csbi, CONSOLE_CURSOR_INFO& cbi, int* pID) {
	cout << "请输入标题:";
	string title = inputBox(csbi, cbi);
	cout << "请输入作者:";
	string name = inputBox(csbi, cbi);
	cout << "请选择发布平台:";
	Platform platform = static_cast<Platform>(menu(cbi, csbi, { "小蓝书","D站","跳音","慢脚" }));
	cout << "请输入播放量:";
	int views = inputBoxInt(csbi, cbi);
	cout << "请输入点赞数:";
	int likes = inputBoxInt(csbi, cbi);
	cout << "请输入评论数:";
	int reviews = inputBoxInt(csbi, cbi);
	cout << "请输入转发量:";
	int forwards = inputBoxInt(csbi, cbi);
	cout << "请输入收藏量:";
	int collections = inputBoxInt(csbi, cbi);
	cout << "请输入tags:";
	string tags = inputBox(csbi, cbi);
	Videos newV = Videos(*pID, tags, name, platform, views, likes, reviews, forwards, collections, tags);
	writeLog("视频"+title+"成功创建");
	cout << endl;
	return newV;
}
//获取信息
void Videos::showInfo(CONSOLE_SCREEN_BUFFER_INFO& csbi) {
	checkLength(19, csbi);
	cout << "========================================" << endl;
	cout << " 编号    : " << id << endl;
	cout << " 标题    : " << title << endl;
	cout << " 作者    : " << author << endl;
	cout << " 平台    : " << platformD[getPlatform()] << endl;
	cout << "----------------------------------------" << endl;
	cout << " 播放量  : " << views << endl;
	cout << " 点赞    : " << likes << endl;
	cout << " 评论    : " << reviews << endl;
	cout << " 转发    : " << forwards << endl;
	cout << " 收藏    : " << collection << endl;
	cout << "----------------------------------------" << endl;
	cout << " 标签    : ";
	for (string& t : tags)
	{
		cout << t << ",";
	}
	cout << endl;
	cout << "========================================" << endl;
}
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

float calculateTrafficScore(Videos v) {
	//播放量 * 0.4 + 点赞数 * 2 + 评论数 * 3 + 转发数 * 4 + 收藏数 * 5
	return v.getViews() * 0.4 + v.getLikes() * 2 + v.getReviews() * 3 + v.getForwards() * 4 + v.getCollection() * 5;

}

//字符串查找
bool findSometing(Videos v, string target) {
	if (v.getTitle().find(target) == string::npos) {

		return v.getAuthor().find(target) == string::npos ? false : true;
	};
	return true;
}

//判级
string judgmentLevel(float trafficS) {
	if (trafficS >= 0 && trafficS <= 999) {
		return "无人问津";
	}
	else if (trafficS >= 1000 && trafficS <= 9999) {
		return "有点水花";
	}
	else if (trafficS >= 10000 && trafficS <= 49999) {
		return "小爆一下";
	}
	else if (trafficS >= 50000 && trafficS <= 199999) {
		return "大爆预备";
	}
	else if (trafficS >= 200000) {
		return "爆款候选";
	}
	else {
		return "出错";
	}
}
// 算分
Di di = Di();
Bl bl = Bl();
Ju ju = Ju();
Sl sl = Sl();
float getTrafficScore(Videos v) {
	switch (v.getPlatform()) {
	case DILIDILI:
		return di.calculateTrafficScore(v);
	case BLUENOTE:
		return bl.calculateTrafficScore(v);
	case JUMPMUSIC:
		return ju.calculateTrafficScore(v);
	case SLOWFOOT:
		return sl.calculateTrafficScore(v);
	}
}
void platformComparison(vector<Videos> allVideos, CONSOLE_SCREEN_BUFFER_INFO& csbi) {
	//对所有内容进行分平台分析
	//分平台
	//D J B S
	vector<vector<Videos>> allPlatforms(4);
	for (Videos v : allVideos) {
		allPlatforms[v.getPlatform()].push_back(v);
	}
	int max = 0;
	Videos maxV;
	int sum = 0;
	float scoreT;
	string pName = "";
	for (vector<Videos> vV : allPlatforms)
	{
		if (vV.size() == 0)
		{
			writeLog("找不到信息 ");
		}
		else {

			pName = vV[0].platformD[vV[0].getPlatform()];
			checkLength(10, csbi);
			greatLine();
			cout << pName << "信息：" << endl;
			cout << "平台内容数量：" << vV.size() << endl;

			for (Videos v : vV) {
				//max
				scoreT = getTrafficScore(v);
				max = max > scoreT ? max : scoreT;
				maxV = v;
				//average
				sum += scoreT;
			}
			cout << "流量分最高的内容： " << maxV.getTitle() << "流量分：" << max << endl;
			cout << "平均流量分：" << max / vV.size() << endl;
			
			max = 0;
			sum = 0;
			scoreT = 0;//复位
			//平均 max 也可以直接把 6封装直接输出排行榜
		}

	}

}
//日志写入
void writeLog(string content) {
	ofstream file("log.txt", ios::app);
	if (file.is_open()) {
		time_t now = time(nullptr);//获取当前时间
		struct tm timeinfo = {};
		localtime_s(&timeinfo, &now);
		//转换为人看的
		std::ostringstream oss;
		oss << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");
		file << oss.str() << "  [INFO]" << content << endl;
		file.close();
	}
}