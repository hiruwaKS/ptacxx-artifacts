// <original>

int main() {
  int arr[4];
  int* p = &arr[2];
  int* q = p - 1;
  int* base = (int*)((char*)q);
  return 0;
}
