/**
 * Author: A Kishore Kumar
 * Date: 2022-02-02
 * License: CC0
 * Source: https://codeforces.com/blog/entry/18051
 * ExtDesc: An iterative lazy segment tree implementation. O(\log N).
 * Description: If harsh TL manually inline f, map, compose and process. Segtree of vector faster than vector of segtree.
 * Usage: __attribute__((always_inline)) inline
 * Status: Needs testing.
 */

template<typename T, typename L>
struct LazySegtree {
    signed n;
    vector<T> t; vector<L> l;    
    T id; L l_id;
 
    int bc(int n) { return (n == 1) ? 1 : (1 << (32 - __builtin_clz (n-1))); };
    T f(T a, T b) { return max(a, b); } 
    T map(T v, L val, int len) { return v+val; }
    void compose(L &cl, L &ul, int len){ cl += ul; }

    LazySegtree(const vector<T> &a, T id, L l_id) : n(bc(sz(a))), id(id), l_id(l_id), t(2*n), l(2*n){
        for (int i = 0; i < sz(a); i++) t[i + n] = a[i]; 
        for (int i = n - 1; i >= 1; i--) t[i] = f(t[2 * i], t[2 * i + 1]);
    }
 
    void apply(int v, L upd, int len) {
        t[v] = map(t[v], upd, len);
        if (v < n) compose(l[v], upd, len);
    }

    void push(int v) {
        apply(2*v, l[v], -1); apply(2*v+1, l[v], -1);
        l[v] = l_id;
    }
    T query(int node, int l, int r, int ql, int qr, int upd, int v) {
        if (r < ql or qr < l) return id;
        if (ql <= l and r <= qr) {
            if (upd) apply(node, v, -1);
            return t[node];
        }
        int m = l + (r - l) / 2;
        push(node);
        if (upd) {
            query(2 * node, l, m, ql, qr, upd, v);
            query(2 * node + 1, m + 1, r, ql, qr, upd, v);
            t[node] = f(t[2 * node], t[2 * node + 1]);
            return T{};
        }
        else
            return f(query(2 * node, l, m, ql, qr, upd, v), query(2 * node + 1, m + 1, r, ql, qr, upd, v));
    }

    void update(int ul, int ur, int v) { query(1, 0, n - 1, ul, ur, 1, v);}
    T query(int ql, int qr) { return query(1, 0, n - 1, ql, qr, 0, -1);}
};
