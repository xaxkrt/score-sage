#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <vector>
using std::vector;

#include <string>
using std::stoi;
using std::string;

#include "./student.h"

int to_int(char c);
void student_sort(vector<Student>& students);

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

    // 读入分数
    vector<int> scores(55, 0);
    for (int i = 1; i <= 55; i++) {
        cout << "\n键入分数:\n" << i << "号(" << names[i - 1] << "):";
        getline(cin, line);

        // 回退
        if (line == "<") {
            if (i - 1 >= 1) {
                cout << "已回退" << endl;
                i -= 2;
                continue;
            } else {
                cout << "没有更靠前的成员!" << endl;
                i--;
                continue;
            }
        } else if (line == ">") { // 前进
            if (i + 1 <= 55) {
                cout << "已前进" << endl;
                continue;
            } else {
                cout << "没有更靠后的成员!" << endl;
                i--;
                continue;
            }
        } else {                   // 加分
            bool flag = false;     // 上一个字符是否为数字?
            bool negative = false; // 是否为负数?
            int num = 0;           // 每一个数字
            int score = 0;         // 此行的最后分数

            line += "\n";
            for (auto c : line) {
                if (c == '-') { // 判断是否为负数
                    negative = true;
                } else if (to_int(c) != 10 && flag) { // 读取到数字的中间
                    num = num * 10 + to_int(c);
                } else if (to_int(c) != 10 && !flag) { // 读取到数字的开头
                    num = to_int(c);
                    flag = true;
                } else if (to_int(c) == 10 && flag) { // 读取到数字的结尾
                    flag = false;
                    if (negative) {
                        num *= -1;
                    }
                    negative = false;
                    // 添加到分数
                    score += num;
                }
            }

            // 读完一行, 添加分数至数组
            scores[i - 1] = score;
        }
    }

    // 初始化学生列表
    vector<Student> students;
    for (int i = 0; i < 55; i++) {
        students.push_back(Student(i + 1, scores[i]));
    }

    // 初始化小组列表
    vector<Student> gro;
    for (int i = 0; i < 11; i++) {
        gro.push_back(students[groups[i][0] - 1]);
        for (int j = 1; j < 5; j++) {
            gro[i]._score += students[groups[i][j] - 1]._score;
        }
    }

    // 排序
    // 个人
    student_sort(students);
    // 小组
    student_sort(gro);

    // 输出
    cout << "个人排名: " << endl;
    for (auto i : students) {
        cout << "{" << names[i._number - 1] << ", " << i._score << "}" << endl;
    }

    cout << "小组排名" << endl;
    for (auto i : gro) {
        cout << "{" << names[i._number - 1] << ", " << i._score << "}" << endl;
    }

    return 0;
}

int to_int(char c) {
    // 判断是否为数字
    if (c < '0' || c > '9') {
        return 10;
    } else {
        return c - 48;
    }
}

void student_sort(vector<Student>& students) {
    bool flag = true;
    while (flag) {
        flag = false;
        for (int i = 0; i < students.size() - 1; i++) {
            if (students[i]._score < students[i + 1]._score) {
                flag = true;
                Student temp = students[i];
                students[i] = students[i + 1];
                students[i + 1] = temp;
            }
        }
    }
}
