[TOC]

# 【算法】苹果一道“24点”类型的面试题详细解析，小班同学也直呼通俗易懂

## 引言

今天看到一道24点类型的问题，题目来自[b站动态](https://b23.tv/kEQpICc)。因为原题题意不清晰，所以我在此描述得更清晰一些：

对于`0 0 0`到`10 10 10`这11组数，请填入运算符凑出6。允许使用的二元运算符包括`** * / % + - << >> & | ^`，允许使用的一元运算符包括`sqrt, fac`（根号、阶乘），允许使用括号。每一次的二元运算结果都可以使用至多一次一元运算符，比如`((0! + 0!)! + 0!)! = 6`是合法的。其中除法需要除得尽才合法。

[本文GitHub传送门](https://github.com/Hans774882968/apple-interview-24point-similar)

## 表达式树介绍

24点的dfs比较好理解，但如果没有专门学习过很难自己想出来。首先我们要了解**表达式树**。以下面这棵表达式树为例：

```
  *
 / \
1   +
   / \
  2   3
```

它表示表达式`1 * (2 + 3)`。表达式树的叶子节点为数字，非叶子节点为二元运算符。我们dfs遍历这棵树，走到非叶子节点，需要先获取左右子树的运算结果，再根据该点的符号获取当前子树的运算结果。

表达式树也可以很轻松地表示一元运算符。比如：

```
  *
 / \
1   +
   / \
  2  fac
      |
      3
```

表示表达式`1 * (2 + 3!)`。实际上，表达式树是**抽象语法树**（Abstract Syntax Tree，AST）的特殊情况，如果你有前端基础，可以进[astexplorer](https://astexplorer.net/)快速学习。

## 算法实现

然后我们就可以理解24点的dfs了。最初有`n`个数，相当于有`n`个单节点的树。我们每次选择两棵子树进行合并，合并`n - 1`次后就得到最终的表达式树。使用dfs枚举所有可能的合并方案即可。

接下来看下实现，以[hdu1427](https://acm.hdu.edu.cn/showproblem.php?pid=1427)为例：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int SZ = 4;

char s[SZ][3];
bool vis[SZ];
int a[SZ];

template<typename Type>inline void read (Type &xx) {
    Type f = 1;
    char ch;
    xx = 0;
    for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar() ) if (ch == '-') f = -1;
    for (; ch >= '0' && ch <= '9'; ch = getchar() ) xx = xx * 10 + ch - '0';
    xx *= f;
}

int getn (char s[]) {
    if (strlen (s) == 2) return 10;
    else if (s[0] == 'A') return 1;
    else if (s[0] == 'J') return 11;
    else if (s[0] == 'Q') return 12;
    else if (s[0] == 'K') return 13;
    return s[0] - '0';
}

bool dfs (int dep) {
    if (dep == SZ - 1) {
        for (int i = 0; i < SZ; ++i) {
            if (!vis[i]) {
                if (a[i] == 24) return true;
            }
        }
        return false;
    }
    bool fl = false;
    for (int i = 0; i < SZ; ++i) {
        if (vis[i]) continue;
        for (int j = i + 1; j < SZ; ++j) {
            if (vis[j]) continue;
            vis[j] = true;
            int x = a[i], y = a[j];
            if (y && x % y == 0) {
                a[i] = x / y;
                if (dfs (dep + 1) ) fl = true;
            }
            if (x && y % x == 0) {
                a[i] = y / x;
                if (dfs (dep + 1) ) fl = true;
            }
            a[i] = x + y;
            if (dfs (dep + 1) ) fl = true;
            a[i] = x - y;
            if (dfs (dep + 1) ) fl = true;
            a[i] = y - x;
            if (dfs (dep + 1) ) fl = true;
            a[i] = x * y;
            if (dfs (dep + 1) ) fl = true;
            a[i] = x;
            vis[j] = false;
        }
    }
    return fl;
}

int main (int argc, char **argv) {
    while (~scanf ("%s%s%s%s", s[0], s[1], s[2], s[3]) ) {
        for (int i = 0; i < SZ; ++i)
            a[i] = getn (s[i]);
        memset (vis, 0, sizeof vis);
        puts (dfs (0) ? "Yes" : "No");
    }
    return 0;
}
```



1. `vis[i] = true`表示`i`号子树属于其他的树，`vis[i] = false`表示`i`号树未被合并过。
2. `a[i]`存`i`号子树的求值结果。
3. 这里是用`i`号来存合并后的树，你想改成`j`号也行。如果你想early return，需要记得**恢复现场**：`a[i] = x; vis[j] = false; return true;`。
4. 如果你想获取生成的表达式，那么你必须引入一个`string ans[N]`。

接下来考虑一元运算符怎么实现。

1. 对于叶子，我们在dfs外部枚举3进制位，约定0表示不变，1表示变为阶乘，2表示变为根号。如果要支持其他一元运算符，比如`- ~`，就相应改成枚举4、5进制位即可。
2. 对于非叶子，在dfs内部进行变换即可。

现在我们已经理解了算法，接下来只需要讲下实现上的细节：

1. 每个运算符都需要考虑准入条件。比如`**, fac`需要防止结果过大（引入`powTooLarge`函数）、`/ %`需要保证除数不为0、`sqrt`需要保证原数是完全平方数（引入`isPerfectSquare`函数）。
2. 输出量较大，所以我们把输出重定向到文件了。
3. 为了方便地验证输出结果的正确性，我们拼接了一段js代码，结构：`let fac = (v) => v > 0 ? v * fac(v - 1) : 1, { sqrt } = Math;\n[].every((v) => v === 6);`。把代码直接复制到浏览器控制台，执行结果为true即符合预期。

下面我给出两版代码，`v2`相比于`v1`只多了上述一元运算符实现点的“2”，但代码量却达到了两倍。

执行结果：`8 8 8`没有找到答案，其他的都找到了不少答案。不过如果允许构造一个集合的话，就有一个比较离谱的答案：`|{ 8, 8, 8 }|! = 6`。

`v1`

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
// Copyright 2023 hans7

const int N = 3, M = 11;
bool vis[N];
int p3[N + 1];
LL fac[M], a[N];
string ans[N];
set<string> ansSet;

void dbg() { puts(""); }
template <typename T, typename... R>
void dbg(const T &f, const R &...r) {
  cout << f << " ";
  dbg(r...);
}

bool powTooLarge(LL x, LL y) {
  if (y >= 63) return x >= 2;
  return y * log(x) >= 43.66827237527655;
}

bool isPerfectSquare(LL v) {
  LL root = sqrt(v);
  return root * root == v;
}

bool dfs(int dep) {
  if (dep + 1 == N) {
    for (int i = 0; i < N; i++) {
      if (!vis[i]) {
        if (a[i] == 6) {
          ansSet.insert(ans[i]);
        }
        return a[i] == 6;
      }
    }
    return false;
  }
  bool fl = false;
  for (int i = 0; i < N; i++) {
    if (vis[i]) continue;
    for (int j = i + 1; j < N; j++) {
      if (vis[j]) continue;
      vis[j] = true;
      LL x = a[i], y = a[j];
      string tmpAnsI = ans[i], tmpAnsJ = ans[j];

      if (!powTooLarge(x, y)) {
        a[i] = round(pow(x, y));
        ans[i] = "(" + tmpAnsI + ") ** (" + tmpAnsJ + ")";
        if (dfs(dep + 1)) fl = true;
      }
      if (!powTooLarge(y, x)) {
        a[i] = round(pow(y, x));
        ans[i] = "(" + tmpAnsJ + ") ** (" + tmpAnsI + ")";
        if (dfs(dep + 1)) fl = true;
      }

      if (y && x % y == 0) {
        a[i] = x / y;
        ans[i] = "(" + tmpAnsI + ") / (" + tmpAnsJ + ")";
        if (dfs(dep + 1)) fl = true;
      }
      if (x && y % x == 0) {
        a[i] = y / x;
        ans[i] = "(" + tmpAnsJ + ") / (" + tmpAnsI + ")";
        if (dfs(dep + 1)) fl = true;
      }

      a[i] = x * y;
      ans[i] = "(" + tmpAnsI + ") * (" + tmpAnsJ + ")";
      if (dfs(dep + 1)) fl = true;

      if (y) {
        a[i] = x % y;
        ans[i] = "(" + tmpAnsI + ") % (" + tmpAnsJ + ")";
        if (dfs(dep + 1)) fl = true;
      }
      if (x) {
        a[i] = y % x;
        ans[i] = "(" + tmpAnsJ + ") % (" + tmpAnsI + ")";
        if (dfs(dep + 1)) fl = true;
      }

      a[i] = x + y;
      ans[i] = "(" + tmpAnsI + ") + (" + tmpAnsJ + ")";
      if (dfs(dep + 1)) fl = true;

      a[i] = x - y;
      ans[i] = "(" + tmpAnsI + ") - (" + tmpAnsJ + ")";
      if (dfs(dep + 1)) fl = true;
      a[i] = y - x;
      ans[i] = "(" + tmpAnsJ + ") - (" + tmpAnsI + ")";
      if (dfs(dep + 1)) fl = true;

      a[i] = x << y;
      ans[i] = "(" + tmpAnsI + ") << (" + tmpAnsJ + ")";
      if (dfs(dep + 1)) fl = true;
      a[i] = y << x;
      ans[i] = "(" + tmpAnsJ + ") << (" + tmpAnsI + ")";
      if (dfs(dep + 1)) fl = true;

      a[i] = x >> y;
      ans[i] = "(" + tmpAnsI + ") >> (" + tmpAnsJ + ")";
      if (dfs(dep + 1)) fl = true;
      a[i] = y >> x;
      ans[i] = "(" + tmpAnsJ + ") >> (" + tmpAnsI + ")";
      if (dfs(dep + 1)) fl = true;

      a[i] = x & y;
      ans[i] = "(" + tmpAnsI + ") & (" + tmpAnsJ + ")";
      if (dfs(dep + 1)) fl = true;

      a[i] = x | y;
      ans[i] = "(" + tmpAnsI + ") | (" + tmpAnsJ + ")";
      if (dfs(dep + 1)) fl = true;

      a[i] = x ^ y;
      ans[i] = "(" + tmpAnsI + ") ^ (" + tmpAnsJ + ")";
      if (dfs(dep + 1)) fl = true;

      a[i] = x;
      ans[i] = tmpAnsI;
      vis[j] = false;
    }
  }
  return fl;
}

int main(int, char **) {
  fstream file;
  file.open("apple_interview_24point_similar-v1.txt", ios::out);
  streambuf *stream_buffer_out = cout.rdbuf();
  cout.rdbuf(file.rdbuf());
  for (int i = 0; i <= N; i++) p3[i] = i ? p3[i - 1] * 3 : 1;
  for (int i = 0; i < M; i++) fac[i] = i ? fac[i - 1] * i : 1;
  for (int i = 0; i < M; i++) {
    ansSet.clear();
    bool hasAns = false;
    for (int S = 0; S < p3[N]; S++) {
      for (int j = 0; j < N; j++) {
        int v = 0;
        string strV;
        int sVal = S / p3[j] % 3;
        if (sVal == 1 && isPerfectSquare(i)) {
          v = sqrt(i);
          strV = "sqrt(" + to_string(i) + ")";
        } else if (sVal == 2) {
          v = fac[i];
          strV = "fac(" + to_string(i) + ")";
        } else {
          v = i;
          strV = to_string(i);
        }
        a[j] = v;
        ans[j] = strV;
      }
      hasAns |= dfs(0);
    }
    cout << i << " " << hasAns << endl;
    cout << "ansSet.size() = " << ansSet.size() << endl;
    string jsCode =
        "let fac = (v) => v > 0 ? v * fac(v - 1) : 1, { sqrt } = Math;\n[";
    for (auto v : ansSet) {
      jsCode += v + ", ";
    }
    jsCode += "].every((v) => v === 6);";
    cout << jsCode << endl;
  }
  cout.rdbuf(stream_buffer_out);
  file.close();
  return 0;
}
```

`v2`代码过长，在此不贴出，[传送门](https://github.com/Hans774882968/apple-interview-24point-similar/blob/main/apple_interview_24point_similar-v2.cpp)

