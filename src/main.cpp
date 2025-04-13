// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}
std::string infx2pstfx(const std::string& inf) {
  std::string output;
  TStack<char, 100> stack;
  std::istringstream in(inf);
  char ch;
  while (in >> std::noskipws >> ch) {
    if (isdigit(ch)) {
      std::string number(1, ch);
      while (in.peek() != EOF && isdigit(in.peek())) {
        char next;
        in >> next;
        number += next;
      }
      output += number + ' ';
    } else if (ch == '(') {
      stack.push(ch);
    } else if (ch == ')') {
      while (!stack.isEmpty() && stack.top() != '(') {
        output += stack.top();
        output += ' ';
        stack.pop();
      }
      if (!stack.isEmpty()) stack.pop();
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
      while (!stack.isEmpty() && precedence(stack.top()) >= precedence(ch)) {
        output += stack.top();
        output += ' ';
        stack.pop();
      }
      stack.push(ch);
    }
  }
  while (!stack.isEmpty()) {
    output += stack.top();
    output += ' ';
    stack.pop();
  }

  return output;
}
int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::istringstream in(post);
  std::string token;
  while (in >> token) {
    if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
      stack.push(std::stoi(token));
    } else {
      int b = stack.top(); stack.pop();
      int a = stack.top(); stack.pop();
      int result = 0;

      switch (token[0]) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': result = a / b; break;
      }

      stack.push(result);
    }
  }
  return stack.top();
}
int main() {
  std::string expr;
  std::cout << "Введите инфиксное выражение: ";
  std::getline(std::cin, expr);

  std::string post = infx2pstfx(expr);
  std::cout << "Постфиксная форма: " << post << "\n";

  int result = eval(post);
  std::cout << "Результат вычисления: " << result << "\n";

  return 0;
}
