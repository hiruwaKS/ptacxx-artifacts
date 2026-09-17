// <original>

using namespace std;
class Entity {
public:
  int id;
  int* data;
};
Entity make(int id, int* x) {
  Entity e;
  e.id = id;
  e.data = x;
  return e;
}
int main() {
  int a = 1;
  Entity e = make(7, &a);
  int* p = e.data;
  return 0;
}
