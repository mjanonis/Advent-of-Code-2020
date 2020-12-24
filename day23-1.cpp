#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

int mod(const int& lhs, const int& rhs) { return (rhs + (lhs % rhs)) % rhs; }

struct List {
  List(size_t v) : val{v}, next{nullptr} {}
  size_t val;
  List* next;
};

void insert(List* l, size_t val) { l->next = new List(val); }

void make_circ(List* head)
{
  List* curr = head;
  while (curr->next) {
    curr = curr->next;
  }
  curr->next = head;
}

int main()
{
  std::ifstream input{"day23.in"};
  std::ofstream output{"day23-1.out"};

  std::string tmp;
  getline(input, tmp);
  std::istringstream iss(tmp);
  std::map<size_t, List*> index;
  size_t min = 1, max = 9;

  char c;
  iss >> c;
  List* head = new List(c - '0');
  index[head->val] = head;

  for (List* curr = head; iss >> c;) {
    insert(curr, c - '0');
    curr = curr->next;
    index[curr->val] = curr;
  }

  make_circ(head);

  size_t curr_cup = head->val;

  for (size_t i = 0; i < 100; ++i) {

    size_t c1, c2, c3;
    c1 = index[curr_cup]->next->val;
    c2 = index[curr_cup]->next->next->val;
    c3 = index[curr_cup]->next->next->next->val;
    index[curr_cup]->next = index[c3]->next;

    size_t dest = curr_cup - 1;
    while (dest == c1 || dest == c2 || dest == c3 || dest < min) {
      if (dest < min) {
        dest = max;
        continue;
      }
      --dest;
    }

    List* dest_next = index[dest]->next;
    index[dest]->next = index[c1];
    index[c3]->next = dest_next;

    curr_cup = index[curr_cup]->next->val;
  }

  List* one = index[1];
  one = one->next;
  for (size_t i = 1; i < 9; ++i) {
    output << one->val;
    one = one->next;
  }
  output << std::endl;
}
