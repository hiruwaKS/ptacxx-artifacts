// <original>

typedef void (*CmdHandler)(void);

static void cmdA() {
}
static void cmdB() {
}
static void cmdC() {
}

static CmdHandler jumpTable[3] = {cmdA, cmdB, cmdC};

int main() {
  int code = 0;
  jumpTable[code]();
  return 0;
}
