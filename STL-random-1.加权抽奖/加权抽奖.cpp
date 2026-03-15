#include<random>
#include<iostream>
using namespace std;

int main() {
	//创建奖池数据
	vector<string> name{ "苹果","葡萄" };
	vector<double> weight{ 4,1 };
	//创建抽奖器，基于奖池数据
	random_device rd;
	mt19937 randInt(rd());
	discrete_distribution<int> lottery(weight.begin(),weight.end());
	//查看概率功能
	auto 查看概率 = [&] {
		vector<double> probabilities = lottery.param().probabilities();
		for (int order = 0; order < probabilities.size(); ++order)
			cout << name[order] << "(" << weight[order] << ")\t" << probabilities[order] * 100 << "%" << endl;
	};
	//抽奖功能
	auto 十连抽 = [&] {
		for (int time = 0; time < 10; ++time) {
			int result = lottery(randInt);
			cout << name[result] << "  ";
		}
		cout << endl << endl;
	};
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//查看概率，抽奖
	查看概率();
	十连抽();
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//修改奖池数据：添加新的品类。示例：添加新的种类“榴莲”
	name.push_back("榴莲");
	weight.push_back(1);
	//包装成参数，传递给抽奖器
	discrete_distribution<int>::param_type paramNew(weight.begin(), weight.end());
	lottery.param(paramNew);
	//查看概率，抽奖
	查看概率();
	十连抽();
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//修改奖池数据：查找并修改某品类的权重。示例：将“苹果”的权重改为1
	for (int order = 0; order < name.size(); ++order)
		if (name[order] == "苹果")weight[order] = 1;
	//包装成参数，传递给抽奖器
	lottery.param({ weight.begin(), weight.end() });
	//查看概率，抽奖
	查看概率();
	十连抽();
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//修改奖池数据：查找并删除某品类。示例：将“葡萄”删除
	auto it=find(name.begin(), name.end(), "葡萄");//查找，定位迭代器
	if (it != name.end()) {
		int index = distance(name.begin(), it);//根据迭代器计算索引
		name.erase(name.begin() + index);
		weight.erase(weight.begin() + index);
	}
	//包装成参数，传递给抽奖器
	lottery.param({ weight.begin(), weight.end() });
	//查看概率，抽奖
	查看概率();
	十连抽();
}