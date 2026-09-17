// <original>

void a() {
}
void b() {
}
static void (*tbl[2][2])() = {{a, a}, {b, b}};
int main() {
  int i = 1, j = 0;
  tbl[i][j]();
  return 0;
}
