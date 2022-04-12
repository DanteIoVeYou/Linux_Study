#include <iostream>


class Task {
public:
  Task(char oper, int left, int right): x(left), y(right), op(oper){}
  ~Task(){}
  void run()
  {
    int ret = -1;
    switch(op) {
      case '+':
        ret = x + y; 
        std::cout << x << op << y << "="<< ret << std::endl;
        break;
      case '-':
        ret = x - y;
        std::cout << x << op << y << "="<< ret << std::endl;
        break;
      case '*':
        ret = x * y;
        std::cout << x << op << y << "="<< ret << std::endl;
        break;
      case '/':
        if(y == 0) {
          std::cout << "0 cannot be denominator" << std::endl;
        }
        else {
          ret = x / y;
          std::cout << x << op << y << "="<< ret << std::endl;
        }
        break;
      case '%':
        if(y == 0) {
          std::cout << "0 cannot be denominator" << std::endl;
        }
        else {
          ret = x % y;
          std::cout << x << op << y << "="<< ret << std::endl;
        }
        break;
      default:
        std::cout << "unknown operator" << std::endl;
        break;
    }
    std::cout << "======================================" << std::endl;
  }
private:
  int x;
  int y;
  char op;
};
