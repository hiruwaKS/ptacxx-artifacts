// <original>

static void a() {
}
static void b() {
}
static void (*tbl[2])() = {a, b};
void call(int i) {
  tbl[i]();
}
int main() {
  int i = 1;
  call(i);
  return 0;
}
