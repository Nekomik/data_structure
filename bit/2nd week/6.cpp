#include <iostream>  
#include <stack>  
#include <map>  
#include <cstring>  
#include <string>  
#include <cmath>  
#include <cctype>  
using namespace std;  
  
map<char, int> precedence = {  
    {'+', 1},  
    {'-', 1},  
    {'*', 2},  
    {'/', 2},  
    {'%', 2},  
    {'^', 3}  
};  
  
bool is_valid_expression(string expression);  
string* infix_to_postfix(string expression, int &length);  
int calculate_expression(string* postfix_expression);  
  
int main() {  
    int n;  
    cin >> n;  
    for (int i = 0; i < n; i++) {  
        string expression;  
        int length;  
        cin >> expression;  
        if (is_valid_expression(expression)) {  
            string* postfix_expression = infix_to_postfix(expression, length);  
  
            // for (int j = 0; j < length; j++) {  
            //     cout << postfix_expression[j] << "|";   
            // }  
            // cout << "length: " << length << endl;  
  
            calculate_expression(postfix_expression);  
            delete[] postfix_expression; // 释放内存  
        }  
        else {  
            cout << "error." << endl;  
        }  
    }  
    return 0;  
}  
  
bool is_valid_expression(string expression) {  
    int balance = 0;  // 括号平衡计数   
    int left_lock = 0;    
    int right_lock = 0;    
    int num_lock = 0;   
    for (int i = 0; i < expression.length(); i++) {   
        char ch = expression[i];   
        if (!isdigit(ch) && precedence.find(ch) == precedence.end() && ch != '(' && ch != ')') {   
            return false;  // 非法字符   
        }   
        if (ch == '(') {   
            if (num_lock == 1) return false;  // 左括号后必须为数字或者左括号   
            balance++;   
            left_lock = 1;   
            num_lock = 0;    
            right_lock = 0;    
        } else if (ch == ')') {   
            balance--;   
            right_lock = 1;   
            num_lock = 0;    
            left_lock = 0;    
            if(i!=0 && expression[i-1] == '-') return false;  // 右括号前必须为操作符或者右括号 )  
            if (balance < 0) return false;  // 右括号多于左括号   
        }   
        else if (isdigit(ch)) {  
            if (right_lock == 1) return false;  // 右括号后必须为操作符或者右括号   
            num_lock = 1;    
            right_lock = 0;    
            left_lock = 0;     
        }   
        else if (ch == '-'){  
            left_lock = 0;    
            right_lock = 0;    
            num_lock = 0;    
        }  
        else {  
            if (left_lock == 1) return false;  // 左括号后必须为数字或者左括号   
            left_lock = 0;    
            right_lock = 0;    
            num_lock = 0;    
        }  
    }   
    return balance == 0;  // 必须平衡   
}  
  
  
string * infix_to_postfix(string expression, int &length) {     
    stack<char> operators;     
    string *postfix_expression;     
    postfix_expression = new string[10000];     
    postfix_expression[0] = "";     
    int index = 0;     
    // 用于合成10以上的数字   
    int lock = 0;    
    int sign = 1;     
    for (int i = 0; i < expression.length(); i++) {     
        char ch = expression[i];     
        if (isdigit(ch)) {     
            // 如果遇到数字，是一个字符不为数字，则拼接为一个大数字  
            if(sign == -1){
                if(i!=1) index++;
                postfix_expression[index] += '-';
                sign = 1;
            }   
            if (lock == 1) {     
                index++;     
                postfix_expression[index] = ch;     
                lock = 0;     
            }     
            else{     
                postfix_expression[index] += ch;  
            }     
        }     
        else if (ch == '(') {     
            operators.push(ch);       
        }     
        else if(ch == ')'){     
            lock = 1;     
            while (!operators.empty() && operators.top() != '(') {     
                postfix_expression[++index] += operators.top();     
                operators.pop();     
            }     
            if (operators.empty()) cout << "ERROR: unmatched parentheses";  // 左右括号不匹配     
            operators.pop();  // 弹出左括号     
                 
        }     
        // 为操作符   
        else if(ch == '^'){     
            lock = 1;     
            while (!operators.empty() && precedence[ch] < precedence[operators.top()]) {     
                postfix_expression[++index] += operators.top();     
                operators.pop();     
            }    
            operators.push(ch);     
        }    
        else if(ch == '-'){
            if(i == 0 || !isdigit(expression[i-1])){
                lock = 0;
                sign = -1;
            }
            else{
                lock = 1;     
                while (!operators.empty() && precedence[ch] <= precedence[operators.top()]) {     
                    postfix_expression[++index] += operators.top();     
                    operators.pop();     
                }     
                operators.push(ch);     
            }
        }
        else{       
            lock = 1;     
            while (!operators.empty() && precedence[ch] <= precedence[operators.top()]) {     
                postfix_expression[++index] += operators.top();     
                operators.pop();     
            }     
            operators.push(ch);       
        }   
         
    }     
    while (!operators.empty()) {     
        if (operators.top() == '(' || operators.top() == ')') cout << "ERROR: unmatched parentheses";  // 左右括号不匹配     
        postfix_expression[++index] += operators.top();     
        operators.pop();     
    }     
    length = index+1;     
    return postfix_expression;     
}     
   

int is_number(string str){  
    if(!isdigit(str[0]) && str[0] != '-') return false;   
    for(int i=1;i<str.length();i++){  
        if(!isdigit(str[i])) return false;   
    }  
    if(str.length() == 1 && str[0] == '-') return false;   
    return true;   
}
   
   
int calculate_expression(string* postfix_expression){    
    stack<int> num;    
    int i = 0;   
    while (!postfix_expression[i].empty()) {    
        if(is_number(postfix_expression[i])){    
            num.push(stoi(postfix_expression[i]));    
        }    
        else{    
            if (num.size() < 2) return -1; // 运算符个数不足    
            int num2 = num.top();    
            num.pop();    
            int num1 = num.top();    
            num.pop();    
            switch(postfix_expression[i][0]){    
                case '+':    
                    num.push(num1+num2);    
                    break;    
                case '-':    
                    // cout << "num1-num2=" << num1-num2 << endl;   
                    num.push(num1-num2);    
                    break;    
                case '*':    
                    num.push(num1*num2);    
                    break;    
                case '/':    
                    if(num2 == 0) {    
                        cout << "Divide 0."<< endl;    
                        return -2;    
                    }   
                    num.push(num1/num2);    
                    break;    
                case '^':     
                    if(num2 < 0) {cout << "error."<< endl;return -1;}   
                    num.push(pow(num1,num2));    
                    break;    
                case '%':    
                    if(num2 == 0) {cout << "error."<< endl;return -1;}    
                    // cout << "num1%num2=" << num1%num2 << endl;   
                    num.push(num1%num2);    
                    break;    
                default:    
                    cout << "ERROR: invalid operator";    
                    return -1;    
        }    
    }    
    i++;   
    }    
    if(num.size() == 1)   
        {     
            cout << num.top() << endl;   
            return num.top();   
        }    
    else{cout << "error."<< endl;return -1;}   
}  