// <original>

using namespace std;
struct Buf {
  int* data;
};
int main() {
  int a = 1;
  Buf x, y;
  x.data = &a;
  y.data = &a;
  Buf* cur = &x;
  Buf* other = &y;

  Buf* tmp = cur;
  cur = other;
  other = tmp;
  int* p = cur->data;
  return 0;
}
