# Git 零基础完整流程手册

> 读者：完全没用过 Git，也不知道命令行怎么操作。
> 目标：照着走一遍，3 小时内把本地代码推到 GitHub，并且理解每一步在干什么。

---

## 第 0 章 先分清：哪些事在终端做，哪些事在网页做

这是新手第一个卡点。Git 和 GitHub 是**两个东西**：

| | 是什么 | 装在哪 | 你在这里做什么 |
| --- | --- | --- | --- |
| **Git** | 一个版本控制程序 | 你自己的电脑上 | 记录改动、生成版本、本地回滚 |
| **GitHub** | 一个网站，提供远程仓库托管 | 浏览器 | 建空仓库、看推送结果、在线浏览代码 |

**所以：`commit` 只能在你电脑的终端里敲，GitHub 网页上没有这个按钮。**
网页上你只需要做一件事：**建一个空的仓库**，拿到它的地址。

> 比喻：
> - Git 是你手里的摄像机和一卷录像带，`commit` = 按下快门拍一张快照存进本地录像带。
> - GitHub 是云端备份盘，`push` = 把录像带寄到云端。
> - 不 push 也不会丢东西，只是只存在你这台电脑上，换台机器或硬盘坏了就没了。

---

## 第 1 章 怎么打开终端（Windows）

**终端**（也叫命令行、黑窗口）是一个只能用键盘输入文字命令的窗口。三种打开方式，任选一种：

1. **开始菜单搜 `Git Bash`**，回车。本手册默认用这个。
2. 打开仓库文件夹（`C:\Users\charry\acm-2026`），在空白处**右键 → Open Git Bash here**（Win11 若没看到，先按 `Shift + 右键` → 显示更多选项）。
3. 用 VS Code 打开这个文件夹，按 `` Ctrl + ` `` 调出集成终端。

打开后你会看到一个窗口，里面有一行字类似：

```
charry@DESKTOP MINGW64 ~
$
```

**三条必须知道的命令行常识：**

| 常识 | 说明 |
| --- | --- |
| `$` 不是你输的内容 | 它是"提示符"，意思是"我准备好了，请你输入"。你只输 `$` 后面的东西。 |
| 按 `Enter` 才执行 | 打错字直接按 Enter 会执行错误命令，用 `←` 退格改完再按。 |
| 粘贴方式特殊 | Git Bash 里用 **鼠标右键 → Paste**，或 `Ctrl + Insert`。直接 `Ctrl+V` 在部分版本无效。 |

还有一个高频困惑：**命令行没有"当前文件夹"的可视化界面**。你人在哪个目录，靠 `pwd` 查看（print working directory，打印当前工作目录）。

---

## 第 2 章 一条命令长什么样：逐词解剖

所有 Git 命令都遵循这个结构：

```
程序名   子命令   选项        参数
  ↓        ↓       ↓           ↓
 git    commit   -m "..."    （无）
