#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include <string>
using namespace std;

//逐字符检查
void test1() {
    ifstream file("XYZ-01_动态元素-惬意.csv");
    int data[15 * 15];

    string buffer = "";
    int readNum = 0;
    while (getline(file, buffer)) {
        buffer += ",";
        string num = "";
        for (int cur = 0; cur < buffer.size(); cur++) {
            char a = buffer[cur];
            if (a == ',') {
                int getNum = stoi(num, 0, 10);
                data[readNum] = getNum;
                readNum++;
                num = "";
            }
            else {
                num += a;
            }
        }
    }

    cout << "读取了" << readNum << endl;
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 15; x++)
            cout << data[y * 15 + x] << ",";
        cout << endl;
    }
}
//字符串流
void test2() {
    ifstream file("XYZ-01_背景.CSV");//后缀可忽略大小写
    if (file.is_open()) {
        string line, cell;
        while (getline(file,line)){
            //cout << line << endl;//getline以换行符为分割，不会把换行符读入
            stringstream lineStream(line);
            int readTime = 0;
            while (getline(lineStream, cell, ',')) {//加不加分隔符结尾都行
                readTime++;
            }
            cout << readTime << endl;
        }
    }
    else {
        cout << "打开文件失败" << endl;
    }

}

int main() {
    test2();
    return 0;
}