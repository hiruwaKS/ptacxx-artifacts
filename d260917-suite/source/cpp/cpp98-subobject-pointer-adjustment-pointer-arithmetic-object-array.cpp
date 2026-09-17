// <svf-test-suite>@64f017e/src/basic_cpp_tests/pwc.cpp

#define LEN 100

int global_obj_f;
int *global_ptr_f = &global_obj_f;

int global_obj_g;
int *global_ptr_g = &global_obj_g;

class A {
  public:
    virtual void f(int *i) {

    }
    virtual void g(int *i) {

    }
    double *f1;
    int *f2;
    int *f3;
};

int main(int argc, char** argv)
{
  int *ptr_f = &global_obj_f;
  int *ptr_g = &global_obj_g;

  A a_array[LEN];
  A *pa;

  pa = a_array;
  for (int i = 0; i < LEN/2; ++i)
    pa += 1;

  pa->f(ptr_f);
  pa->g(ptr_g);

  return 0;
}
