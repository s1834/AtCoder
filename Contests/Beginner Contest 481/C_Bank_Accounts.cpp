#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    map<string, int> mp;
    int id = 1;
    vector<int> ans;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if(mp.find(s) != mp.end()) ans.push_back(mp[s]);
        else {
            mp[s] = id;
            ans.push_back(id);
            id++;
        }
    }
    
    for(auto &x : ans) cout << x << endl;
    
    return 0;
}

/*
Approach: Map + Sequential ID Assignment

Intuition:
----------
Each pumpkin has a name, and every unique name must receive an ID.
The first time a name appears, we assign it the next available
positive integer. If the same name appears again, we reuse its
previously assigned ID.

Since names are processed in the order they appear, assigning IDs
using an increasing counter guarantees that every new account
receives the smallest positive integer not used previously.

1. Initialize the Map
---------------------
map<string, int> mp;

The map stores:
- Key: pumpkin name.
- Value: ID assigned to that name.

Initially, the map is empty because no accounts have been opened.

2. Initialize the ID Counter
----------------------------
int id = 1;

The variable id represents the next available ID.

Every time a new name appears, we assign this ID and increment it.
Because IDs are assigned consecutively starting from 1, the next
ID is always the smallest positive integer not yet used.

3. Process Each Event
---------------------
for(int i = 0; i < n; i++)

Read the pumpkin's name into string s.

Case 1: The Name Already Exists
-------------------------------
if(mp.find(s) != mp.end())

The find() function checks whether s exists in the map.

If it exists, the pumpkin already has an account. Retrieve its ID:

ans.push_back(mp[s]);

No new account is created, and id remains unchanged.

Case 2: The Name Is New
-----------------------
else {
    mp[s] = id;
    ans.push_back(id);
    id++;
}

Since the name does not exist in the map:
- Assign the current ID to the name.
- Store that ID in the answer vector.
- Increment id to prepare for the next new name.

This ensures that repeated names always receive the same ID.

4. Store and Print the Answers
------------------------------
vector<int> ans;

The vector stores the ID corresponding to every event in input order.

After processing all events:

for(auto &x : ans) cout << x << endl;

Print each assigned or previously existing ID on a separate line.

5. Example Walkthrough
----------------------
Input:
n = 8
pumpkin hobak pompoen hobak pumpkin boga boga hobak

Initially:
mp = {}
id = 1

Event 1: pumpkin
- New name; assign ID 1.
- mp["pumpkin"] = 1
- id = 2
- ans = [1]

Event 2: hobak
- New name; assign ID 2.
- mp["hobak"] = 2
- id = 3
- ans = [1, 2]

Event 3: pompoen
- New name; assign ID 3.
- mp["pompoen"] = 3
- id = 4
- ans = [1, 2, 3]

Event 4: hobak
- Name already exists.
- Reuse ID 2.
- ans = [1, 2, 3, 2]

Event 5: pumpkin
- Name already exists.
- Reuse ID 1.
- ans = [1, 2, 3, 2, 1]

Event 6: boga
- New name; assign ID 4.
- id = 5
- ans = [1, 2, 3, 2, 1, 4]

Event 7: boga
- Name already exists.
- Reuse ID 4.
- ans = [1, 2, 3, 2, 1, 4, 4]

Event 8: hobak
- Name already exists.
- Reuse ID 2.

Final Output:
1
2
3
2
1
4
4
2

6. Why This Works
-----------------
Every unique name receives an ID exactly once, when it first appears.
The counter increases only when a new account is created.

Therefore:
- Different names receive different IDs.
- Repeated names always reuse their original IDs.
- New IDs are assigned in increasing order, so each is the smallest
  positive integer that has not already been used.

Complexity Analysis:
--------------------
Let n be the number of events and L be the maximum name length.

Time Complexity: O(n * L * log n)
- Each map lookup or insertion takes O(log n) comparisons.
- Comparing strings can take O(L) time.
- Processing all n events gives O(n * L * log n).

Space Complexity: O(n * L)
- The map stores at most n unique names.
- The answer vector stores n IDs.

Core Idea:
----------
Use a map to remember the ID assigned to each unique name. Assign
the next consecutive ID to a new name and reuse the stored ID whenever
that name appears again.
*/