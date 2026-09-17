// <original>

int main() {
  int a;
  int* p = &a;
  int** q = &p;
  int*** r = &q;
  int** s = *r;
  int* t = *s;
  return 0;
}
