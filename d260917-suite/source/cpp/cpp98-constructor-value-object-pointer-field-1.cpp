// <original>

using namespace std;

class Entity {
public:
  int id;
  int* data;
};

Entity makeEntity(int id, int* x) {
  return Entity{id, x};
}

int main() {
  int a = 1;
  Entity e = makeEntity(7, &a);
  int* p = e.data;
  return 0;
}
