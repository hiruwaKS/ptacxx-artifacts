// <original>

int main() {
  int a = 1, b = 2;
  int* arr[2] = {&b, &a};
  int* p = arr[0];
  for (int i = 0; i < 2; i++) {
    int* t = arr[i];
    arr[i] = p;
    p = t;
  }
  return 0;
}
