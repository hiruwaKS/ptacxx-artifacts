// <original>

using namespace std;
struct Builder {
  int* val;
};
Builder* builder_add(Builder* b, int* x) {
  b->val = x;
  return b;
}
int main() {
  int a = 1;
  Builder b;
  Builder* r = builder_add(&b, &a);
  int* p = r->val;
  return 0;
}
