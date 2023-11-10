/**
 * Author: Vidit Jain
 * Date: 2023-11-10
 * License: CC0
 * Source: Combination of various implementations 
 * ExtDesc: An iterative lazy segment tree implementation. O(\log N).
 * Description: If harsh TL manually inline f, map, compose. Segtree of vector faster than vector of segtree. $\text{f}$ - two elements, $\text{map}$ - element + update, $\text{compose}$ - two updates.
 * Usage: __attribute__((always_inline)) inline
 * Status: Needs testing.
 */

template<class T, class L, class F, class M, class C>
struct LazySegtree {
    signed n;
    vector<T> t; vector<L> l;    
    T id; L l_id;
 
    int bc(int n) { return (n == 1) ? 1 : (1 << (32 - __builtin_clz(n-1))); };
	F f; M map; C compose;

    LazySegtree(const vector<T> &a, T id, L l_id, F f, M map, C compose) : n(bc(sz(a))), id(id), l_id(l_id), t(2*n,id), l(2*n,l_id), f(f), map(map), compose(compose){
        for (int i = 0; i < sz(a); i++) t[i+n] = a[i]; 
        for (int i = n - 1; i >= 1; i--) t[i] = f(t[2*i], t[2*i+1]);
    }
 
    void apply(int v, L upd, int len) {
        map(t[v], upd, len);
        if (v < n) compose(l[v], upd, len);
    }

    void push(int v, int len) {
        apply(2*v, l[v], len/2); apply(2*v+1, l[v], len/2);
        l[v] = l_id;
    }
	template<bool upd>
    T process(int node, int l, int r, int ql, int qr, L v) {
        if (r < ql or qr < l) return id;
        if (ql <= l and r <= qr) {
            if (upd) apply(node, v, r-l+1);
            return t[node];
        }
        int m = (l+r)>>1; 
        push(node, r-l+1);
		auto a = process<upd>(2*node, l, m, ql, qr, v);
		auto b = process<upd>(2*node+1, m+1, r, ql, qr, v);
		return upd ? t[node] = f(t[2 * node], t[2 * node + 1]) : f(a, b);
    }

    void update(int ul, int ur, L v) { process<true>(1, 0, n-1, ul, ur, v);}
    T query(int ql, int qr) { return process<false>(1, 0, n-1, ql, qr, -1);}
};

