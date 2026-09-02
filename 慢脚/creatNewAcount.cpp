#include "tools.h"
extern std::mutex mtx;
User creatNewAcount(string acount, string name, string password, int* pId) {
	std::lock_guard<std::mutex> lock(mtx);
	User a;
	if (validateAccount(acount, name, password)) {
		cout << "账号校验通过" << endl;
		//检验通过再配置id，加上时间戳
		a.acount = acount;
		a.name = name;
		a.id = *pId;
		(*pId)++;
		time_t now = time(nullptr);//获取当前时间
		struct tm timeinfo = {};
		localtime_s(&timeinfo, &now);
		//转换为人看的
		std::ostringstream oss;
		oss << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");
		a.createTime = oss.str();


		return a;
	}

}