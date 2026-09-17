// <original>

using namespace std;
struct file_operations {
  int (*open)(void*);
  int (*read)(void*);
  int (*write)(void*);
};
static int my_open(void* p) {
  return 0;
}
static int my_read(void* p) {
  return 0;
}
static int my_write(void* p) {
  return 0;
}

int main() {
  static file_operations fops = {my_open, my_read, my_write};
  file_operations* ops = &fops;
  int op = 0;
  void* arg = nullptr;
  if (op == 0)
    ops->open(arg);
  return 0;
}