```

| 位置 | 叫什么 | 作用 | `git commit -m "初始化"` 里对应 |
| --- | --- | --- | --- |
| 第 1 个词 | 程序名 | 你要运行哪个软件 | `git` |
| 第 2 个词 | 子命令 | 让这个软件做哪件事 | `commit`（提交） |
| 带 `-` 的词 | 选项/参数开关 | 调整这件事的细节 | `-m`（message，附言） |
| 引号里的内容 | 值 | 具体内容 | `"初始化"` |

**记住这个模式，后面所有命令你都能自己读懂。** 比如 `git push -u origin main`：程序 `git` + 做 `push`（推送）这件事 + 选项 `-u` + 两个参数 `origin`（推到哪个远程）和 `main`（推哪个分支）。

**术语对照表（后面会反复出现）：**

| 词 | 读音/含义 | 一句话解释 |
| --- | --- | --- |
| repository / repo | 仓库 | 一个被 Git 管理的文件夹 |
| branch | 分支 | 一条独立的开发线，默认叫 `main` |
| origin | — | 给远程仓库起的默认名字，只是个代号，可以改 |
| main | — | 主分支的名字（老版本 Git 默认叫 `master`） |
| stage / index | 暂存区 | 一个缓冲区，存放"本次要提交的改动" |
| commit | 提交 | 一次快照，是版本历史里的一个节点 |
| remote | 远程 | 指 GitHub 上那个仓库 |
| push | 推送 | 把本地提交上传到远程 |
| pull | 拉取 | 把远程的更新下载到本地 |

---

## 第 3 章 完整流程：12 步，逐步拆解

> 每一步给五个信息：**【在哪做】【敲什么】【看到什么】【意味着什么】【为什么】**
> 请在终端里一步一步跟着敲，**不要一次性粘贴全部**。看到预期输出再进入下一步。

---

### 步骤 1｜进入仓库目录

**【在哪做】** 终端
**【敲什么】**
```bash
cd /c/Users/charry/acm-2026
```
**【看到什么】** 什么也不显示。命令行没消息就是好消息。
**【意味着什么】** `cd` = change directory，切换目录。Windows 的 `C:\Users\...` 在 Git Bash 里要写成 `/c/Users/...`（反斜杠换成正斜杠，`C:` 变成 `/c`）。
**【为什么】** 后面所有命令都只对"当前所在目录"生效。走错目录，Git 会报 `not a git repository`。

验证一下：
```bash
pwd
```
应输出 `/c/Users/charry/acm-2026`。

---

### 步骤 2｜配置你的身份

**【在哪做】** 终端
**【敲什么】**（把引号里的内容换成你自己的）
```bash
git config --global user.name "zzzz-yx502"
git config --global user.email "你的GitHub邮箱"
```
**【看到什么】** 无输出。
**【意味着什么】** 逐词拆解：

| 词 | 含义 |
| --- | --- |
| `git` | 运行 Git 程序 |
| `config` | 配置（configuration） |
| `--global` | 全局，即对本机所有仓库生效（不加这个则只对当前仓库生效） |
| `user.name` | 配置项名称：作者名 |
| `"zzzz-yx502"` | 配置项的值 |

**【为什么】** 每一条 commit 都会永久记录"谁在什么时候提交的"。没配的话，Git 会拒绝提交并报错 `Please tell me who you are`。这个信息会公开显示在 GitHub 的提交记录里，所以建议用 GitHub 用户名 + GitHub 绑定的邮箱。

检查是否生效：
```bash
git config --list
```
输出里应包含 `user.name=...` 和 `user.email=...`。

补充一条 Windows 专用配置（解决换行符问题）：
```bash
git config --global core.autocrlf true
```
Windows 用 `CRLF` 换行，Linux/Mac 用 `LF`。不配这个，跨平台协作时会出现"整个文件都变了"的假象。

---

### 步骤 3｜看清当前状态

**【在哪做】** 终端
**【敲什么】**
```bash
git status
```
**【看到什么】**
```
On branch main

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        .gitignore
        README.md
        cf/
        contests/
        notes/
        template/
```
**【意味着什么】** `git status` 是**最常用的命令**，任何时候不确定就敲它。这里的信息是：

- `On branch main` —— 你在 `main` 分支上
- `No commits yet` —— 这个仓库还一次都没提交过
- `Untracked files` —— **未跟踪文件**：文件在你硬盘上真实存在，但 Git 从来没记录过它

**【为什么】** Git 默认**不会**自动管理新文件。新文件必须先被你"点名"，Git 才会开始跟踪它。这是新手最反直觉的一点：`git status` 里看到红色文件 ≠ 出错，只是"还没纳入管理"。

---

### 步骤 4｜把文件放进暂存区

**【在哪做】** 终端
**【敲什么】**
```bash
git add README.md
```
**【看到什么】** 无输出。
**【意味着什么】**

| 词 | 含义 |
| --- | --- |
| `add` | 添加，指"添加到暂存区"——**不是"新建文件"**，文件已经存在了 |
| `README.md` | 要添加的具体文件名，注意大小写必须完全一致 |

**【为什么】** 这是新手最大的误解点。`add` 的真正含义是：**从当前所有改动里，挑出这些，标记为"这次提交要包含"**。之所以要多这一步，是为了让你能精确控制"一次提交里包含哪些改动"——比如你同时改了 5 个文件，但只想提交其中 2 个，靠的就是 `add` 来挑。

> 三个区的比喻：
> - **工作区** = 你的书桌，东西摊得到处都是（你正在编辑的文件）
> - **暂存区** = 桌上的一个纸箱，你把要寄走的东西放进去（`git add`）
> - **版本库** = 封箱、贴单、入库（`git commit`）
> - **远程仓库** = 快递站（`git push`）
>
> 关键：**只有放进纸箱的东西才会被寄走**。桌上剩下的留在原地。

---

### 步骤 5｜确认暂存区里装了什么

**【在哪做】** 终端
**【敲什么】**
```bash
git status
```
**【看到什么】**
```
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   README.md

