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
        LL originalTmpAI = a[i];
        if (0 <= originalTmpAI && originalTmpAI < M) {
          a[i] = fac[originalTmpAI];
          ans[i] = "fac((" + tmpAnsI + ") ** (" + tmpAnsJ + "))";
          if (dfs(dep + 1)) fl = true;
        }
        if (isPerfectSquare(originalTmpAI)) {
          a[i] = sqrt(originalTmpAI);
          ans[i] = "sqrt((" + tmpAnsI + ") ** (" + tmpAnsJ + "))";
          if (dfs(dep + 1)) fl = true;
        }
      }
      if (!powTooLarge(y, x)) {
        a[i] = round(pow(y, x));
        ans[i] = "(" + tmpAnsJ + ") ** (" + tmpAnsI + ")";
        if (dfs(dep + 1)) fl = true;
        LL originalTmpAI = a[i];
        if (0 <= originalTmpAI && originalTmpAI < M) {
          a[i] = fac[originalTmpAI];
          ans[i] = "fac((" + tmpAnsJ + ") ** (" + tmpAnsI + "))";
          if (dfs(dep + 1)) fl = true;
        }
        if (isPerfectSquare(originalTmpAI)) {
          a[i] = sqrt(originalTmpAI);
          ans[i] = "sqrt((" + tmpAnsJ + ") ** (" + tmpAnsI + "))";
          if (dfs(dep + 1)) fl = true;
        }
      }

      if (y && x % y == 0) {
        a[i] = x / y;
        ans[i] = "(" + tmpAnsI + ") / (" + tmpAnsJ + ")";
        if (dfs(dep + 1)) fl = true;
        LL originalTmpAI = a[i];
        if (0 <= originalTmpAI && originalTmpAI < M) {
          a[i] = fac[originalTmpAI];
          ans[i] = "fac((" + tmpAnsI + ") / (" + tmpAnsJ + "))";
          if (dfs(dep + 1)) fl = true;
        }
        if (isPerfectSquare(originalTmpAI)) {
          a[i] = sqrt(originalTmpAI);
          ans[i] = "sqrt((" + tmpAnsI + ") / (" + tmpAnsJ + "))";
          if (dfs(dep + 1)) fl = true;
        }
      }
      if (x && y % x == 0) {
        a[i] = y / x;
        ans[i] = "(" + tmpAnsJ + ") / (" + tmpAnsI + ")";
        if (dfs(dep + 1)) fl = true;
        LL originalTmpAI = a[i];
        if (0 <= originalTmpAI && originalTmpAI < M) {
          a[i] = fac[originalTmpAI];
          ans[i] = "fac((" + tmpAnsJ + ") / (" + tmpAnsI + "))";
          if (dfs(dep + 1)) fl = true;
        }
        if (isPerfectSquare(originalTmpAI)) {
          a[i] = sqrt(originalTmpAI);
          ans[i] = "sqrt((" + tmpAnsJ + ") / (" + tmpAnsI + "))";
          if (dfs(dep + 1)) fl = true;
        }
      }

      LL originalTmpAI = a[i];
      a[i] = x * y;
      ans[i] = "(" + tmpAnsI + ") * (" + tmpAnsJ + ")";
      if (dfs(dep + 1)) fl = true;
      originalTmpAI = a[i];
      if (0 <= originalTmpAI && originalTmpAI < M) {
        a[i] = fac[originalTmpAI];
        ans[i] = "fac((" + tmpAnsI + ") * (" + tmpAnsJ + "))";
        if (dfs(dep + 1)) fl = true;
      }
      if (isPerfectSquare(originalTmpAI)) {
        a[i] = sqrt(originalTmpAI);
        ans[i] = "sqrt((" + tmpAnsI + ") * (" + tmpAnsJ + "))";
        if (dfs(dep + 1)) fl = true;
      }

      if (y) {
        a[i] = x % y;
        ans[i] = "(" + tmpAnsI + ") % (" + tmpAnsJ + ")";
        if (dfs(dep + 1)) fl = true;
        LL originalTmpAI = a[i];
        if (0 <= originalTmpAI && originalTmpAI < M) {
          a[i] = fac[originalTmpAI];
          ans[i] = "fac((" + tmpAnsI + ") % (" + tmpAnsJ + "))";
          if (dfs(dep + 1)) fl = true;
        }
        if (isPerfectSquare(originalTmpAI)) {
          a[i] = sqrt(originalTmpAI);
          ans[i] = "sqrt((" + tmpAnsI + ") % (" + tmpAnsJ + "))";
          if (dfs(dep + 1)) fl = true;
        }
      }
      if (x) {
        a[i] = y % x;
        ans[i] = "(" + tmpAnsJ + ") % (" + tmpAnsI + ")";
        if (dfs(dep + 1)) fl = true;
        LL originalTmpAI = a[i];
        if (0 <= originalTmpAI && originalTmpAI < M) {
          a[i] = fac[originalTmpAI];
          ans[i] = "fac((" + tmpAnsJ + ") % (" + tmpAnsI + "))";
          if (dfs(dep + 1)) fl = true;
        }
        if (isPerfectSquare(originalTmpAI)) {
          a[i] = sqrt(originalTmpAI);
          ans[i] = "sqrt((" + tmpAnsJ + ") % (" + tmpAnsI + "))";
          if (dfs(dep + 1)) fl = true;
        }
      }

      a[i] = x + y;
      ans[i] = "(" + tmpAnsI + ") + (" + tmpAnsJ + ")";
      if (dfs(dep + 1)) fl = true;
      originalTmpAI = a[i];
      if (0 <= originalTmpAI && originalTmpAI < M) {
        a[i] = fac[originalTmpAI];
        ans[i] = "fac((" + tmpAnsI + ") + (" + tmpAnsJ + "))";
        if (dfs(dep + 1)) fl = true;
      }
      if (isPerfectSquare(originalTmpAI)) {
        a[i] = sqrt(originalTmpAI);
        ans[i] = "sqrt((" + tmpAnsI + ") + (" + tmpAnsJ + "))";
        if (dfs(dep + 1)) fl = true;
      }

      a[i] = x - y;
      ans[i] = "(" + tmpAnsI + ") - (" + tmpAnsJ + ")";
      if (dfs(dep + 1)) fl = true;
      originalTmpAI = a[i];
      if (0 <= originalTmpAI && originalTmpAI < M) {
        a[i] = fac[originalTmpAI];
        ans[i] = "fac((" + tmpAnsI + ") - (" + tmpAnsJ + "))";
        if (dfs(dep + 1)) fl = true;
      }
      if (isPerfectSquare(originalTmpAI)) {
        a[i] = sqrt(originalTmpAI);
        ans[i] = "sqrt((" + tmpAnsI + ") - (" + tmpAnsJ + "))";
        if (dfs(dep + 1)) fl = true;
      }
      a[i] = y - x;
      ans[i] = "(" + tmpAnsJ + ") - (" + tmpAnsI + ")";
      if (dfs(dep + 1)) fl = true;
      originalTmpAI = a[i];
      if (0 <= originalTmpAI && originalTmpAI < M) {
        a[i] = fac[originalTmpAI];
        ans[i] = "fac((" + tmpAnsJ + ") - (" + tmpAnsI + "))";
        if (dfs(dep + 1)) fl = true;
      }
      if (isPerfectSquare(originalTmpAI)) {
        a[i] = sqrt(originalTmpAI);
        ans[i] = "sqrt((" + tmpAnsJ + ") - (" + tmpAnsI + "))";
        if (dfs(dep + 1)) fl = true;
      }

      a[i] = x << y;
      ans[i] = "(" + tmpAnsI + ") << (" + tmpAnsJ + ")";
      if (dfs(dep + 1)) fl = true;
      originalTmpAI = a[i];
      if (0 <= originalTmpAI && originalTmpAI < M) {
        a[i] = fac[originalTmpAI];
        ans[i] = "fac((" + tmpAnsI + ") << (" + tmpAnsJ + "))";
        if (dfs(dep + 1)) fl = true;
      }
      if (isPerfectSquare(originalTmpAI)) {
        a[i] = sqrt(originalTmpAI);
        ans[i] = "sqrt((" + tmpAnsI + ") << (" + tmpAnsJ + "))";
        if (dfs(dep + 1)) fl = true;
      }
      a[i] = y << x;
      ans[i] = "(" + tmpAnsJ + ") << (" + tmpAnsI + ")";
      if (dfs(dep + 1)) fl = true;
      originalTmpAI = a[i];
      if (0 <= originalTmpAI && originalTmpAI < M) {
        a[i] = fac[originalTmpAI];
        ans[i] = "fac((" + tmpAnsJ + ") << (" + tmpAnsI + "))";
        if (dfs(dep + 1)) fl = true;
      }
      if (isPerfectSquare(originalTmpAI)) {
        a[i] = sqrt(originalTmpAI);
        ans[i] = "sqrt((" + tmpAnsJ + ") << (" + tmpAnsI + "))";
        if (dfs(dep + 1)) fl = true;
      }

      a[i] = x >> y;
      ans[i] = "(" + tmpAnsI + ") >> (" + tmpAnsJ + ")";
      if (dfs(dep + 1)) fl = true;
      originalTmpAI = a[i];
      if (0 <= originalTmpAI && originalTmpAI < M) {
        a[i] = fac[originalTmpAI];
        ans[i] = "fac((" + tmpAnsI + ") >> (" + tmpAnsJ + "))";
        if (dfs(dep + 1)) fl = true;
      }
      if (isPerfectSquare(originalTmpAI)) {
        a[i] = sqrt(originalTmpAI);
        ans[i] = "sqrt((" + tmpAnsI + ") >> (" + tmpAnsJ + "))";
        if (dfs(dep + 1)) fl = true;
      }
      a[i] = y >> x;
      ans[i] = "(" + tmpAnsJ + ") >> (" + tmpAnsI + ")";
      if (dfs(dep + 1)) fl = true;
      originalTmpAI = a[i];
      if (0 <= originalTmpAI && originalTmpAI < M) {
        a[i] = fac[originalTmpAI];
        ans[i] = "fac((" + tmpAnsJ + ") >> (" + tmpAnsI + "))";
        if (dfs(dep + 1)) fl = true;
      }
      if (isPerfectSquare(originalTmpAI)) {
        a[i] = sqrt(originalTmpAI);
        ans[i] = "sqrt((" + tmpAnsJ + ") >> (" + tmpAnsI + "))";
        if (dfs(dep + 1)) fl = true;
      }

      a[i] = x & y;
      ans[i] = "(" + tmpAnsI + ") & (" + tmpAnsJ + ")";
      if (dfs(dep + 1)) fl = true;
      originalTmpAI = a[i];
      if (0 <= originalTmpAI && originalTmpAI < M) {
        a[i] = fac[originalTmpAI];
        ans[i] = "fac((" + tmpAnsI + ") & (" + tmpAnsJ + "))";
        if (dfs(dep + 1)) fl = true;
      }
      if (isPerfectSquare(originalTmpAI)) {
        a[i] = sqrt(originalTmpAI);
        ans[i] = "sqrt((" + tmpAnsI + ") & (" + tmpAnsJ + "))";
        if (dfs(dep + 1)) fl = true;
      }

      a[i] = x | y;
      ans[i] = "(" + tmpAnsI + ") | (" + tmpAnsJ + ")";
      if (dfs(dep + 1)) fl = true;
      originalTmpAI = a[i];
      if (0 <= originalTmpAI && originalTmpAI < M) {
        a[i] = fac[originalTmpAI];
        ans[i] = "fac((" + tmpAnsI + ") | (" + tmpAnsJ + "))";
        if (dfs(dep + 1)) fl = true;
      }
      if (isPerfectSquare(originalTmpAI)) {
        a[i] = sqrt(originalTmpAI);
        ans[i] = "sqrt((" + tmpAnsI + ") | (" + tmpAnsJ + "))";
        if (dfs(dep + 1)) fl = true;
      }

      a[i] = x ^ y;
      ans[i] = "(" + tmpAnsI + ") ^ (" + tmpAnsJ + ")";
      if (dfs(dep + 1)) fl = true;
      originalTmpAI = a[i];
      if (0 <= originalTmpAI && originalTmpAI < M) {
        a[i] = fac[originalTmpAI];
        ans[i] = "fac((" + tmpAnsI + ") ^ (" + tmpAnsJ + "))";
        if (dfs(dep + 1)) fl = true;
      }
      if (isPerfectSquare(originalTmpAI)) {
        a[i] = sqrt(originalTmpAI);
        ans[i] = "sqrt((" + tmpAnsI + ") ^ (" + tmpAnsJ + "))";
        if (dfs(dep + 1)) fl = true;
      }

      a[i] = x;
      ans[i] = tmpAnsI;
      vis[j] = false;
    }
  }
  return fl;
}

int main(int, char **) {
  fstream file;
  file.open("apple_interview_24point_similar-v2.txt", ios::out);
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
