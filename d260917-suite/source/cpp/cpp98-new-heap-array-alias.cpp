// <original>

using namespace std;
struct V {
  int** data;
};
int main() {
  int a = 1;
  V v;
  v.data = new int*[4];
  int idx = 1;
  int** arr1 = v.data;
  arr1[idx] = &a;
  int** arr2 = v.data;
  int* p = arr2[idx];
  return 0;
}
