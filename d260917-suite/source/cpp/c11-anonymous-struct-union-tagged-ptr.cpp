// <original>

using namespace std;
struct TaggedVal {
  int tag;
  union {
    int i;
    int* ptr;
  };
};
int main() {
  int a = 1;
  TaggedVal v;
  v.tag = 1;
  v.ptr = &a;
  int* p = v.ptr;
  return 0;
}
