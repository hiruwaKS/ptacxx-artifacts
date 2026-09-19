# e260917-lotus-crash-fix

## Purpose

- 用现在的指向集结果测试 lotus 各种分析器，修复 crash

## Data Generation

- 跨仓库编译（见附录A）
- 上下文不敏感、流不敏感分析器选择
    - 硬性要求
        - CI（上下文不敏感）：pts 由上下文不敏感的插桩器生成，不选 CS 相关（`--k-limit>0`、`--andersen-k-cs>0`、`--analysis-mode=cs1/cs2/origin`）。
        - FI（流不敏感）：不选 FS（流敏感）相关选项。
    - 不做正交：每个 index 相对 base 只改一个变量。
    - 偏好
        - 常用性：优先默认 / 常用档位。
        - 选项覆盖：尽量覆盖不同实现路径（存储、求解器、优化、调用图、归一化）。
    - 例外（不参与对比，仅测 crash）
        - LotusAA、Lotus-tpa 本身为流敏感，指向集与 CI/FI oracle 不可比；仍纳入本任务做 crash 检测。
- 基准版本
    - lotus@7503f45f
    - 编译基准版本
- 数据收集标准
    - 在 `d260917-suite` 里面找 案例，传入分析器，在 `d260917-pts` 找 pts 文件运行（driver 的 `pts-test` 指令），把分析器输出结果 dump 到 `blob/<baseline or fix>/<analyzer index>`
        - 每个 llvm 版本 921 个案例
    - 解决 AliasSpecManager 找不到的问题
        - 去 ptacxx 或者 lotus 目录运行
    - watchdog 机制
        - 墙钟计时会算上排队时间
        - 让程序主动在 timeout 时间退出
        - timeout 选多大？
            - 1s -> 4s -> 16s 递进
    - name区分
        - 对于stl-sensitive，加上stl前缀区分
    - pts-test 正常数据 csv
        - name
        - 所有的init信息，铺平（5列）
        - pass xx; fail xx; unresolved xx（3列）
    - pts-test 异常文件 csv
        - name
        - 分类：init/query × error/abort/segfault/other + timeout（1列）
        - 具体（1列）
            - init error（escape 转义回车到一行）
            - pts-test query error
            - crash (abort sigfault 区分)
- 评估/批量运行
    - `runIndexes.py` 内置附录 B 的 25 个 index；`AN_DIR`、`LOTUS_CONFIG_DIR` 必填。
    - `<EXPERIMENT_DIR>`：`e260918-lotus-crash-fix`
    - `<ANALYZER_DIR>`：存放 `lotus-{aa,tpa,sparrow-aa,aser-aa,un-dyckaa,un-seadsa-aa}` 的目录
    - `<CONFIG_DIR>`：含 `ptr.spec` / `modref.spec` 的目录
- 修复产物目录 `blob/fix/`（仿 `blob/baseline/`）
    - `<index>/{pts-test-normal,abnormal}.csv`：分分析器 integration 结果，与 `blob/baseline/<index>/` 直接 diff
    - `issue-<analyzer>-<slug>.md`：每个独立修复一份 issue
    - `branch.txt`：独立修复分支与分分析器 integration 分支清单
    - 生成：切到 `fix-integration-<analyzer>` 重编后 `./runIndexes.py fix <index...>`
- 意外
    - 发现 seadsa 全崩了，打算先修，不然 seadsa 没有有意义结果
    - 就是一个 pass 没注册问题，简单修复
    - AserPTA、SeaDsa driver 的 pipeline 含会改 IR
    - TODO：给 SeaDsa/TPA/AserPTA 加 **IR 规范化** 支持——把 ptrtoint→bitcast 的 pass 放进 `common`，在 `loadMainModule` 之后、`buildModuleIndex()` 之前跑一次，使索引与建图用同一份已规范化的 `M`
    - 最后决定不做 seadsa 的实验
