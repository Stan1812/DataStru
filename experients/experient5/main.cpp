#include <fstream>
#include <iostream>
#include <cstring>
// #include <stren>
using namespace std;
const int maxsize = 10000;
string content[maxsize]; // 字符串数组，存储文件内容
int lineIndex = 0;
typedef char sstring[maxsize];
// using namespace std;

void createTextFile()
{
// C++ 通过以下几个类支持文件的输入输出：
// ofstream: 写操作（输出）的文件类 (由ostream引申而来)
// ifstream: 读操作（输入）的文件类(由istream引申而来)
// fstream: 可同时读写操作的文件类 (由iostream引申而来)
    sstring data;
    int i = 0;
    char temp;
    ofstream file;
    file.open("exp.txt");
    cout << "Write file, input '#' to stop: " << endl;
    while (true)
    {
        temp = getchar();
        if (temp != '#')
        {
            data[i++] = temp;
        }
        else
        {
            break;
        }
    }
    getchar();
    file << data << endl;
    file.close();
}

int choose()
{
    int c;
    cout << "\t文本编辑系统菜单🈳️" << endl
         << endl;
    cout << "\t1. 创建文本文件" << endl;
    cout << "\t2. 文件单词计数" << endl;
    cout << "\t3. 文件单词定位" << endl;
    cout << "\t0. exit" << endl;
    cout << "请输入你的选择: ";
    cin >> c;
    cin.ignore();
    return c;
}

void getFileContent()
{
    sstring data;
    int index = 0;
    ifstream infile("exp.txt");
    while (infile.getline(data, maxsize))
    {
        content[index++] = data;
    }
    lineIndex = index;
}
int getLength(sstring s)
{
    return strlen(s);
}

int getIndex(string s, sstring t, int pos)
{
    // 返回子串t在主串s中第pos个字符之后的位置。
    // 1 <= pos <= sLen
    // 匹配失败返回-1
    int i = pos - 1, j = 0, sLen = s.length(), tLen = getLength(t);
    while (i < sLen && j < tLen)
    {
        if (s[i] == t[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == tLen)
    {
        return i - tLen + 1;
    }
    return 0;
}

void wordCount()
{
    sstring queryStr;
    int i = 0;
    int count = 0; // 计数
    cout << "输入你要计数的字符串: ";
    cin >> queryStr;
    while (i < lineIndex)
    {
        int index = 1;
        while (true)
        {
            index = getIndex(content[i], queryStr, index) + 1;
            if (index - 1 == 0)
            {
                break;
            }
            count++;
        }
        i++;
    }
    cout << count << endl;
}

void strFind()
{
    sstring s;
    int row, col, index = 1;
    cout << "请输入需要定位的字符串: ";
    cin >> s;
    for (int i = 0; i < lineIndex; i++)
    {
        int count = 0;
        while (true)
        {
            index = getIndex(content[i], s, index) + 1;
            if (index - 1 != 0)
            {
                count++;
                printf("字符串 %s 在第 %d 行，第 %d 列.\n", s, i + 1, index - 1);
                continue;
            }
            break;
        }
        printf("在第%d行共出现了%d次\n", i + 1, count);
    }
}

int main()
{
    getFileContent();
    bool t = true;
    while (t)
    {
        switch (choose())
        {
        case 1:
        {
            createTextFile();
            getFileContent();
            cout << endl;
            break;
        }
        case 2:
        {
            wordCount();
            cout << endl;
            break;
        }
        case 3:
        {
            strFind();
            cout << endl;
            break;
        }
        case 0:
        {
            t = false;
            cout << "exit success" << endl;
            break;
        }
        default:
        {
            cout << "输入有误，请重新输入" << endl;
        }
        }
    }
    return 0;
}
