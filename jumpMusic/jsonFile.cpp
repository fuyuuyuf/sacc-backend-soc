#include "jsonFile.h"
//自动补全有点厉害，这两个全身自动补的
Videos readFromJson(const json& j) {
	int id = j.at("id").get<int>();
	string title = j.at("title").get<string>();
	string author = j.at("author").get<string>();
	Platform platform = static_cast<Platform>(j.at("platform").get<int>());
	int views = j.at("views").get<int>();
	int likes = j.at("likes").get<int>();
	int reviews = j.at("reviews").get<int>();
	int forwards = j.at("forwards").get<int>();
	int collection = j.at("collection").get<int>();
	string tags = j.at("tags").get<string>();
	return Videos(id, title, author, platform, views, likes, reviews, forwards, collection, tags);
}
json writeToJson(const Videos& v) {
	json j;
	j["id"] = v.getId();
	j["title"] = v.getTitle();
	j["author"] = v.getAuthor();
	j["platform"] = static_cast<int>(v.getPlatform());
	j["views"] = v.getViews();
	j["likes"] = v.getLikes();
	j["reviews"] = v.getReviews();
	j["forwards"] = v.getForwards();
	j["collection"] = v.getCollection();
	j["tags"] = v.getTags();
	return j;
}