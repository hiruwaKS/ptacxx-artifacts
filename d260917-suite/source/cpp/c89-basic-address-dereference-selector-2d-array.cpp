// <original>

using namespace std;
int main() {
  int a = 1;
  int* bufs[2][4];
  int sel = 0;
  bufs[sel][0] = &a;
  sel = 1 - sel;
  sel = 1 - sel;
  int* p = bufs[sel][0];
  return 0;
}
