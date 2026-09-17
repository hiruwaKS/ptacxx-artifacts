// <original>

#include <queue>

using namespace std;

int main() {
  int a = 1;
  queue<int*> q;
  q.push(&a);
  int* p = q.front();
  return 0;
}
