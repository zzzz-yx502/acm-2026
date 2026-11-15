# Git 入门备忘（Day 1）

## 一、三个区域

```
工作区（Working Directory）  --git add-->  暂存区（Index/Stage）  --git commit-->  版本库（Repository）
                                                                                    |
                                                                             --git push-->  远程仓库（Remote）
```

理解要点：`git add` 不是"保存文件"，是**挑选这次要提交的改动**放进暂存区。
`git commit` 才是真正生成一个版本快照。

## 二、最小命令集

| 命令 | 作用 |
| --- | --- |
| `git init -b main` | 在当前目录初始化仓库，主分支叫 main |
| `git status` | 看当前状态（最常用，不确定就敲它） |
| `git add <文件>` | 把指定文件加入暂存区 |
| `git add .` | 把当前目录所有改动加入暂存区 |
| `git commit -m "说明"` | 提交暂存区内容，生成一个版本 |
| `git log --oneline --graph` | 查看提交历史 |
| `git diff` | 看工作区 vs 暂存区的差异 |
| `git diff --staged` | 看暂存区 vs 最新提交的差异 |

## 三、远程相关

| 命令 | 作用 |
| --- | --- |
| `git remote add origin <url>` | 关联远程仓库，命名为 origin |
| `git remote -v` | 查看已关联的远程地址 |
| `git push -u origin main` | 首次推送并建立跟踪关系 |
| `git push` | 之后直接推送 |
| `git pull` | 拉取远程更新 |

## 四、撤销与回滚（按危险程度递增）

| 场景 | 命令 | 危险度 |
| --- | --- | --- |
| 改了文件想丢弃改动 | `git restore <文件>` | 低（只动工作区） |
| 已 add，想撤回暂存 | `git restore --staged <文件>` | 低 |
| 刚提交，想改提交信息 | `git commit --amend -m "新信息"` | 中（改历史） |
| 想撤销最近一次提交但保留改动 | `git reset --soft HEAD~1` | 中 |
| 想彻底丢弃最近一次提交和改动 | `git reset --hard HEAD~1` | **高** |
| 已推送的错误提交，想用新提交抵消 | `git revert <commit>` | 低（安全，生成反向提交） |

铁律：**已经 push 到远程的提交，不要用 reset 改历史，用 revert。**

## 五、本仓库约定

- 主分支：`main`
- 提交信息：`feat: 洛谷 P3371 堆优化 dijkstra`
- 编译产物（`*.exe`、`*.out`）不入库，已在 `.gitignore` 排除

## 六、今日踩坑记录

（实操中遇到的问题记在这里）

1.
2.
3.
