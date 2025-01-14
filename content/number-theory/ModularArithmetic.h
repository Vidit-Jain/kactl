/**
 * Author: Kishore Kumar
 * Date: 2023-03-08
 * License: CC0
 * Source: folklore
 * Description: inv() works for any coprime mod. If mod is prime, can make it faster by using fermats. 
 */
#pragma once

template<const int mod>
struct mint {
	constexpr mint(int x = 0) : val((x % mod + mod) % mod) {}
	mint& operator+=(const mint &b) { val += b.val; val -= mod * (val >= mod); return *this; }
	mint& operator-=(const mint &b) { val -= b.val; val += mod * (val < 0); return *this; }
	mint& operator*=(const mint &b) { val = 1ll * val * b.val % mod; return *this; }
	mint& operator/=(const mint &b) { return *this *= b.inv(); }
	mint inv() const {
		int x = 1, y = 0, t;
		for(int a=val, b=mod; b; swap(a, b), swap(x, y))
			t = a/b, a -= t * b, x -= t * y;
		return mint(x);
	}
	mint pow(int b) const {
		mint a = *this, res(1);
		for(; b; a *= a, b /= 2)  if(b&1) res *= a;
		return res;
	}
	friend mint operator+(const mint &a, const mint &b) {return mint(a) += b;}
	friend mint operator-(const mint &a, const mint &b) {return mint(a) -= b;}
	friend mint operator*(const mint &a, const mint &b) {return mint(a) *= b;}
	friend mint operator/(const mint &a, const mint &b) {return mint(a) /= b;}
	friend bool operator==(const mint &a, const mint &b) {return a.val == b.val;}
	friend bool operator!=(const mint &a, const mint &b) {return a.val != b.val;}
	friend bool operator<(const mint &a, const mint &b) {return a.val < b.val;}
	friend ostream& operator<<(ostream &os, const mint &a) {return os << a.val;}
	int val;
};
using Mint = mint<MOD>;