- 应对意外：筛出“已知 IR 变换问题、不修复”
    - 依据：前置 pass 的 IR 变换使查询指针变野指针，其余正常指针仍指向原文 IR 值
    - 筛出标准
        - 崩溃 Value 在 stripPointerCasts 后于当前 IR 无对应定义，而其他查询 Value 均有对应指令
        - 该 Value 从不进 ptrManager 注册表（getPointersWithValue 返回空），同类正常 Value 有记录
        - 用未跑前置 pass 的原始模块同 query 不崩，跑过 transform 的模块才崩
        - 崩溃指针仅出现在 query 侧，模块全局 use/def 链中无任何指向它的引用
    - 对于 AserPTA 抽样
- 独立修复
    - 用 git branch
    - 先调试，看看哪里崩溃，找根因
    - 分支命名：用根因，命名 `fix-<analyzer>-<slug>`（analyzer 取 `lotus|tpa|sparrow|aser|dyckaa|seadsa|common`，slug 用 kebab-case 简述且不含 `fix`，如 `fix-aser-null-deref`）；每条分支从 `baseline` 切出、只含一个修复；分分析器汇总分支为 `fix-integration-<analyzer>`
    - 每次修复只能基于一个基准版本，和基准版本做差分
        - 除非这个修复非常关键，是整体性
    - 得到分支
    - 整合验证
    - 再评估
        - 先独立评估（每个修复分支）
            - 只重跑受影响 index，与 baseline 同 index 差分，确认
                - 原 crash（initError / query error / abort / sigfault / timeout）消失
                - 未引入新 crash：pass/fail/error 计数与 baseline 相比无回退，异常文件集合只减不增
                - pts 结果差异仅落在该修复的预期范围内；若有超预期差异，回到根因重新判断
            - 评估
        - 再整体验证
            - 合并各修复增量到对应 `fix-integration-<analyzer>`
            - 评估
- 确认
    - 问题：批量结果的 `class` 列里，crash 与纯慢**都可能是 `timeout`**（abort 后进程卡在打印 stack dump，被 watchdog 杀掉），只看 CSV 分不出来。
    - 方法：对 abnormal 的 case 用 `--dump-dir` 复跑并**放宽 timeout，统计每个 case 实际跑完的时间**：
        - 能跑完（有 `<init>` + `<queryresult>`）→ 单纯慢，其 `<init>` 里的 `total`（或 `analysis`）即实际耗时
        - 跑不完 / 含 `PLEASE submit` / `Stack dump` / `Assertion ... failed` → crash（abort / sigfault）
- issue 格式
    - [<AA name>] crashes on ... test 如果有需要 under <配置>
    - 案例与观察
        - 指向public的文件或者直接复制进去
    - 根因
    - 修复
        - 为什么能修复
        - 为什么放这个函数
        - 为什么放函数的这一段，而不是函数的别处（特别是一个线性结构的函数，说清楚先后关系很关键）
        - 这个函数原先的复杂度怎么样，会不会引入一些更高复杂度？（比如在O(1)操作里面引入了一个遍历全IR的操作）
    - 验证

## Data Result

- baseline 1-18：18 index × 921 case
- fix：11 分支 / 25 index-run × 921 case
- integration：4 分支 / 13 index × 921 case
- 修复分支
    - lotus：`fix-lotus-cyclic`、`fix-lotus-unreachable-anchor`、`fix-lotus-minor`
    - tpa：`fix-tpa-extractvalue-resolve`、`fix-tpa-formal-params`、`fix-tpa-addr-taken-entry`、`fix-tpa-loadstore-memlevel`、`fix-tpa-call-dest`
    - sparrow：`fix-sparrow-nonptr-constant`、`fix-sparrow-global-alias`
    - dyckaa：`fix-dyckaa-atomic`
- 各种统计分布见图（`fix.png` `fix-time-growth`）
    - 除了 AserPTA、SeaDsa 其他分析器的 crash 被完全修复
    - 除了 tpa-load-store 的修复，其他时间变化不大，这说明确实这个修复极大影响了传播

## Conclusion

- 成功地修复了 lotus 的 crash
- 发现一点，最好不要删掉开发者的 assert，assert 往往是最能体现开发者对于代码的理解，删掉后往往会导致语义错误

## Other

- 局限性
    - IR transform 问题未考虑是实验的最大败笔，现在的 IR 编号是错误的，整体的结构会改变（AserPTA、SeaDsa 不修的原因）

## 附录 A：跨仓库编译

