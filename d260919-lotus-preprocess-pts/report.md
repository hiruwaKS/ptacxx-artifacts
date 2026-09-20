# d260919-lotus-preprocess-pts

## Purpose

- 产出"IR 预处理后"的 pts 数据集，作为 `d260917-pts` 的重要修复：**索引（VId / alias spec）与分析使用同一份已规范化的 `M`**。
- 解决 `e260917-lotus-crash-fix` 遗留的 **IR 变换问题**（见该 artifact 的 `Other / 局限性` 与 `Data Generation / 意外`）：
    - 部分分析器（TPA / AserPTA / SeaDsa）的前置 pass 会改写 IR，使索引所基于的模块与分析所用模块不是同一份；pts dump 里的查询 `Value` 在变换后的模块中已无对应定义（`stripPointerCasts` 后成野指针、从不进 ptrManager 注册表），从而 crash / 语义错误。

## Data Generation

- 自变量：是否启用 `lotusIRPreprocess`。
    - baseline：`lotus@5cce9f78`
    - fix：分支 `fix-common-ir-preprocess`，从 baseline 切出，只含该 pass 及接入代码。
- 控制变量：llvm 版本、案例集、analyzer index 与参数、instrument/pts 数据、timeout 阶梯、并发数（均与 crash-fix 一致，便于直接 diff）。


- 工具与参数
    - `<ptacxx>/driver --output-ir <path>`：新增，`init()` 后 dump 当前模块；默认关。
    - `<ptacxx>/irHash <file.ll|.bc>`：独立工具，算模块**结构 hash**（对命名 / debug info / metadata 不敏感）。
    - 整条预处理链路（原始 `.ll` vs 跑完后的模块），只回答"这条链路有没有改 IR"
    - 实现要点
        - LLVM14 无 `StructuralHash`（LLVM16+ 才有），按同口径自实现；随 `src/tools/` 一起编；细节见 ptacxx 仓库，此处不展开。
        - LLVM21 有
    - 自检
        - 稳定：同一文件重复计算一致；改命名 / 开关 debug info 不影响 hash。
        - 敏感：真正改指令（比较谓词、返回值）会改变 hash。
        - 覆盖：同一 case 跑全部 25 个 index 配置，未被变换时 hash 与原始 `.ll` 一致。
    - AserPTA 预处理 bug 修复
        - 意外：aser 预处理在约 300/921 个含 `invoke` 的 case 上产出无效 IR（unwind 目标非 landingpad），verifier abort；已修复，修后 921 case 全部合法。

- 重新构建数据集
    - 确定重建范围
        - llvm14
        - tpa(2)、aser(9–13)、seadsa(19–25)
    - 参见 `d260917-pts/report.md` 中间加上一步：经过分析器
    - 升级，记录表改成 caseId（避免记录过长路径）、status、instrument time、dynamic aa time、ir size expansion、pts lines
    - 这里限制 AserPTA 的案例数到 907 个（因为异常控制流未建模）

## Data Result

- 重建范围：llvm14；分析器 tpa / aser / seadsa（前置 pass 会改写 IR，oracle 必须从 M\* 重建），另留 aa 作为 no-preprocess 的参照。
- 用例数：aser 907（额外排除 14 个异常控制流用例，异常控制流未建模）；其余均 921（统一排除 2 个 UB 用例）。

| 分析器 | 用例数 | 运行成功 | 非空 pts | pts 行数合计 |
|---|---|---|---|---|
| tpa | 921 | 921 | 921 | 152195 |
| aser | 907 | 907 | 907 | 146347 |
| seadsa | 921 | 921 | 921 | 151096 |
| no-preprocess | 921 | 921 | 921 | 151081 |

- 产物位置
    - `blob/llvm14-<analyzer>-pts/<sub>/<caseId>.ll.inst.bc|.inst|.ll.pts`：重建后的 oracle 数据集
    - `blob/llvm14-<analyzer>-pts/results.csv`：caseId、status、instrument time、dynamic aa time、ir size expansion、pts lines
    - `blob/llvm14-<analyzer>-pts/results.md`：汇总
    - `blob/<analyzer>/<caseId>.ll`：预处理后 M\*
    - `blob/work/<analyzer>/mstar/<sub>/<caseId>.ll`：喂给插桩的 staging 树

## Usage

## Other
