/**
 * Author: A Kishore Kumar
 * Date: 2023-11-07
 * Source: Myself
 * ExtDesc: Keeping this for times when I need to quickly query max set-xor and don't want to modify our trie.
 * Status: Tested once on a CF problem https://codeforces.com/contest/1777/problem/F
 */
template<int NX = int(1e6 + 5e5)>
struct Trie {
    int root, lastocc;
    array<array<int, 2>, NX> mem; // use vector if stack storage dies
    int bit(int s, int i) { return bool(s & (1 << i)); }
    void insert(int s){
        int curptr = root;
        for(int i=30; i >= 0; i--){
            if(!mem[curptr][bit(s, i)]) mem[curptr][bit(s, i)] = ++lastocc;
            curptr = mem[curptr][bit(s, i)];
        }
    }
    bool empty() { return !mem[root][0] and !mem[root][1]; }
    int query(int s){
        int curptr = root, ans = 0;
        for(int i=30; i >= 0; i--)
            if(mem[curptr][bit(s, i) ^ 1]) 
                curptr = mem[curptr][bit(s, i) ^ 1], ans |= (bit(s, i) ^ 1) << i;
            else curptr = mem[curptr][bit(s, i)], ans |= (bit(s, i)) << i;
        return ans;
    }
};
