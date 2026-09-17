// <original>

void (*g)(void);
void x();
void y() {
  g = x;
}
void x() {
  g = y;
}
int main() {
  g = y;
  g();
  return 0;
}
