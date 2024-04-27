#include<iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MAX_EXPRESSIONS 100

int generateOperand(string* expression, int max, int decimalPlaces);
int generateOperator(string* expression);
int generateExpression(string* expression, int numOperators, int parentheses, int maxOperand, int decimalPlaces);
int main() {
    srand(time(0));
    int maxOperand = 10, decimalPlaces = 0;
    int parentheses = 0;
    int expressionCount = 5, i, length = 3, viewOption = 0;
    string filename;

    cout << "��ѡ��ϰ�����ͣ�" << endl;
    cout << "1. ʮ����" << endl;
    cout << "2. ������" << endl;
    cout << "3. ǧ����" << endl;
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

    cout << "������ϰ������" << endl;
    cin >> expressionCount;
    cout << "��������ʽ���ȣ��������������" << endl;
    cin >> length;
    cout << "ʹ��С����λ����" << endl;
    cin >> decimalPlaces;

    cout << "�Ƿ�ʹ������:" << endl << "1.��" << endl << "2.��" << endl;
    cin >> parentheses;

    string** expressions = new string * [MAX_EXPRESSIONS];

    for (i = 0; i < expressionCount; i++) {
        expressions[i] = new string[MAX_EXPRESSIONS];
        generateExpression(expressions[i], length, parentheses, maxOperand, decimalPlaces);
    }
    cout << "�������" << endl;
    cout << "��ѡ��鿴���ͣ�" << endl;
    cout << "1. ֱ����ʾ" << endl;
    cout << "2. ���浽�ļ�" << endl;
    cout << "3. ��ӡ" << endl;
    cin >> viewOption;
    if (viewOption == 1) {
        for (int i = 0; i < expressionCount; i++) {
            cout << *expressions[i] << endl;
        }
    }
    if (viewOption == 2) {
        cout << "�������ļ�������֧��TXT����" << endl;
        cin >> filename;
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "�޷����ļ�" << endl;
            return 1;
        }
        for (int i = 0; i < expressionCount; i++) {
            outFile << *expressions[i] << endl;
        }
        outFile.close();

        cout << "д��ɹ�!" << endl;
    }
    if (viewOption == 3) {
        cout << "�ù�����δʵ��" << endl;
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
    int operation = rand() % 4;
    switch (operation)
    {
    case 0:
        expression->push_back('+');
        break;
    case 1:
        expression->push_back('-');
        break;
    case 2:
        expression->push_back('*');
        break;
    case 3:
        expression->push_back('/');
        break;
    default:
        break;
    }
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
