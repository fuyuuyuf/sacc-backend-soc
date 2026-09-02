#pragma once
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <unordered_map>
#include <format>
#include <random>
#include  "json.hpp" 
#include <fstream>  
#include <iomanip> 
#include <windows.h>

using json = nlohmann::json;
using namespace std;
void gotoxy(int x, int y);
void printColorfulText(string content, int color);
void setCursorVisible(CONSOLE_CURSOR_INFO& cbi, bool visible);
void colorOutput(CONSOLE_SCREEN_BUFFER_INFO& csbi, string input);
string inputBox(CONSOLE_SCREEN_BUFFER_INFO& csbi, CONSOLE_CURSOR_INFO& cbi);
void numberLock(int& target, int min, int max);
int menu(CONSOLE_CURSOR_INFO& cbi, CONSOLE_SCREEN_BUFFER_INFO& csbi, std::vector<string> enmuList, bool isS = false);
void greatLine();
void printBigWelcome();
void checkLength(int max, CONSOLE_SCREEN_BUFFER_INFO& csbi);
enum Platform;
//平台枚举
enum Platform {
	DILIDILI,
	JUMPMUSIC,
	BLUENOTE,
	SLOWFOOT
};
//拆分方法
std::vector<string> split(string line, char delimiter);
//视频内容类
/**
 * @brief 视频信息管理类
 * @param id          视频ID
 * @param title       视频标题
 * @param author      视频作者
 * @param platform    发布平台
 * @param views       播放量
 * @param likes       点赞数
 * @param reviews     评论数
 * @param forwards    转发数
 * @param collection  收藏数
 * @param tags        视频标签 （vector<string>)
 */
class Videos {
public:
	string platformD[4] = { "D站" ,"跳音", "小蓝书", "慢脚" };//输出对应
	Videos() {};
	//有参构造
	Videos(int id, string title, string author,
		Platform platform, int views, int likes, int reviews,
		int forwards, int collection, string  tags)
		: id(id), title(title), author(author), platform(platform), views(views),
		likes(likes), reviews(reviews), forwards(forwards)
		, collection(collection), tags(split(tags, ','))
	{
		//cout << format("[INFO] 视频: {} 创建完成。保存完毕。", title) << endl;
	}
	void showInfo(CONSOLE_SCREEN_BUFFER_INFO& csbi);
	//get/set方法
	int getId() const { return id; }
	string getTitle() const { return title; }
	string getAuthor() const { return author; }
	Platform getPlatform() const { return platform; }
	int getViews() const { return views; }
	int getLikes() const { return likes; }
	int getReviews() const { return reviews; }
	int getForwards() const { return forwards; }
	int getCollection() const { return collection; }
	std::vector<string> getTags() const { return tags; }

	void setViews(int newViews) { views = newViews>0 ? newViews : 0; }
	void setLikes(int newLikes) { likes = newLikes>0 ? newLikes : 0; }
	void setReviews(int newReviews) { reviews = newReviews>0 ? newReviews : 0; }
	void setForwards(int newForwards) { forwards = newForwards>0 ? newForwards : 0; }
	void setCollection(int newCollection) { collection = newCollection>0 ? newCollection : 0	; }
private:
	int id;
	string title;
	string author;
	Platform platform;
	int views;
	int likes;
	int reviews;
	int forwards;
	int collection;
	std::vector<string> tags;





};
//整合信息
void platformComparison(vector<Videos> allVideos, CONSOLE_SCREEN_BUFFER_INFO& csbi);
//创作者类
class creater {
	string myLevel() {
		if (totalTrafficScore < 0) {
			return "数据异常";
		}
		else if (totalTrafficScore <= 10) {
			return "新人创作者";
		}
		else if (totalTrafficScore <= 99) {
			return "潜力创作者";
		}
		else if (totalTrafficScore <= 999) {
			return "热门创作者";
		}
		else {
			return "平台顶流";
		}
	}
public:
	string name;
	int	followerCount;
	int	contentCount;
	int	totalTrafficScore;
};
//PlatformG
class platformD {
public:
	platformD();
	platformD(Platform p, float nf1, int nf2, int nf3, int nf4) :platform(p), f1(nf1), f2(nf2), f3(nf3), f4(nf4) {
	}
	Platform platform;
	float f1;
	int f2;
	int f3;
	int f4;
	void setF(int nf1, int nf2, int nf3, int nf4) {
		f1 = nf1;
		f2 = nf2;
		f3 = nf3;
		f4 = nf4;
	}
	float calculateTrafficScore(Videos v) {
		return v.getViews() * f1 + v.getLikes() * f2 + v.getReviews() * f3 + v.getCollection() * f4;
	}

};
string judgmentLevel(float trafficS);
bool findSometing(Videos v, string target);
//平台参数
class Di : public platformD {
public:
	Di() : platformD(DILIDILI, 0.4, 2, 3, 5) {}
};
class Ju : public platformD {
public:
	Ju() : platformD(JUMPMUSIC, 0.5, 1.5, 2.5, 3.5) {}
};
class Bl : public platformD {
public:
	Bl() : platformD(BLUENOTE, 0.6, 1.2, 2.2, 3.2) {}
};
class Sl : public platformD {
public:
	Sl() : platformD(SLOWFOOT, 0.7, 1.1, 2.1, 3.1) {}
};
 
//算分
float calculateTrafficScore(Videos v);
float getTrafficScore(Videos v);
void writeLog(string content);
//处理接受的字符串转int的可以能问题
int inputBoxInt(CONSOLE_SCREEN_BUFFER_INFO& csbi, CONSOLE_CURSOR_INFO& cbi);
//输入创建
Videos createViedos(CONSOLE_SCREEN_BUFFER_INFO& csbi, CONSOLE_CURSOR_INFO& cbi, int* pID);