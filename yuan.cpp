#include<iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MAX_EXPRESSIONS 100

char operatortable[4];
int operatorcount = 0;

int generateOperand(string* expression, int max, int decimalPlaces);
int generateOperator(string* expression);
int generateExpression(string* expression, int numOperators, int parentheses, int maxOperand, int decimalPlaces);
int main() {
    srand(time(0));
    int maxOperand = 10, decimalPlaces = 0;
    int parentheses = 0;
    int expressionCount = 5, i, length = 3, viewOption = 0;
    string filename;

    cout << "请选择习题类型：" << endl;
    cout << "1. 十以内" << endl;
    cout << "2. 百以内" << endl;
    cout << "3. 千以内" << endl;
    cin >> maxOperand;

    switch (maxOperand)
    {
    case 1:
        maxOperand = 10;
        break;
    case 2:
        maxOperand = 100;
        break;
    case 3:
        maxOperand = 1000;
        break;
    default:
        break;
    }

    cout << "请输入习题数：" << endl;
    cin >> expressionCount;
    cout << "请输入算式长度（运算符个数）：" << endl;
    cin >> length;
    cout << "请输入使用的运算符" << endl;
    cout << "1.+" << endl;
    cout << "2.-" << endl;
    cout << "3.*" << endl;
    cout << "4./" << endl;
    cout << "5.全部" << endl;
    cout << "0.完成" << endl;
    i = 0;
    while (1) {
        cin >> operatorcount;
        if (operatorcount == 0) { break; }
        if (operatorcount==5) {
            operatortable[0] = '+';
            operatortable[1] = '-';
            operatortable[2] = '*';
            operatortable[3] = '/';
            i = 4;
            break;
        }
        switch (operatorcount)
        {
        case 1:
            operatortable[i] = '+';
            i++;
            break;
        case 2:
            operatortable[i] = '-';
            i++;
            break;
        case 3:
            operatortable[i] = '*';
            i++;
            break;
        case 4:
            operatortable[i] = '/';
            i++;
            break;
        default:
            break;
        }
        cout << "请继续输入或输0退出" << endl;
    }
    operatorcount = i;
    cout << "使用小数的位数：" << endl;
    cin >> decimalPlaces;
    cout << "是否使用括号:" << endl << "1.是" << endl << "2.否" << endl;
    cin >> parentheses;

    string** expressions = new string * [MAX_EXPRESSIONS];

    for (i = 0; i < expressionCount; i++) {
        expressions[i] = new string[MAX_EXPRESSIONS];
        generateExpression(expressions[i], length, parentheses-1, maxOperand, decimalPlaces);
    }
    cout << "生成完成" << endl;
    cout << "请选择查看类型：" << endl;
    cout << "1. 直接显示" << endl;
    cout << "2. 保存到文件" << endl;
    cout << "3. 打印" << endl;
    cin >> viewOption;
    if (viewOption == 1) {
        for (int i = 0; i < expressionCount; i++) {
            cout << *expressions[i] << endl;
        }
    }
    if (viewOption == 2) {
        cout << "请输入文件名（仅支持TXT）：" << endl;
        cin >> filename;
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "无法打开文件" << endl;
            return 1;
        }
        for (int i = 0; i < expressionCount; i++) {
            outFile << *expressions[i] << endl;
        }
        outFile.close();

        cout << "写入成功!" << endl;
    }
    if (viewOption == 3) {
        cout << "该功能暂未实现" << endl;
    }
    return 0;
}


int generateOperand(string* expression, int max, int decimalPlaces) {
    int digitCount = 0, i;
    for (i = 1; max > 10; i++) {
        max = max / 10;
    }
    for (int j = 0; j < i; j++) {
        int digit = rand() % 10;
        expression->push_back(digit + '0');
    }
    if (decimalPlaces > 0) {
        expression->push_back('.');
        for (int j = 0; j < decimalPlaces; j++) {
            int digit = rand() % 10;
            expression->push_back(digit + '0');
        }
    }
    return 1;
}

int generateOperator(string* expression) {
    int operation = rand() % operatorcount;
    expression->push_back(operatortable[operation]);
    return 1;
}

int generateExpression(string* expression, int numOperators, int parentheses, int maxOperand, int decimalPlaces) {
    if (numOperators <= 0) {
        generateOperand(expression, maxOperand, decimalPlaces);
        return 1;
    }

    if (parentheses != 0 && parentheses != -1) {
        expression->push_back('(');
    }
    generateOperand(expression, maxOperand, decimalPlaces);
    generateOperator(expression);
    numOperators--;
    if (parentheses == -1) {
        generateExpression(expression, numOperators, -1, maxOperand, decimalPlaces);
    }
    else if ((rand() % 4) != 0) {
        generateExpression(expression, numOperators, 0, maxOperand, decimalPlaces);
    }
    else {
        generateExpression(expression, numOperators, 1, maxOperand, decimalPlaces);
    }
    if (parentheses != 0 && parentheses != -1) {
        expression->push_back(')');
    }
}
