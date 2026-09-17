// <original>

struct Cmd {
  int code;
  void (*h)();
};
void a() {
}
static const Cmd tbl[] = {{0, a}, {1, a}};
int main() {
  int i = 1;
  tbl[i].h();
  return 0;
}
