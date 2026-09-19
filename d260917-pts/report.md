# d260917-pts

## Purpose

- d260917-suite 还不是完整的 test-case，我们需要动态方法给出 query 和对应的 oracle，这样才能用于测试分析器

## Data Generation

- 精度：流不敏感+上下文不敏感
- 所用插桩器
    - instrument 与 hook in PTACXX@d3b178a
    - 插桩器可靠性如何？
        - 简单地测过，能用
- 插桩方式
    - 输入：`d260917-suite/blob/{llvm14,llvm21}` 下的 `.ll`
    - 脚本：`instrument.py <LLVM_PATH> --instrument <bin> --hook <so> [--libcxx-lib DIR] [--src DIR] [--blob DIR] [--label LABEL] [--list FILE] [--mode FLAG] [--k N]`
        - 流水线：`.ll` → `instrument -mode-ptr` → `clang++ + libhook.so` → 运行
        - 产物镜像输入目录到 `blob/<ver>/`：`<src>.ll.inst.bc`、`<src>.ll.inst`、`<src>.ll.pts`，以及 `results.csv`、`instrument.log`（失败时另有 `logs/`）
        - 运行时 `PTACXX_MODE=1`、`PTACXX_K=0`、`PTACXX_DUMP_PATH=<src>.ll`，hook 自行追加 `.pts`
```bash
# LLVM 21
python3 instrument.py <LLVM21> \
--instrument <BUILD21>/src/instrument/instrument \
--hook       <BUILD21>/src/hook/libhook.so \
--libcxx-lib <LIBCXX> \
--src <SUITE>/blob/llvm21

# LLVM 14
python3 instrument.py <LLVM14> \
--instrument <BUILD14>/src/instrument/instrument \
--hook       <BUILD14>/src/hook/libhook.so \
--libcxx-lib <LIBCXX> \
--src <SUITE>/blob/llvm14 \
--list <LIST>
```

- 剔除用例
    - `c/c89-basic-address-dereference-test-recursiveglobal.c`
    - `c/c89-member-access-path13-struct-field-alias.c`
    - 原因：程序依赖未初始化值（UB），插桩改变内存布局后行为翻转、运行 segfault（`rc=-11` / `rc=139`）；未插桩时只是恰好 `rc=0`，并非真正可运行
    - 处理：从数据集中剔除
- 简单检查dump结果
    - pts 打头
    - 行完整


## Data Result

| 指标 | llvm14 | llvm21 |
|---|---|---|
| 用例数 | 921 | 923 |
| 运行成功（rc=0） | 921 | 921 |
| 运行失败（已排除） | 0 | 2（UB 用例） |
| 非空 pts 用例 | 866 | 866 |
| pts 行数合计 | 150,159 | 123,882 |
| pts 边数合计（target 总数） | 170,035 | 140,440 |
| 插桩流水线总耗时 | 1212.1 s | 1147.0 s |

- 分布 `distributions.png`

## Usage

- crash fix
    - e260917-lotus-crash-fix
- unsoundness fix

## Other

- TODO
    - 插桩器对 null pointer 的支持
    - 插桩器对 流敏感和上下文敏感 的支持
