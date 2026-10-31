#include<bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    
    int count = 0;
    for(auto &ch : s) {
        if(ch == 'o') count++;
    }
    
    if(count % 2 == 0) cout << "even\n";
    else cout << "odd\n";
    
    return 0;
}

/*
Approach: String Traversal + Counting

Intuition:
----------
We are given a string containing only 'o' and '.'.

We need to count the number of occurrences of 'o':
- If the count is odd, print "odd".
- If the count is even, print "even".

The key idea is to traverse the string once, count every 'o',
and use the modulo operator to determine whether the count is even
or odd.

--------------------------------------------------
1. Read the Input
--------------------------------------------------

string s;
cin >> s;

Read the input string from standard input.

--------------------------------------------------
2. Initialize the Counter
--------------------------------------------------

int count = 0;

Maintain a variable count to store the total number of 'o'
characters in the string.

--------------------------------------------------
3. Count Occurrences of 'o'
--------------------------------------------------

for(auto &ch : s) {
    if(ch == 'o') count++;
}

Traverse every character in the string using a range-based for loop.

If the current character is 'o', increment count.

Characters containing '.' are ignored.

After the loop, count represents the total number of 'o' characters.

--------------------------------------------------
4. Check Whether the Count Is Even or Odd
--------------------------------------------------

if(count % 2 == 0)
    cout << "even\n";
else
    cout << "odd\n";

Use the modulo operator (%) to check the parity of count.

- count % 2 == 0 means the count is even.
- count % 2 == 1 means the count is odd.

Print the corresponding result.

--------------------------------------------------
5. Example Walkthrough
--------------------------------------------------

Example 1:
s = "oo.o.o"

Occurrences of 'o' = 4

count = 4

4 % 2 == 0

Output: even

Example 2:
s = "..o....."

Occurrences of 'o' = 1

count = 1

1 % 2 != 0

Output: odd

Example 3:
s = "."

Occurrences of 'o' = 0

count = 0

0 % 2 == 0

Output: even

--------------------------------------------------
6. Complexity Analysis
--------------------------------------------------

Time Complexity: O(n)

We traverse the string exactly once, where n is its length.

Space Complexity: O(1)

Only one counter variable is used, excluding the input string.

Core Idea:
----------
Count the occurrences of 'o' in the string and use count % 2
to determine whether the total is even or odd.
*/