// <original>

int g;
int* gp = &g;
class Base {
public:
  virtual void f(int* i) {
  }
};
class D1 : public Base {
public:
  virtual void f(int* i) {
  }
};
class D2 : public Base {
public:
  virtual void f(int* i) {
  }
};
int main() {
  int* p = &g;
  Base* b = new D1;
  b->f(p);
  return 0;
}
