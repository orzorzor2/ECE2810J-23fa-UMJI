#include "dlist.h"
#include <iostream>
#include <string>

using namespace std;


// + - * / r  at least two
void binary(Dlist<int> &stack, char operand) {
    int *a = nullptr, *b = nullptr;
    try {
        a = stack.removeFront();
        b = stack.removeFront();

        //通过引用捕获异常比较推荐
    } catch (emptyList &) {
        if (a) {
            stack.insertFront(a); // 如果a已被移除，则将其放回栈中
        }
        throw; // 重新抛出异常
    }
    switch (operand) {
        case '+':
            *b = *b + *a;
            stack.insertFront(b);
            break;
        case '-':
            *b = *b - *a;
            stack.insertFront(b);
            break;
        case '*':
            *b = *a * *b;
            stack.insertFront(b);
            break;
        case '/':
            if (*a == 0) {
                cout << "Divide by zero\n";
                stack.insertFront(b);
                stack.insertFront(a);
                return;
            } else {
                *b = *b / *a;
                stack.insertFront(b);
            }
            break;
        case 'r':
            stack.insertFront(a);
            stack.insertFront(b);
            break;
        default:
            break;
    }
}


// n d p at least one
void unary(Dlist<int> &stack, char operand) {
    int *a = nullptr;
    try {
        a = stack.removeFront();
    }
    catch (emptyList &) {
        throw;
    }
    switch (operand) {
        case 'n':
            *a = -*a;
            break;
        case 'd': {
            int *duplicate = new int(*a);
            stack.insertFront(duplicate);
            break;
        }
        case 'p':
            cout << *a << endl;
            break;
        default:
            break;
    }
    stack.insertFront(a);
}

void clear(Dlist<int> &stack) {
    try {
        while (true) {
            stack.removeFront();
        }
    }
    catch (emptyList &) {}
}

void print(Dlist<int> &stack) {
    Dlist<int> copy(stack);
    while (!copy.isEmpty()) {
        int *a = copy.removeFront();
        cout << *a << " ";
        delete a;}
    cout << "\n";
}




bool isInteger(const string &str) {
    if (str.empty()) return false;
    int start = 0;
    if (str[0] == '-') start = 1; // 跳过可能的负号

    if (start == 1 && str.length() == 1) return false; // 字符串仅包含负号

    // 确保字符串剩余部分都是数字
    for (string::size_type i = start; i < str.length(); i++) {
        if (!(('0' <= str[i]) && (str[i] <= '9'))) return false;
    }

    return true; // 所有字符都是数字
}

bool isoperator(const string &str) {
    if (str == "+" || str == "-" || str == "*" || str == "/" || str == "n" || str == "d" || str == "r" || str == "p" ||
        str == "c" || str == "a" || str == "q") {
        return true;
    } else {
        return false;
    }
}

//在operate中进一步完善not enough operand异常，因为它和emptylist相关
void operate(Dlist<int> &stack, string command) {
    try {
        //switch不能接收string
        switch (command[0]) {
//            case 'q': 单独处理了

            case '+':
            case '-':
            case '*':
            case '/':
            case 'r':
                binary(stack, command[0]);
                break;
            case 'n':
            case 'd':
            case 'p':
                unary(stack, command[0]);
                break;
            case 'c':
                clear(stack);
                break;
            case 'a':
                print(stack);
                break;
            default:
                break;
        }
    }
    catch (emptyList &) {
        cout << "Not enough operands\n";
    }
}

int main() {
    string command;
    auto *stack = new Dlist<int>;

    while (cin >> command) { // 读取字符串，直到遇到空白字符
        //如果是整数,压入栈
        if (!isInteger(command) && !isoperator(command)) {
            cout << "Bad input\n";
        }

        if (isInteger(command)) {
            int num = stoi(command);
            int *newInt = new int(num);
            stack->insertFront(newInt);
        } //如果是操作字符 这里情况较多，故另写函数

            //剩下两个报错在这里
        else if (isoperator(command)) {
            if (command == "q") {
                //或者用 delete stack; return 0;结束程序
                break;
            } else {
                operate(*stack, command);
            }
        }
    }
    delete stack;
    return 0;
}

//int main(){
//    return 0;
//}