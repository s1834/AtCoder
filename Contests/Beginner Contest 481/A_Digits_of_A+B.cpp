#include<bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    
    int sum = a + b;
    int count = 0;
    while(sum) {
        sum /= 10;
        count++;
    }
    
    cout << count << endl;
    
    return 0;
}

/*
Approach: Digit Counting Using Division

Intuition:
----------
We are given two integers a and b. We first calculate their sum,
then count the number of digits in that sum.

1. Calculate the Sum
--------------------
int sum = a + b;

Since both a and b are between 1 and 9, their sum lies between 2 and 18.

2. Count the Digits
-------------------
int count = 0;

while(sum) {
    sum /= 10;
    count++;
}

In each iteration:
- sum /= 10 removes the last digit of sum using integer division.
- count++ increments the number of digits processed.

Example 1:
a = 4, b = 9
sum = 13

Iteration 1:
sum = 13 / 10 = 1
count = 1

Iteration 2:
sum = 1 / 10 = 0
count = 2

The loop stops when sum becomes 0.

Output: 2

Example 2:
a = 7, b = 1
sum = 8

Iteration 1:
sum = 8 / 10 = 0
count = 1

Output: 1

3. Print the Answer
-------------------
cout << count << endl;

The variable count contains the total number of digits in a + b.

Complexity Analysis:
--------------------
Time Complexity: O(log(a + b)), because each iteration removes one
digit. Since a + b <= 18, the loop executes at most two times.

Space Complexity: O(1), because only a constant number of variables
are used.

Core Idea:
----------
Calculate a + b, repeatedly divide the sum by 10 until it becomes 0,
and count how many divisions are performed.
*/