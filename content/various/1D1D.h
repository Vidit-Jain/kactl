/**
 * Author: Vidit Jain
 * License: CC0
 * Source: https://codeforces.com/contest/319/submission/125522308 
 * ExtDesc: Given $a[i] = \min_{lo(i) \le k < hi(i)}(f(i, k))$ where the (minimal) optimal $k$ increases with $i$, computes $a[i]$ for $i = L..R-1$.
 * Description: Quadrangle Inequality must hold. If \texttt{dp[i] = dp[j] + C[j + 1][i]}, change \texttt{k = \{\{-1, 0\}\}}, remove \texttt{dp[0] = 0}, add condition for \texttt{i == -1} in cost function, start loop in \texttt{solve()} from $0$.
 * Status: tested on https://codeforces.com/contest/319/problem/C 
 */
#pragma once

template<typename T>
struct DP1D {
	int n;
	T id;
	using vt = vector<T>;
	vt dp;
	deque<pii> k = {{0, 1}};
	DP1D(int n, T id):n(n), id(id), dp(n,id) {}
	T C(int i, int j) { return dp[i];}
	T solve() {
		dp[0] = 0;
		rep(i, 1, n) {
			dp[i] = C(k.front().ff, i);
			if (i == n - 1) break;
			k.front().ss++;
			if (sz(k) != 1 && k[0].ss == k[1].ss) k.pop_front();
			while (!k.empty() && C(k.back().ff, k.back().ss) >= C(i, k.back().ss)) 
				k.pop_back();
	 
			if (k.empty()) k.pb({i, i + 1});
			else {
				int low = k.back().ss, high = n;
				while (high > low + 1) {
					int mid = (low + high) >> 1;
					if (C(k.back().ff, mid) >= C(i, mid)) high = mid;
					else low = mid;
				}
				if (high != n) k.pb({i, high});
			}
		}
		return dp[n - 1];
	}
};
