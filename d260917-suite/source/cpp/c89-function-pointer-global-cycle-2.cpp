// <original>

void (*g)(void);
void x();
void w();
void y() {
  g = w;
}
void w() {
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
