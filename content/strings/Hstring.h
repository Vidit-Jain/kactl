/**
 * Author: Kishore Kumar
 * Date: 2023-03-10
 * License: CC0
 * Source: own work
 * Description: Consider memory limit and discard rabin-karp array $h$ if substring hashes 
 * are not required when facing memory limit issues. Intuitive hash, $h[i+1] = h[i] * pp[i] * \cdots$.
 * $h(l, r) = (h[r+1] - h[l]) * ipp[l]$
 * Status: stress-tested
 */

#include <../number-theory/ModularArithmetic.h>
#include "Hashing.h"

template<typename T>
struct Hstring{
	vector<HT> h;
	Hstring() = default;
	Hstring(T &v) : h(sz(v)+1) {
		for(int i=0; i < sz(v); i++) h[i+1] = h[i] * p1 + mint_ntuple(v[i]);
	}
	HT hash(int l, int r){ return h[r+1] - h[l] * p[r-l+1]; }
	HT hash() { return h.back(); }
}; 
