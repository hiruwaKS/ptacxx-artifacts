// <original>

int global_obj;
int* global_ptr = &global_obj;

class A {
public:
  virtual void f(int* i) {
  }
};

class B : public A {
  virtual void f(int* i) {
  }
};

int main() {
  int* ptr = &global_obj;
  A* pb = new B;
  pb->f(ptr);
  return 0;
}
