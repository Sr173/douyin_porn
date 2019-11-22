// http_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "cpr/cpr.h"
#include <locale>
#include "md5.h"
#include "json/json.h"
#include "url_encode.h"
#include "std_expansion.h"
#include <fstream>
#include "base64.h"

#pragma comment(lib , "cpr.lib")
#pragma comment(lib , "libcurl-d_imp.lib")
#pragma comment(lib , "jsoncpp.lib")

const int appid = 2124529448;
const auto appkey = "iMrvcy9tYbszACe2";

//const int appid = 10000;
//const auto appkey = "a95eceb1ac8c24ee28b70f7dbba912bf";

struct pic_porn_point {
	std::string data;
};

std::string read_file_base64(std::string path)
{
	std::ifstream infile;
	infile.open(std::string(path), std::ios::in | std::ios::binary | std::ios::ate);
	std::string data;
	data.resize(infile.tellg());
	int file_size = infile.tellg();
	infile.seekg(0, std::ios::beg);
	infile.read(const_cast<char*>(data.data()), file_size);
	infile.close();
	return base64_encode(reinterpret_cast<unsigned char const*>(data.data()), data.size());
}

pic_porn_point check_pic_is_porn(std::string path)
{
	pic_porn_point ppp;
	Json::Value value;
	value["app_id"] = std::to_string(appid);
	value["time_stamp"] = std::to_string(time(0));
	value["nonce_str"] = []() {
		std::string temp = "";
		srand(time(0));
		for (int i = 0; i < 10; i++) temp += char(rand() % ('Z' - 'A') + 'a');
		return temp;
	}();
	value["image"] = read_file_base64("C:\\Users\\admin\\Desktop\\IMG_0892(20191122-100233).png");
	std::string sign_str;
	for (const auto& key : value.getMemberNames()) {
		if (value[key].asString() != "")
			sign_str += key + '=' + url_encode(value[key].asString()) + '&';
	}
	sign_str += std::string("app_key=") + appkey;

	
	auto md5 = MD5(sign_str).toStr();
	value["sign"] = std::string_toupper(md5);

	auto post_data = std::string();
	for (const auto& key : value.getMemberNames()) {
		if (value[key].asString() != "")
			post_data += key + '=' + url_encode(value[key].asString()) + '&';
	}
	
	//std::cout << post_data << std::endl;
	auto r = cpr::Post(cpr::Url{ "https://api.ai.qq.com/fcgi-bin/vision/vision_porn" },
		cpr::VerifySsl(false),
		cpr::Body(post_data)
		);
	std::cout << r.text << std::endl;
	return ppp;
}

int main()
{
	check_pic_is_porn("");
	Json::Value value;

	value["AB"] = "CD";
	value["DD"] = "CD";
	value["AC"] = "CD";

	for (const auto& pair : value.getMemberNames()) {
		std::cout << value[pair].asString() << std::endl;
	}
	
	system("chcp 65001");
	
	auto r = cpr::Get(
		cpr::Url{ "https://www.iesdouyin.com/share/user/63169086371" },
		cpr::VerifySsl(false) ,
		cpr::UserAgent("Mozilla/5.0 (iPad; CPU OS 6_0 like Mac OS X) AppleWebKit/536.26 (KHTML, like Gecko) Version/6.0 Mobile/10A5376e Safari/8536.25")
	);
	auto start = r.text.find("tac=");
	auto end = r.text.find("</script>", start);
	auto tac = r.text.substr(start, end - start);
	
	std::cout << tac << std::endl;

	auto r1 = cpr::Post(
		cpr::Url{ "http://119.23.8.232:8888" },
		cpr::Body(tac.data(), tac.length())
	);

	std::cout << r1.text << std::endl;

	auto like_uri = std::string() + "https://www.iesdouyin.com/web/api/v2/aweme/like/?"
		"user_id=63169086371&sec_uid=&count=21&max_cursor=0&aid=1128&_signature="
		+ r1.text + 
		"&dytk=ec509a9933a542deb54f12d5825b3365";

	std::cout << like_uri << std::endl;
	
	auto result = cpr::Get(
		cpr::Url{ like_uri },
		cpr::VerifySsl(false),
		cpr::UserAgent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.108 Safari/537.36")
	);

	std::cout << result.text << std::endl;
}