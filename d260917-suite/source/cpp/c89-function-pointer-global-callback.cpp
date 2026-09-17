// <original>

void cb() {
}
void (*g)(void);
void reg() {
  g = cb;
}
int main() {
  reg();
  g();
  return 0;
}