Untracked files:
        .gitignore
        cf/
        ...
```
**【意味着什么】** `README.md` 从红色（Untracked）移到了绿色（Changes to be committed = 已暂存，等待提交）。其余文件还在 Untracked。
**【为什么】** 养成"`add` 之后必看一眼 `status`"的习惯。这是唯一能防止"误把不该提交的东西提交上去"的动作。

---

### 步骤 6｜看一眼暂存的具体内容

**【在哪做】** 终端
**【敲什么】**
```bash
git diff --staged
```
**【看到什么】** 一份带 `+` 和 `-` 的文本差异，`+` 是新增行，`-` 是删除行。
**【意味着什么】** `diff` = difference（差异）。`--staged` 表示"拿暂存区的内容和上一次提交比"（第一次提交时就是和"空"比，所以全是 `+`）。
**【为什么】** 提交前最后一道自检。能确认"我要提交的确实是这些内容"，而不是误改了别的东西。

> 相关命令：`git diff`（不加 `--staged`）比的是"工作区 vs 暂存区"，即你改了但还没 add 的部分。

---

### 步骤 7｜生成第一个版本（commit）

**【在哪做】** 终端
**【敲什么】**
```bash
git commit -m "chore: 初始化 ACM 仓库骨架"
```
**【看到什么】**
```
[main (root-commit) 3f2a1b9] chore: 初始化 ACM 仓库骨架
 1 file changed, 42 insertions(+)
 create mode 100644 README.md
```
**【意味着什么】** 逐词拆解：

| 词 | 含义 |
| --- | --- |
| `commit` | 提交：把暂存区内容打包成一个永久的版本快照 |
| `-m` | message 的缩写，表示"后面引号里是提交说明" |
| `"chore: 初始化 ACM 仓库骨架"` | 提交说明本身 |

输出解读：
- `[main (root-commit) 3f2a1b9]` —— 在 main 分支上，`root-commit` 表示这是第一个提交（根提交），`3f2a1b9` 是这个版本的**唯一编号（哈希值）**
- `1 file changed, 42 insertions(+)` —— 改了 1 个文件，新增 42 行

**【为什么】** 这是"存档"动作。之后你无论怎么改文件，都可以随时回到这个版本。

> **提交说明怎么写**：格式 `类型: 说明`。常用类型：
> - `feat` 新增功能/新题解
> - `fix` 修复错误
> - `docs` 文档笔记
> - `chore` 杂项/初始化
>
> 写"修复 bug"是废话，写"fix: 洛谷 P3371 数组越界"才有价值——三个月后你会感谢自己。

---

### 步骤 8｜把剩下的文件也提交

**【在哪做】** 终端
**【敲什么】**
```bash
git add .
git commit -m "feat: 添加竞赛模板与 Git 笔记"
```
**【看到什么】** 类似上一步，但显示 `6 files changed`。
**【意味着什么】** `.`（一个点）表示**当前目录下的所有改动**。这是你以后 90% 的操作方式。
**【为什么】** 逐次提交比一次全提交更好：历史更清晰，出问题时能精确回退。但第一次建仓库时，先单文件演示一次流程是值得的。

> `.gitignore` 在这里起作用了：里面写了 `*.exe`、`*.out`，所以编译出来的可执行文件**永远不会**被 `git add .` 抓到。

---

### 步骤 9｜查看提交历史

**【在哪做】** 终端
**【敲什么】**
```bash
git log --oneline
```
**【看到什么】**
```
e4c8a21 (HEAD -> main) feat: 添加竞赛模板与 Git 笔记
3f2a1b9 chore: 初始化 ACM 仓库骨架
```
**【意味着什么】**

| 词 | 含义 |
| --- | --- |
| `log` | 日志，列出所有提交 |
| `--oneline` | 每个提交只显示一行（哈希前 7 位 + 说明），否则会显示作者、日期等一大堆 |
| `HEAD -> main` | `HEAD` 是"你当前所在位置"的指针，指向 main 分支的最新提交 |

**【为什么】** 这是"我做过什么"的账本。加 `--graph --all` 可以看分支的树形结构：`git log --oneline --graph --all`。

---

### 步骤 10｜在 GitHub 上建空仓库

**【在哪做】** 🌐 **浏览器**（这一步终端做不了）

1. 登录 github.com
2. 点右上角搜索框**左边的 `+` 号** → **New repository**
   （或直接在地址栏输入 `https://github.com/new`）
