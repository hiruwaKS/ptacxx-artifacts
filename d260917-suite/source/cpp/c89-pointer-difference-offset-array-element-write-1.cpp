// <original>

using namespace std;

int main() {
  int a = 1;
  int* buf[8];
  int start = 2;
  int** view = &buf[start];
  *view = &a;
  int* p = buf[2];
  return 0;
}
