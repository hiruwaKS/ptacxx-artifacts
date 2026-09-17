// <original>

int main() {
  int a = 1;
  int* buf[8];
  int start = 2;
  buf[2] = &a;
  int** view = &buf[start];
  int* p = *view;
  return 0;
}
