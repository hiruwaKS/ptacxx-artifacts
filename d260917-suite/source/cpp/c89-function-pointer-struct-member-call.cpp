// <original>

struct FnRef {
  void (*f)();
  void call() {
    f();
  }
};
void a() {
}
int main() {
  FnRef fr;
  fr.f = a;
  fr.call();
  return 0;
}
