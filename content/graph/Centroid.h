/**
 * Author: A Kishore Kumar
 * Date: 2023-12-30
 * Source: https://codeforces.com/blog/entry/114287
 * ExtDesc: Centroid decomposition template. Use lambda f as [&](vvi &adj, int centroid, int subsize, int clevel)
 */

template<typename F>
void decompose(const vvi &adj, const F &f){
    int n = sz(adj);
    vi sub(n, 1), p(n, -1), ord(n), used(n);
    for(int i=0, t=0, v=ord[i]; i < n; v=ord[++i])
        for(auto &to : adj[v]) if(to != p[v]) p[to] = v, ord[++t] = to;
    for(int i=n-1; i > 0; i--) sub[p[ord[i]]] += sub[ord[i]];
    vvi ctree(n);
    function<void(int,int)> dfs = [&](int c, int level){
        int size = sub[c], pr = -1;
        while(exchange(pr, c) != c)
            for(auto &to : adj[c]) if(!used[to] and 2*sub[to] > size)
                sub[c] -= sub[to], sub[to] = size, c = to;
        used[c] = true;
        for(auto &to : adj[c]) if(!used[to]) {
            dfs(to, level+1);
            ctree[c].pb(to); ctree[to].pb(c);
        }
        f(ctree, c, size, level);
    };
    dfs(0, 0);
};