```bash
# lotus AA
cmake --build <LOTUS_BUILD> --target LotusAA CanaryParallel CanaryGSA CanaryPlatform AliasSpecManager CanaryLLVMUtils Annotation
cmake --build <PTACXX_BUILD> --target lotus-aa
# TPA
cmake --build <LOTUS_BUILD> --target FSCSPointerAnalysis TPATransforms CanaryAliasCLIUtils CanaryLLVMUtils Annotation
cmake --build <PTACXX_BUILD> --target lotus-tpa
# Sparrow AA
cmake --build <LOTUS_BUILD> --target Andersen CanaryAliasPtsSet CanaryCUDD AliasSpecManager CanaryLLVMUtils Annotation
cmake --build <PTACXX_BUILD> --target lotus-sparrow-aa
# AserPTA
cmake --build <LOTUS_BUILD> --target AserPTA CanaryAliasCLIUtils CanaryAliasPtsSet CanaryCUDD AliasSpecManager CanaryLLVMUtils Annotation
cmake --build <PTACXX_BUILD> --target lotus-aser-aa
# (unification-based) DyckAA
cmake --build <LOTUS_BUILD> --target CanaryDyckAA CanaryCFG CanaryParallel AliasSpecManager CanaryLLVMUtils Annotation
cmake --build <PTACXX_BUILD> --target lotus-un-dyckaa
# (unification-based) SeaDsa
cmake --build <LOTUS_BUILD> --target SeaDsaAnalysis
cmake --build <PTACXX_BUILD> --target lotus-un-seadsa-aa
```

## 附录 B：Analyzer Index

| Index | Analyzer | Extra Parameters |
| --- | --- | --- |
| 1 | LotusAA |  |
| 2 | Lotus-tpa | `--k-limit=0` |
| 3 | Sparrow-AA (base) | `--andersen-k-cs=0` |
| 4 | Sparrow-AA (bdd) | `--andersen-k-cs=0 --andersen-use-bdd-pts` |
| 5 | Sparrow-AA (hcd) | `--andersen-k-cs=0 --enable-hcd` |
| 6 | Sparrow-AA (hu) | `--andersen-k-cs=0 --enable-hu` |
| 7 | Sparrow-AA (hvn) | `--andersen-k-cs=0 --enable-hvn` |
| 8 | Sparrow-AA (lcd) | `--andersen-k-cs=0 --enable-lcd` |
| 9 | Lotus-aser-aa (base) | `--analysis-mode=ci` |
| 10 | Lotus-aser-aa (solver-basic) | `--analysis-mode=ci --solver=basic` |
| 11 | Lotus-aser-aa (solver-deep) | `--analysis-mode=ci --solver=deep` |
| 12 | Lotus-aser-aa (field-nosens) | `--analysis-mode=ci --field-sensitive=false` |
| 13 | Lotus-aser-aa (bdd) | `--analysis-mode=ci --pta-use-bdd-pts` |
| 14 | un-DyckAA |  |
| 15 | un-DyckAA (iter-10) | `--dyckaa-inter-iteration=10` |
| 16 | un-DyckAA (type-check-0) | `--function-type-check-level=0` |
| 17 | un-DyckAA (cast-comb) | `--with-function-cast-comb` |
| 18 | un-DyckAA (workers-4) | `--nworkers=4` |
| 19[未] | un-SeaDsa (ci) | `--sea-dsa=ci` |
| 20[未] | un-SeaDsa (type-aware) | `--sea-dsa=ci --sea-dsa-type-aware` |
| 21[未] | un-SeaDsa (devirt) | `--sea-dsa=ci --sea-dsa-devirt` |
| 22[未] | un-SeaDsa (no-trust-args) | `--sea-dsa=ci --sea-dsa-trust-args=false` |
| 23[未] | un-SeaDsa (ext-alloc) | `--sea-dsa=ci --sea-dsa-assume-external-functions-allocators` |
| 24[未] | un-SeaDsa (clib-spec) | `--sea-dsa=ci --sea-dsa-use-clib-spec` |
| 25[未] | un-SeaDsa (no-td-copying) | `--sea-dsa=ci --sea-dsa-no-td-copying-opt` |
