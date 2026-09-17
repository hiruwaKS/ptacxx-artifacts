// <svf-test-suite>@64f017e/src/failed_tests/vdiamond-multi-inher.cpp

int global_obj_f;
int *global_ptr_f = &global_obj_f;

int global_obj_g;
int *global_ptr_g = &global_obj_g;

int global_obj_h;
int *global_ptr_h = &global_obj_h;

int global_obj_l;
int *global_ptr_l = &global_obj_l;

int global_obj_m;
int *global_ptr_m = &global_obj_m;

class A {
  public:
    virtual void f(int *i) {

    }
};

class B: public virtual A {
  public:
    virtual void g(int *i) {

    }
};

class C: public virtual A {
  public:
    virtual void h(int *i) {

    }
};

class D {
  public:
    virtual void l(int *i) {

    }
};

class E: public B, public C, public D {
  public:
    virtual void m(int *i) {

    }
};

int main(int argc, char **argv)
{
  int *ptr_f = &global_obj_f;
  int *ptr_g = &global_obj_g;
  int *ptr_h = &global_obj_h;
  int *ptr_l = &global_obj_l;
  int *ptr_m = &global_obj_m;

  A *pa;
  B *pb;
  C *pc;
  D *pd;
  E *pe;

  E e;

  pa = &e;
  pa->f(ptr_f);

  pb = &e;
  pb->g(ptr_g);

  pc = &e;
  pc->h(ptr_h);

  pd = &e;
  pd->l(ptr_l);

  pe = &e;
  pe->m(ptr_m);

  return 0;
}
