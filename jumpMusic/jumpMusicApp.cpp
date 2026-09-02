#pragma execution_character_set("utf-8")
#include "jsonFile.h"
#include "tools.h"
using namespace std;

int main() {
	SetConsoleOutputCP(65001);
	//初始化获取信息
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	CONSOLE_CURSOR_INFO cbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbi);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	setCursorVisible(cbi, false);
	//主流程
	//printBigWelcome();
	cout << "欢迎来到跳音流量观察台\n当前身份：后端组 SOC 实习生\n负责人：qizao" << endl;
	int globalId = 0;//全局id
	int* pID = &globalId;
	std::vector<Videos > allVideos;
	vector<string> showList;//用于展示名称
	
 
	//读取json文件
	std::ifstream inFile("all_videos.json");
	json loadedData;
	inFile >> loadedData;//写入
	inFile.close();
	for (size_t i = 0; i < loadedData.size(); i++)
	{
		allVideos.push_back(readFromJson(loadedData[i]));
		showList.push_back(allVideos[i].getTitle());
		writeLog("读取到视频："+ allVideos[i].getTitle());
	}
 

	while (true) {
		greatLine();
		cout << "选择你要进行的操作" << endl;
		greatLine();

		std::vector<string> menu1 = {
			"1. 添加一条内容数据",
			"2. 查看所有内容数据",
			"3. 计算并展示流量等级",
			"4. 搜索指定标题或作者",
			"5. 所有标签排序",
			"6. 流量分数排行",
			"7. 平台数据对比", 
			"8. 清空日志",
			"0. 退出系统" };
		switch (menu(cbi, csbi, menu1, true)) {
		case 0: {
			Videos v = createViedos(csbi, cbi, pID);
			allVideos.push_back(v);
			showList.push_back(v.getTitle());//便于2
			loadedData.push_back(writeToJson(v));
			//保存
			std::ofstream outFile("all_videos.json");
			outFile << std::setw(4) << loadedData << std::endl;

			outFile.close();
			break;
		}
		case 1: {
			if (showList.size() == 0) {
				cout << "当前还没有内容数据，运营同学还没开始发疯。" << endl;
				break;
			}
			int choiced = menu(cbi, csbi, showList);
			allVideos[choiced].showInfo(csbi);
			break;
		}
		case 2: {
			int choiced = menu(cbi, csbi, showList);
			cout << "流量等级:" << judgmentLevel(calculateTrafficScore(allVideos[choiced])) << endl;
			break;
		}
		case 3:{
			vector<Videos> findedList;
			cout << "你要查找的关键词:";
			string target = inputBox(csbi, cbi);
			for (size_t i = 0; i < showList.size(); i++)
			{
				if (findSometing(allVideos[i], target))
				{
					findedList.push_back(allVideos[i]);
				}
			}
			if (findedList.size()==0)
			{
				writeLog("未找到信息");
				cout << "未找到" << endl;
			}
			else {
				cout << "查找结果" << endl;
				for (Videos v:findedList)
				{
					cout<<"标题：" << v.getTitle() << endl;
					cout << "作者：" << v.getAuthor() << endl;
					greatLine();
				}
			}
			//int choiced = menu(cbi, csbi, showList);
			break;
		}
		case 4: {
			
			//所有标签排序
			std::unordered_map<std::string, int>  allTags;
			std::vector<string> allTagsN;
			for (size_t i = 0; i < allVideos.size(); i++)
			{
				std::vector<string> tags = allVideos[i].getTags();
				for (string tag : tags)
				{
					
					allTags[tag] = allTags[tag] + 1;
					if (std::ranges::find(allTagsN, tag) == allTagsN.end()) {
						allTagsN.push_back(tag);
					}	
				}
			}
			int max = allTagsN.size();
			vector<string> temp;
			string tempN;
			int tempCount = -1;
			for (size_t i = 0; i < max; i++)
			{
				//找到最大
				for (string n : allTagsN) {
					if (allTags[n] > tempCount)
					{
						tempCount = allTags[n];
						tempN = n;

					}
				}
				temp.push_back(tempN );
				allTagsN.erase(std::ranges::find(allTagsN, tempN));//删除已经找过的
				tempCount = -1;
			}
			for (string n : temp) {
				checkLength(10, csbi);
				cout << n << " : " << allTags[n] << endl;
			}
			
			break;
		}
		case 5: {
			for (size_t i = 0; i < allVideos.size()-1; i++)
			{
				for (size_t j = i; j < allVideos.size()-1; j++)
				{
					if(calculateTrafficScore(allVideos[i]) < calculateTrafficScore(allVideos[j]))
					{
						std::swap(allVideos[i], allVideos[j]);
					}
				}
			}
			checkLength(9, csbi);
			for (size_t i = 0; i < allVideos.size(); i++)
			{
				cout << "TOP" << i + 1 << ":" << allVideos[i].getTitle() << " 流量分数:" << calculateTrafficScore(allVideos[i]) << endl;

			}
			break;
		}
		case 6:
			platformComparison(allVideos,csbi);
			break;
		case 7: {
			ofstream file("log.txt", ios::app);
			file << "";
			file.close();
		}
		case 8:
			cout << "退出";
			std::system("pause");
			return 0;
			break;

		}


	}


	std::system("pause");
	return 0;
}
