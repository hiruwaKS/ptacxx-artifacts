// <original>

static void a() {
}
static void b() {
}
static void (*tbl[2])() = {a, b};

int main() {
  int i = 1;
  tbl[i]();
  return 0;
}
