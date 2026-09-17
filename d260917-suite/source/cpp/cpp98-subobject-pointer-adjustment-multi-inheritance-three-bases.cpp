// <svf-test-suite>@64f017e/src/failed_tests/multi-inheritance-3.cpp

int global_obj_f;
int *global_ptr_f = &global_obj_f;

int global_obj_g;
int *global_ptr_g = &global_obj_g;

int global_obj_h;
int *global_ptr_h = &global_obj_h;

int global_obj_l;
int *global_ptr_l = &global_obj_l;

class A {
  public:
    virtual void f(int *i) {

    }
};

class B {
  public:
    virtual void g(int *i) {

    }
};

class C {
  public:
    virtual void h(int *i) {

    }
};

class D: public A, public B, public C {
  public:
    virtual void l(int *i) {

    }
};

int main(int argc, char **argv)
{
  int *ptr_f = &global_obj_f;
  int *ptr_g = &global_obj_g;
  int *ptr_h = &global_obj_h;
  int *ptr_l = &global_obj_l;

  D d;

  A *pa = &d;
  pa->f(ptr_f);

  B *pb = &d;
  pb->g(ptr_g);

  C *pc = &d;
  pc->h(ptr_h);

  D *pd = &d;
  pd->l(ptr_l);

  return 0;
}
