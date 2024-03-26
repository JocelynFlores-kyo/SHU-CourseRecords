#include <iostream>
#include <fstream>
#include <map>
#include <cctype>
#include <string>
#include <algorithm>

using namespace std;

// 函数原型
bool isIdentifierChar(char ch);
string toLower(const string &s);

int main() {
    ifstream sourceFile("source.txt");
    ofstream outputFile("output.txt");
    map<string, int> identifierCount;
    string token;
    char ch;

    if (!sourceFile.is_open()) {
        cerr << "无法打开源文件source.txt" << endl;
        return 1;
    }

    while (sourceFile.get(ch)) {
        if (isalpha(ch)) {
            // 开始构建标识符
            token = ch;
            while (sourceFile.get(ch) && isIdentifierChar(ch)) {
                token += ch;
            }
            // 将标识符转换为小写并计数
            identifierCount[toLower(token)]++;
            // 如果不是标识符字符，则跳过
            if (!isIdentifierChar(ch)) {
                continue;
            }
        }
        // 忽略注释和字符串中的内容
        else if (ch == '/' && sourceFile.peek() == '*') {
            // 跳过注释
            while (sourceFile.get(ch) && !(ch == '*' && sourceFile.peek() == '/')) {}
            if (ch == '*') {
                sourceFile.get(ch); // 跳过结束的 '/'
            }
        }
        else if (ch == '\'' || ch == '\"') {
            // 跳过字符串
            while (sourceFile.get(ch) && ch != '\'' && ch != '\"') {}
        }
    }

    // 输出标识符及其出现次数
    for (const auto &pair : identifierCount) {
        outputFile << "(" << pair.first << ", " << pair.second << ")\n";
    }

    sourceFile.close();
    outputFile.close();

    cout << "标识符统计完成，结果已输出到output.txt文件中。" << endl;

    return 0;
}

// 辅助函数定义
bool isIdentifierChar(char ch) {
    return isalnum(ch) || ch == '_';
}

string toLower(const string &s) {
    string result;
    transform(s.begin(), s.end(), back_inserter(result), ::tolower);
    return result;
}