3. **Repository name** 填 `acm-2026`
4. 选 Public 或 Private，都行
5. **下面三个勾选项全部不要勾**：
   - ☐ Add a README file
   - ☐ Add .gitignore
   - ☐ Choose a license
6. 点绿色 **Create repository**

**【意味着什么】** 这一步只是"在云端准备一个空箱子"。
**【为什么第 5 步必须不勾】** 一旦勾选，GitHub 会自动帮你生成一个提交，云端就有内容了。而你的本地仓库也有内容，两边历史互不相干 → `push` 会被拒绝，报 `rejected`。新手最高频的翻车点就在这里。**远程必须是完全空的，才和本地对得上。**

建完后页面会跳到一个带命令提示的页面。它给的命令不用照抄，用我们下面这套。

---

### 步骤 11｜拿到推送凭证（PAT）

**【在哪做】** 🌐 **浏览器**（GitHub 从 2021 年起禁止用账号密码推送）

1. 右上角头像 → **Settings**
2. 左栏拉到最底部 → **Developer settings**
3. 左栏 → **Personal access tokens** → **Tokens (classic)**
4. 右上 **Generate new token** → **Generate new token (classic)**
5. 填写：
   - **Note**：`acm-2026-push`（只是给你自己看的备注）
   - **Expiration**：90 days
   - **Select scopes**：勾选 **`repo`**（整块，它包含仓库读写权限）
6. 拉到底点 **Generate token**
7. **立刻复制** `ghp_xxxxxxxx...` 这串字符

**【意味着什么】** PAT = Personal Access Token，一串代替密码的令牌。
**【为什么】** 它比密码安全：可以限定权限范围、可以设置过期时间、可以随时吊销而不影响账号本身。页面刷新后就再也看不到这串字符了，丢了只能重新生成。

---

### 步骤 12｜关联远程仓库并推送

**【在哪做】** 终端
**【敲什么】**
```bash
git remote add origin https://github.com/zzzz-yx502/acm-2026.git
```

**【看到什么】** 无输出。
**【意味着什么】** 逐词拆解：

| 词 | 含义 |
| --- | --- |
| `remote` | 远程仓库相关操作 |
| `add` | 添加一个远程地址（这里的 add 和 `git add` 完全无关） |
| `origin` | 你给这个远程起的**代号**，行业惯例就叫 origin，你也可以叫别的 |
| `https://...` | 远程仓库的实际地址 |

验证：
```bash
git remote -v
```
输出应有两行（fetch 和 push 各一行）：
```
origin  https://github.com/zzzz-yx502/acm-2026.git (fetch)
origin  https://github.com/zzzz-yx502/acm-2026.git (push)
```

