// <svf-test-suite>@64f017e/src/ae_nullptr_deref_tests/int_ptr_uninit_ptr.c

static void UNSAFE_LOAD(void *ptr) { (void)ptr; }

int main() {
  int* p;
  UNSAFE_LOAD(p);
}
