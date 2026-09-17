// <original>

int main() {
  int a;
  int* p = &a;
  int** q = &p;
  int*** r[4];
  for (int i = 0; i < 4; i++)
    r[i] = &q;
  int** s = *r[3];
  int* t = *s;
  return 0;
}