然后推送：
```bash
git push -u origin main
```

| 词 | 含义 |
| --- | --- |
| `push` | 推送：把本地提交上传到远程 |
| `-u` | `--set-upstream` 的缩写，建立"本地 main 追踪远程 main"的关系。**只在第一次需要** |
| `origin` | 推到哪个远程（步骤 12 起的代号） |
| `main` | 推哪个分支 |

**【看到什么】** 第一次会弹出一个登录窗口（Git Credential Manager）：
- **Username**：填 GitHub 用户名 `zzzz-yx502`
- **Password**：**填步骤 11 复制的 token**，不是你的 GitHub 登录密码

成功后的输出：
```
Enumerating objects: 12, done.
...
To https://github.com/zzzz-yx502/acm-2026.git
 * [new branch]      main -> main
branch 'main' set up to track 'origin/main'.
```

**【意味着什么】** `[new branch] main -> main` = 远程新建了 main 分支，内容来自本地 main。`set up to track` = 追踪关系建立成功。
**【为什么加 `-u`】** 加过之后，以后只需要敲 `git push` 一个词，Git 就知道默认推到 origin 的 main。不加的话每次都要写全 `git push origin main`。

**【验证】** 刷新 GitHub 仓库页面，应能看到 README.md 等全部文件，且提交信息与你本地一致。

---

## 第 4 章 以后的日常：只用四个命令

第一遍走完后，日常开发循环就只剩这些：

```bash
git status              # 1. 看看改了什么
git add .               # 2. 全部放进暂存区
git commit -m "feat: 洛谷 P3371 堆优化 dijkstra"   # 3. 存档
git push                # 4. 上传（-u 只需第一次）
```

外加一个保险动作：**开始干活前先 `git pull`**，把远程最新内容拉下来，避免冲突。

---

## 第 5 章 报错对照表

| 报错原文 | 中文意思 | 怎么处理 |
| --- | --- | --- |
| `fatal: not a git repository` | 当前目录不是 Git 仓库 | `cd` 到仓库目录，或该目录还没 `git init` |
| `Please tell me who you are` | 没配身份 | 回到步骤 2 |
| `src refspec main does not match any` | 本地没有任何提交，没东西可推 | 先完成 `add` + `commit` |
| `remote origin already exists` | 已经加过名为 origin 的远程 | `git remote set-url origin <新地址>` 改地址，不要重复 add |
| `rejected ... fetch first` | 远程有你本地没有的提交 | `git pull --rebase origin main` 然后再 `git push` |
| `Authentication failed` | 认证失败，多半是密码填错 | 密码位置必须填 token，不是账号密码 |
| `error: failed to push some refs` | 推送失败的总称 | 看它上面一行的具体原因，通常是上面两条之一 |
| 中文文件名显示成 `\344\270\255` | 编码显示问题 | `git config --global core.quotepath false`（已配） |
| `nothing to commit, working tree clean` | 没有新改动（**这不是报错**） | 说明所有改动都已提交 |

---

## 第 6 章 验收清单

做完打勾，全部打勾才算这一课过关：

- [ ] `git config --list` 能看到 `user.name` 和 `user.email`
- [ ] `git log --oneline` 至少有 2 条提交记录
- [ ] GitHub 网页上能看到仓库里的全部文件
- [ ] 网页上最新一条提交信息与本地 `git log` 的第一行完全一致
- [ ] 能不看手册说清：`add` / `commit` / `push` 各自把内容从哪个区送到哪个区
- [ ] 能说清"为什么建 GitHub 仓库时不能勾 README"
- [ ] 能说清"push 时密码位置该填什么"

---

## 附：一张图记住数据流向

```
工作区 ──git add──> 暂存区 ──git commit──> 本地版本库 ──git push──> GitHub
   ↑                                                                │
   └────────────────────── git pull ────────────────────────────────┘
```

---

## 今日踩坑记录

（实操中遇到的问题记在这里，写清楚"报错原文 + 原因 + 怎么解决的"）

1.
2.
3.
