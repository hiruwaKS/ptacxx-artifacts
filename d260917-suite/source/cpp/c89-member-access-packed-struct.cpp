// <original>

struct __attribute__((packed)) S {
  char c;
  int* p;
};
int main() {
  int a;
  S s;
  s.p = &a;
  int* q = s.p;
  return 0;
}
