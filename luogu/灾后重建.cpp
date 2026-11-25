/*
题目:P1119 灾后重建
链接：https://www.luogu.com.cn/problem/P1119#ide
日期：2026-11-25
标签：Floyd、中转点
反思：第一版用的是Floyd模板，没搞懂中转点的意义。按需求选择 按重建完成的时间顺序把村庄序号升序排列，当作中转点就过了
*/


#include <iostream>
#include <algorithm>
using namespace std;
const int N = 210;
const int INF = 0x3f3f3f3f;
int dp[N][N];
int t[N];
int n, m;
signed main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
        for (int j = 0; j < n; j++) {
            if (i == j)dp[i][j] = 0;
            else dp[i][j] = INF;
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        dp[u][v] = min(dp[u][v], w);
        dp[v][u] = min(dp[u][v], w);
    }
    int q; cin >> q;
    int cnt = 0;
    for (int h = 0; h < q; ++h) {
        int x, y, t0; cin >> x >> y >> t0;
        while (cnt < n && t[cnt] <= t0) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dp[i][cnt] != INF && dp[cnt][j] != INF) {
                        dp[i][j] = min(dp[i][j], dp[i][cnt] + dp[cnt][j]);
                    }
                }
            }
            cnt++;
        }
        if (t[x] > t0 || t[y] > t0) { cout << "-1\n"; continue; }
        if (dp[x][y] == INF)cout << "-1\n";
        else cout << dp[x][y] << '\n';
    }
    return 0;
}