// <original>

using namespace std;
struct Wrapper {
  int* data;
};
Wrapper makeWrapper(int* x) {
  return {x};
}
int main() {
  int a = 1;
  Wrapper w = makeWrapper(&a);
  int* p = w.data;
  return 0;
}
