// <original>

using namespace std;
int main() {
  int a = 1;
  int* buf[4];
  int head = 0, tail = 0;
  buf[head] = &a;
  head = (head + 1) & 3;
  int idx = (head - 1) & 3;
  int* p = buf[idx];
  return 0;
}
