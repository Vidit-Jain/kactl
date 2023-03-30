/**
 * Author: A Kishore Kumar
 * Date: 2023-03-30
 * Source: Wikipedia, https://codeforces.com/blog/entry/3781
 * Description: Dilworth's theorem states that the size of the maximum antichain in a POSET $S$ is equal to the 
 * minimum number of chains needed to partition $S$, where a chain is a subset of $S$ with elements 
 * arranged in ascending order, and a partition is a set of chains where each element occurs in 
 * exactly one chain. An antichain is a subset of $S$ where no two elements are comparable. 
 * $\forall x, y \in A$ we have neither $x \leq y$ nor $y \leq x$. Handle equality case 
 * carefully. We need strict-weak ordering to hold. Can sort by index maybe.
 */
