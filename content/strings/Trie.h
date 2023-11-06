/**
 * Author: A Kishore Kumar
 * Date: 2023-05-19
 * Source: Myself
 * ExtDesc: Simple integer pointer based trie. 
 * Status: NOT-TESTED
 */
template<int NX = int(1e6 + 5e5)>
struct Trie {
    int root, lastocc;
    array<array<int, 26>, NX> mem; // use vector if stack storage dies
    void insert(const string &s){
        int curptr = root;
        for(auto &c : s){
            if(!mem[curptr][c - 'a']) mem[curptr][c - 'a'] = ++lastocc;
            curptr = mem[curptr][c - 'a'];
        }
    }
    bool search(const string &s){
        int curptr = root;
        for(auto &c : s)
            if(!mem[curptr][c - 'a']) return false;
            else curptr = mem[curptr][c - 'a'];
        return true;
    }
};
