// <original>

using namespace std;
struct Builder {
  int* a;
  int* b;
};
Builder* builder_set(Builder* b, int* x) {
  b->a = x;
  return b;
}
int main() {
  int a = 1;
  Builder b;
  b.b = nullptr;
  Builder* r = builder_set(builder_set(&b, &a), &a);
  int* p = r->a;
  return 0;
}
