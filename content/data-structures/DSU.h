/**
 * Author: Kishore Kumar
 * Date: 2022-10-15
 * License: CC0
 * Source: folklore
 * ExtDesc: Disjoint-set data structure. $O(\alpha(N))$
 * Description: dsu[v] holds -size(v) if v is parent, else contains parent id
 */
#pragma once

struct DSU{
	vi dsu;
	int num_comps;
	DSU(int n) : dsu(n, -1), num_comps(n) {}
	int parent(int i){ return dsu[i] < 0 ? i : dsu[i] = parent(dsu[i]); }
	int size(int i) { return -dsu[parent(i)]; }
	int operator[](int i){ return parent(i); }
	void unify(int a, int b){
		a = parent(a), b = parent(b);
		if(dsu[a] > dsu[b]) swap(a, b);
		if(a!=b) dsu[a] += dsu[b], dsu[b] = a, num_comps--;
	}
};

struct RollbackUF {
	vi e; vii st;
	RollbackUF(int n) : e(n, -1) {}
	int size(int x) { return -e[parent(x)]; }
	int parent(int x) { return e[x] < 0 ? x : parent(e[x]); }
	int operator[](int i){ return parent(i); }
	int time() { return sz(st); }
	void rollback(int t) {
		for (int i = time(); i --> t;)
			e[st[i].first] = st[i].second;
		st.resize(t);
	}
	bool join(int a, int b) {
		a = parent(a), b = parent(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		st.pb({a, e[a]}); st.pb({b, e[b]});
		e[a] += e[b]; e[b] = a;
		return true;
	}
};