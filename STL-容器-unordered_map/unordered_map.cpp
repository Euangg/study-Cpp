#include<unordered_map>
#include<iostream>
using std::unordered_map;
using std::string;
using std::cout;
using std::endl;

//基本使用
void test1() {
	unordered_map<string, int>dict;

	dict["apple"] = 9;
	dict["pine"] = 9;
	dict["grape"] = 9;

	dict["pine"] = 55;

	for (auto& d : dict) {
		cout << d.first << ":" << d.second << endl;
	}


	cout << dict["asd"] << endl;//可以访问没有的
}

//初始化
void test2() {
	unordered_map<string, int>dict = { {"apple",0},{"pine",0}};

	dict["grape"] = 9;

	dict["pine"] = 55;

	for (auto& d : dict) {
		cout << d.first << ":" << d.second << endl;
	}
}

//某个键是否存在
void test3() {
	unordered_map<string, int>dict = { {"apple",0},{"pine",0} };

	if (dict.contains("applse")) { cout << "contain" << endl; }
	else { cout << "dont contain" << endl; }
}

//at读取
void test4() {
	unordered_map<string, int>dict = { {"apple",70},{"pine",0} };

	cout << dict.at("applse") << endl;//如果没有，会抛出异常，而不是添加新键

	
}

//try_emplace添加新键
void test5() {
	unordered_map<string, int>dict = { {"apple",70},{"pine",0} };
	dict.try_emplace("pear", 2);//没有，会创建
	cout << dict.at("pear") << endl;

	dict.try_emplace("apple", 20);//有了，不动
	cout << dict.at("apple") << endl;
}

//insert_or_assign等价的[]
void test6() {
	unordered_map<string, int>dict = { {"apple",70},{"pine",0} };
	dict.insert_or_assign("pear", 99);
	cout << dict.at("pear") << endl;

	dict.insert_or_assign("apple", 999);
	cout << dict.at("apple") << endl;
}


int main() {
	//test1();
	//test3();
	//test4();
	//test5();
	test6();
}