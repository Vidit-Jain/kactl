/**
 * Author: A Kishore Kumar
 * Date: 2023-03-30
 * License: CC0
 * Source: http://rng-58.blogspot.com/2017/02/hashing-and-probability-of-collision.html
 * ExtDesc: Let $G$ be a tree with depth $d$ and $k$ children. The function $P(G)$ is defined 
 * recursively as $P(G) = 1$ if $G$ is a single leaf, otherwise $P(G) = (x_d + P(G_1))(x_d + P(G_2)) 
 * \cdots (x_d + P(G_k))$, where $G_1, G_2, \ldots, G_k$ are the subtrees corresponding to the 
 * children of the root of $G$, and $x_d$ is a variable. Using this definition, we obtain a 
 * multi-variable polynomial over $d$ variables of degree $l$, where $l$ is the number of leaves in 
 * the tree. Evaluating this polynomial for random variables yields a hash function with collision 
 * probability at most $l/\text{MOD}$.
 * Time: $O(nlogn)$
 * Status: Tested on CF
 */

#include "../strings/Hashing.h"

vector<HT> R(MAXN);
void prec(){
	auto rng = std::mt19937(std::random_device()());
	for(int i=0; i < sz(R); i++) R[i] = {rng(), rng()}; //*
}
HT hasher(vector<HT> &h, int d){
	HT ret_hash = mint_ntuple(1);
	for(auto &x : h) ret_hash *= (R[d] + x);
	return ret_hash;
}
auto comp = [&](vvi &adj){
	vector<HT> iso(n);
	function<int(int, int)> dfs = [&](int v, int p){
		vector<HT> c;
		int dep = 0;
		for(auto &to : adj[v]) if(to != p) {
			dep = max(dep, dfs(to, v) + 1);
			c.pb(iso[to]);
		}		 
		return iso[v] = hasher(c, dep), dep;
	};
	return dfs(0, -1), iso;
};
