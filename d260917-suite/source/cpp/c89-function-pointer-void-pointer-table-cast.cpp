// <original>

void a() {
}
int main() {
  void* tbl[2];
  tbl[1] = (void*)a;
  int i = 1;
  void (*f)() = (void (*)(void))tbl[i];
  f();
  return 0;
}
