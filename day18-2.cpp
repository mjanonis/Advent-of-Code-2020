#include <cctype>
#include <fstream>
#include <queue>
#include <stack>
#include <vector>

std::queue<char> parse(const std::string& expression)
{
  std::queue<char> result;
  std::stack<char> op;

  for (const auto& c : expression) {
    // Skip spaces
    if (c == ' ') {
      continue;
    }

    if (isdigit(c)) {
      result.push(c);
    }
    else if (c == '+' || c == '*') {
      while (!op.empty() && op.top() != '(' &&
             (op.top() == '+' || op.top() == '*') && op.top() > c) {
        result.push(op.top());
        op.pop();
      }
      op.push(c);
    }
    else if (c == '(') {
      op.push(c);
    }
    else if (c == ')') {
      while (!op.empty() && op.top() != '(') {
        result.push(op.top());
        op.pop();
      }
      if (op.top() == '(') {
        op.pop();
      }
    }
  }
  while (!op.empty()) {
    result.push(op.top());
    op.pop();
  }
  return result;
}

long long int evaluate(std::queue<char> expression)
{
  long long int t1, t2;
  std::vector<long long int> tmp;
  char c;
  while (!expression.empty()) {
    c = expression.front();
    expression.pop();
    if (c == '*' || c == '+') {
      t1 = tmp.back();
      tmp.pop_back();
      t2 = tmp.back();
      tmp.pop_back();

      if (c == '*') {
        tmp.push_back(t1 * t2);
      }
      else {
        tmp.push_back(t1 + t2);
      }
    }
    else {
      tmp.push_back(c - '0');
    }
  }
  return tmp[0];
}

int main()
{
  std::ifstream input{"day18.in"};
  std::ofstream output{"day18-2.out"};

  std::string expression;
  long long int sum = 0;
  while (getline(input, expression)) {
    sum += evaluate(parse(expression));
  }

  output << sum << std::endl;
}
