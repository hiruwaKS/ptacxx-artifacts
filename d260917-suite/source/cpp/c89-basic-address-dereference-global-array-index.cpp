// <original>

int* garr[4];
int main() {
  int a;
  int i = 2;
  garr[i] = &a;
  int* p = garr[i];
  return 0;
}
