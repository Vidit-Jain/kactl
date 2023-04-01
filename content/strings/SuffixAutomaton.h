/**
 * Author: Pramod Rao
 * Date: 2022-04-01
 * License: CC0
 * Source: https://cp-algorithms.com/string/suffix-automaton.html
 * ExtDesc: modular suffix automaton. Build online by extend or pass string.
 * Status: NOT-TESTED
 */

template<const int maxLen>
struct SA{
	struct state{
		int len{}, link{};
		map<char, int> next;
	};
	state st[maxLen * 2];
	int z = 1, last = 0;
	SA() { st[0].len = 0, st[0].link = -1; }
	explicit SA(const string &str) {
		st[0].len = 0, st[0].link = -1;
		for (auto &c: str) this->extend(c);
	}
	void extend(char c) {
		int cur = z++;
		st[cur].len = st[last].len + 1;
		int p = last;
		for (; p != -1 && !st[p].next.count(c); p = st[p].link)
			st[p].next[c] = cur;
		if (p == -1) {
			st[cur].link = 0;
		} else {
			int q = st[p].next[c];
			if (st[p].len + 1 == st[q].len) {
				st[cur].link = q;
			} else {
				int clone = z++;
				st[clone] = {st[p].len + 1, st[q].link, st[q].next};
				for (; p != -1 && st[p].next[c] == q; p = st[p].link)
					st[p].next[c] = clone;
				st[q].link = st[cur].link = clone;
			}
		}
		last = cur;
	}
};
