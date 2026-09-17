// <svf-test-suite>@64f017e/src/basic_cpp_tests/func-ptr-in-class.cpp

int global_obj_f;
int *global_ptr_f = &global_obj_f;

int global_obj_g;
int *global_ptr_g = &global_obj_g;

int global_obj_f_v;
int *global_ptr_f_v = &global_obj_f_v;

int global_obj_g_v;
int *global_ptr_g_v = &global_obj_g_v;

void f(int *i) {

}

void g(int *i) {

}

class A {
  public:
    virtual void f(int *i) {

    }
    virtual void g(int *i) {

    }
    void (*pf)(int *i);
    void (*pg)(int *i);
};

int main(void)
{
  int *ptr_f = &global_obj_f;
  int *ptr_g = &global_obj_g;
  int *ptr_f_v = &global_obj_f_v;
  int *ptr_g_v = &global_obj_g_v;

  A *a = new A;
  a->pf = &f;
  a->pg = &g;

  a->pf(ptr_f);
  a->pg(ptr_g);

  a->f(ptr_f_v);
  a->g(ptr_g_v);

  return 0;
}
