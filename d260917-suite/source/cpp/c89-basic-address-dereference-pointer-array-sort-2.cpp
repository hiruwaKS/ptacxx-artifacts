// <original>

int main() {
  int a = 1, b = 2, c = 3;
  int* arr[3] = {&c, &b, &a};
  int* p = arr[0];
  for (int i = 0; i < 3; i++) {
    int* t = arr[i];
    arr[i] = p;
    p = t;
  }
  return 0;
}
