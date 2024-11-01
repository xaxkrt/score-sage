#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::stoi;

#include <fstream>
using std::ifstream;

#include <vector>
using std::vector;

#include <string>
using std::string;

int main() {
    vector<string> names;
    vector<vector<unsigned int>> groups;

    ifstream fin;
    // 读入姓名
    string line;
    fin.open("./name_list.txt");
    if (!fin.is_open()) {
        cout << "打开文件 ./name_list.txt 失败!" << endl;
        return 1;
    }

    while (getline(fin, line)) {
        names.push_back(line);
    }
    fin.close();

    // 读入小组
    fin.open("./groups.txt");
    vector<unsigned int> temp;
    if (!fin.is_open()) {
        cout << "打开文件 ./groups.txt 失败!" << endl;
        return 1;
    }

    while (getline(fin, line)) {
        temp.push_back(stoi(line));
    }

    groups.push_back({});
    for (auto i : temp) {
        if (groups[groups.size() - 1].size() < 5) {
            groups[groups.size() - 1].push_back(i);
        } else {
            groups.push_back({});
            groups[groups.size() - 1].push_back(i);
        }
    }

    return 0;
}
