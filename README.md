# ACM 2026 — 竞赛刷题与工程练习仓库

大二学年竞赛主线（洛谷专题 + Codeforces）与 C++ 工程练习的统一仓库。
目标：题解可检索、模板可复用、提交记录可追溯。

## 目录结构

| 目录 | 用途 |
| --- | --- |
| `template/` | 竞赛通用模板（快读、常用宏、对拍脚本） |
| `luogu/` | 洛谷专题题解，按专题编号命名 |
| `cf/` | Codeforces 题目，按 `contestID-题号` 命名 |
| `contests/` | 正式比赛 / 模拟赛的现场代码与复盘 |
| `notes/` | 算法笔记、专题总结、Git 与工具链备忘 |

## 命名规范

- 洛谷：`luogu/Pxxxx_题名.cpp`，如 `P3371_单源最短路.cpp`
- CF：`cf/1900A_cover_in_water.cpp`（contestID 4 位 + 题号）
- 比赛：`contests/2026-11-15_校赛/a.cpp`

## 提交信息规范

```
<类型>: <简短说明>

类型：feat 新题解 / fix 修正错误 / docs 笔记 / chore 杂项
示例：feat: 洛谷 P3371 堆优化 dijkstra
```

## 目标（2026 学年）

- 刷题量：800–1200 道
- Codeforces Rating：1600 左右
- 竞赛：区域赛铜／银
