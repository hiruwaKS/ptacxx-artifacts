// <original>

struct Cmd {
  int code;
  void (*handler)(void);
};
static void cmdA() {
}
static void cmdB() {
}
static Cmd cmds[] = {{0, cmdA}, {1, cmdB}};
int main() {
  cmds[1].handler();
  return 0;
}
