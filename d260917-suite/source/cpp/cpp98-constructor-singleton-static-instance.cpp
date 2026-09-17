// <original>

using namespace std;
class Singleton {
public:
  static Singleton* instance() {
    static Singleton inst;
    return &inst;
  }
  int* p = nullptr;
};
int main() {
  int a = 1;
  Singleton* s = Singleton::instance();
  s->p = &a;
  Singleton* s2 = Singleton::instance();
  int* q = s2->p;
  return 0;
}
