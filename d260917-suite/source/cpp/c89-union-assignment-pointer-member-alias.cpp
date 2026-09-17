// <original>

using namespace std;
union U {
  int* p;
  int* q;
};
int main() {
  int a = 1;
  U u;
  u.p = &a;
  int* r = u.q;
  return 0;
}
