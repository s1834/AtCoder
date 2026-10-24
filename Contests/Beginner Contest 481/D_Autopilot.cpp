#include<bits/stdc++.h>
using namespace std;

int findDistance(vector<vector<int>>& adj, int& n, int s, int t) {
    vector<int> dist(n + 1, INT_MAX); // store minimum distance to reach a planet
    deque<int> dq;
    
    dist[s] = 0; // distance to reach start planet is 0
    dq.push_front(s);
    
    while(!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        
        // visit all adjacent planets from current planet
        for(int v : adj[u]) {
            int cost = (v == adj[u][0]) ? 0 : 1; // if closest planet with minimum number then fuel is 0
            
            // if known cost to reach destination(v) planet is more than cost to reach from current(u) planet
            if(dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                
                // if cost is 0 priortize going through it
                if(cost == 0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }
    
    return (dist[t] == INT_MAX) ? -1 : dist[t]; // if target reachable or not
}

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    
    vector<vector<int>> adj(n + 1);
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }
    
    for(int i = 1; i <= n; i++) sort(adj[i].begin(), adj[i].end()); // sort so we can figure out if cost is 0 or 1
    
    cout << findDistance(adj, n, s, t) << endl;
    
    return 0;
}

/*
Approach: 0-1 BFS + Sorted Adjacency Lists

Intuition:
----------
We are given a directed graph of N planets and M one-way routes.
The spaceship can move from a planet to another directly reachable
planet in two ways:

1. Move to the smallest-numbered directly reachable planet without
   consuming fuel. The cost of this move is 0.
2. Move to any directly reachable planet by consuming 1 unit of fuel.
   The cost of this move is 1.

We need to find the minimum fuel required to travel from S to T.
If T is unreachable, return -1.

Since every edge has a cost of either 0 or 1, we can use 0-1 BFS,
which is a variation of BFS that uses a deque to process lower-cost
paths before higher-cost paths.

--------------------------------------------------
1. Build the Directed Graph
--------------------------------------------------

vector<vector<int>> adj(n + 1);

For every route (a, b), add b to adj[a].

adj[a] stores all planets directly reachable from planet a.

Because routes are one-way, we only add:
adj[a].push_back(b);

We do not add the reverse edge unless it is separately provided
in the input.

The graph uses 1-based planet numbering, so the adjacency list
has size n + 1.

--------------------------------------------------
2. Sort Every Adjacency List
--------------------------------------------------

for(int i = 1; i <= n; i++)
    sort(adj[i].begin(), adj[i].end());

Sorting each adjacency list ensures that the smallest-numbered
reachable planet appears at index 0.

Therefore:
adj[u][0] = smallest-numbered planet directly reachable from u.

This is important because moving to this particular planet costs
zero fuel, while moving to any other directly reachable planet
costs one unit of fuel.

--------------------------------------------------
3. Initialize the Distance Array
--------------------------------------------------

vector<int> dist(n + 1, INT_MAX);

dist[v] stores the minimum fuel currently known to be required
to reach planet v from the starting planet S.

Initially, every planet is considered unreachable, so its distance
is initialized to INT_MAX.

dist[s] = 0;

The spaceship starts at S, so reaching the starting planet requires
zero fuel.

deque<int> dq;
dq.push_front(s);

The deque stores planets whose outgoing edges need to be processed.

We initially insert S at the front because its distance is zero.

--------------------------------------------------
4. Process Planets Using 0-1 BFS
--------------------------------------------------

while(!dq.empty())

Continue processing until there are no more planets in the deque.

int u = dq.front();
dq.pop_front();

Remove the front planet u to examine all its outgoing routes.

For every directly reachable planet:

for(int v : adj[u])

Determine the fuel cost of moving from u to v.

--------------------------------------------------
5. Determine the Edge Cost
--------------------------------------------------

int cost = (v == adj[u][0]) ? 0 : 1;

Because adj[u] is sorted:

- If v == adj[u][0], v is the smallest-numbered reachable planet,
  so the move consumes zero fuel.
- Otherwise, the move consumes one unit of fuel.

For example:
adj[2] = [4, 5]

Moving from planet 2 to planet 4 costs 0.
Moving from planet 2 to planet 5 costs 1.

If a planet has only one outgoing route, that route is necessarily
the zero-cost move.

--------------------------------------------------
6. Relax the Distance
--------------------------------------------------

if(dist[u] + cost < dist[v])

The current path reaches u using dist[u] units of fuel.
Moving from u to v adds cost more units.

Therefore, the candidate distance to v is:

dist[u] + cost

If this is smaller than the previously known distance dist[v],
update the distance:

dist[v] = dist[u] + cost;

This is called relaxation.

It ensures that the algorithm keeps improving the minimum fuel
estimate whenever a cheaper route is discovered.

--------------------------------------------------
7. Update the Deque
--------------------------------------------------

if(cost == 0)
    dq.push_front(v);
else
    dq.push_back(v);

This is the central idea of 0-1 BFS.

Case 1: Zero-cost edge
----------------------
If cost == 0, moving to v does not increase the fuel consumed.

The new distance is equal to dist[u], so v is inserted at the
front of the deque to prioritize processing it.

Case 2: One-cost edge
---------------------
If cost == 1, the distance increases by one.

Insert v at the back of the deque so that zero-cost transitions
can be processed first.

This ordering allows 0-1 BFS to find shortest paths when edge
weights are restricted to 0 and 1.

--------------------------------------------------
8. Return the Answer
--------------------------------------------------

return (dist[t] == INT_MAX) ? -1 : dist[t];

After the deque is exhausted:

- If dist[t] is still INT_MAX, planet T was never reached.
  Return -1.
- Otherwise, return dist[t], the minimum fuel required to reach T.

--------------------------------------------------
9. Example Walkthrough
--------------------------------------------------

Consider Sample Input 1:

N = 7, M = 10
S = 2, T = 1

Routes:
2 -> 5
2 -> 4
4 -> 2
4 -> 3
3 -> 1
3 -> 5
3 -> 6
5 -> 6
6 -> 1
6 -> 7

After sorting the adjacency lists:

adj[2] = [4, 5]
adj[3] = [1, 5, 6]
adj[4] = [2, 3]
adj[5] = [6]
adj[6] = [1, 7]

Start:
dist[2] = 0

Process planet 2:
-----------------
The smallest reachable planet is 4.

2 -> 4 costs 0.
dist[4] = 0

The other route is 2 -> 5, which costs 1.
dist[5] = 1

Planet 4 is added to the front, while planet 5 is added to the back.

Process planet 4:
-----------------
The smallest reachable planet is 2.

4 -> 2 costs 0.
The distance to planet 2 remains 0.

The route 4 -> 3 costs 1.
dist[3] = 1

Process planet 3:
-----------------
Its smallest reachable planet is 1.

3 -> 1 costs 0.
dist[1] = 1

The other routes 3 -> 5 and 3 -> 6 each cost 1.
They cannot improve the already known distance to planet 5,
but planet 6 can be reached with distance 2.

Planet 1 is reachable with fuel consumption 1.

Output:
1

One optimal route is:
2 -> 4 -> 3 -> 1

Fuel consumed:
0 + 1 + 0 = 1

--------------------------------------------------
10. Why 0-1 BFS Works
--------------------------------------------------

Ordinary BFS finds shortest paths efficiently when every edge has
the same cost.

Here, however, edges have different costs: either 0 or 1.

0-1 BFS handles this difference by using a deque:
- Zero-cost transitions go to the front.
- One-cost transitions go to the back.

Whenever a shorter path to a planet is found, its distance is
updated and the planet is inserted into the deque according to
the cost of the transition.

This prioritizes paths with lower fuel consumption and computes
the minimum distance to every reachable planet.

--------------------------------------------------
11. Complexity Analysis
--------------------------------------------------

Let N be the number of planets and M the number of routes.

Sorting:
- Sorting all adjacency lists takes
  O(M log M) time in the general upper bound.

0-1 BFS:
- With standard 0-1 BFS, each edge is relaxed in O(1) time
  when processed, giving O(N + M) time.

Overall Time Complexity:
O(N + M log M)

Space Complexity:
O(N + M)

The adjacency list stores all N planets and M routes.
The distance array and deque require O(N) additional space.

Core Idea:
----------
Sort each adjacency list so its first element is the smallest
reachable planet. Assign that edge cost 0 and all other outgoing
edges cost 1. Then use 0-1 BFS with a deque to calculate the
minimum fuel required to reach T, returning -1 if it is unreachable.
*/