#include<bits/stdc++.h>
using namespace std;

void match(unordered_map<string, int>& votes, string ballot) {
    int n = ballot.size();
    int count = 0;
    string candidate = "";

    for (int i = 0; i < n; i++) {
        char curr = ballot[i];
        for (char j = 'a'; j <= 'z'; j++) {
            ballot[i] = j;
            if (votes.find(ballot) != votes.end()) {
                count++;
                candidate = ballot;
            }
        }

        ballot[i] = curr;
    }

    if (count == 1) votes[candidate]++;
    
    return;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<string> candidates(n);
    unordered_map<string, int> votes;
    for(int i = 0; i < n; i++) {
        cin >> candidates[i];
        votes[candidates[i]] = 0;
    }
    
    vector<string> ballots(m);
    for(int i = 0; i < m; i++) cin >> ballots[i]; 
    
    for(int i = 0; i < m; i++) {
        if(votes.find(ballots[i]) != votes.end()) votes[ballots[i]]++;
        else match(votes, ballots[i]);
    }
    
    for(auto &x : candidates) cout << votes[x] << endl;
    
    return 0;
}

/*
    Approach: Hash Map + Brute Force Character Replacement

    The goal is to determine how many votes each candidate receives.

    For every ballot T:
        1. If T exactly matches a candidate's name, that candidate
           receives one vote.
        2. Otherwise, if exactly one candidate's name can be obtained
           by changing exactly one character of T, that candidate
           receives one vote.
        3. If zero or multiple candidates match after one character
           change, the ballot is invalid and nobody receives a vote.

    The solution uses an unordered_map to store candidate names and
    their vote counts. For ballots without an exact match, the helper
    function `match()` tries replacing each character with every
    lowercase English letter.

    ------------------------------------------------------------
    Key Observation
    ------------------------------------------------------------

    Two strings can match after changing exactly one character only
    if they have the same length and differ at exactly one position.

    For example:

        Candidate: "kato"
        Ballot:    "kano"

    Comparing character by character:

        k == k
        a == a
        t != n
        o == o

    Only one position differs, so "kato" can be obtained by changing
    one character of "kano".

    However:

        Candidate: "sato"
        Ballot:    "kano"

    Comparing the strings:

        s != k
        a == a
        t != n
        o == o

    Two positions differ, so this candidate cannot receive the vote
    through a one-character replacement.

    Importantly, the problem requires EXACTLY ONE matching candidate
    for the replacement case. If multiple candidates can be obtained
    by changing one character, the ballot is invalid.

    ------------------------------------------------------------
    Step 1: Define the match() helper function
    ------------------------------------------------------------

        void match(unordered_map<string, int>& votes, string ballot)

    The helper function handles ballots that do not exactly match
    any candidate's name.

    Parameters:

        votes:
            Maps each candidate's name to their current vote count.

        ballot:
            The ballot string being checked.

    The map is passed by reference so that when a candidate receives
    a vote, the updated count is reflected in `main()`.

    The ballot is passed by value, so modifying its characters inside
    `match()` does not modify the original string stored in `ballots`.

    ------------------------------------------------------------
    Step 2: Initialize the matching variables
    ------------------------------------------------------------

        int n = ballot.size();
        int count = 0;
        string candidate = "";

    `n` stores the length of the ballot.

    `count` tracks the number of candidate matches discovered by
    trying character replacements.

    `candidate` stores the name of the most recently matched candidate.

    The final decision depends on `count`:

        count == 0:
            No candidate matches after one character replacement.

        count == 1:
            Exactly one candidate matches, so that candidate receives
            one vote.

        count > 1:
            Multiple matches exist, so the ballot is invalid.

    Since candidate names are distinct, every successful replacement
    that matches a name identifies a distinct candidate.

    ------------------------------------------------------------
    Step 3: Choose a character position
    ------------------------------------------------------------

        for (int i = 0; i < n; i++) {
            char curr = ballot[i];

    The outer loop visits every character position of the ballot.

    At each position `i`, we save the original character:

        char curr = ballot[i];

    This is necessary because the algorithm temporarily replaces
    the character and must restore it before moving to the next
    position.

    Example:

        ballot = "aoki"

    Initially, the algorithm considers:

        i = 0 -> 'a'
        i = 1 -> 'o'
        i = 2 -> 'k'
        i = 3 -> 'i'

    Each position is checked independently to find every candidate
    that differs from the ballot at exactly that position.

    ------------------------------------------------------------
    Step 4: Try every lowercase English letter
    ------------------------------------------------------------

        for (char j = 'a'; j <= 'z'; j++) {
            ballot[i] = j;

    For the current position, the inner loop tries all 26 lowercase
    English letters.

    For example, if:

        ballot = "aoki"
        i = 1

    The algorithm tries strings such as:

        "aaki"
        "abki"
        "acki"
        ...
        "aoki"
        ...
        "azki"

    Every candidate string is generated by modifying only position
    `i`, while leaving all other positions unchanged.

    Therefore, if a generated string matches a candidate's name,
    that candidate's name differs from the original ballot at at
    most one position.

    ------------------------------------------------------------
    Step 5: Check whether the generated string is a candidate
    ------------------------------------------------------------

        if (votes.find(ballot) != votes.end()) {
            count++;
            candidate = ballot;
        }

    The unordered_map `votes` contains every candidate's name.

    Expression:

        votes.find(ballot) != votes.end()

    checks whether the currently generated string exists as a
    candidate's name in the map.

    If it exists:

        count++;

    We have found another matching candidate.

        candidate = ballot;

    We store that candidate's name so that it can receive a vote
    if it turns out to be the unique match.

    Notice that the loop tries every letter, including the original
    character at position `i`.

    This means the original ballot can be counted as a match again
    if it is a candidate's name. However, `main()` calls `match()`
    only when the ballot does NOT exactly match a candidate.

    Therefore, for the ballots passed to `match()`, the original
    string cannot match any candidate, and this does not introduce
    an exact-match duplicate in the replacement case.

    ------------------------------------------------------------
    Step 6: Restore the original character
    ------------------------------------------------------------

        ballot[i] = curr;

    After trying all 26 letters at position `i`, we restore the
    original character.

    This is essential because the next iteration must modify a
    different position of the original ballot, not a string left
    over from the previous set of replacements.

    For example:

        Original ballot = "aoki"

    After checking position 0, the string must return to "aoki"
    before checking position 1.

    Otherwise, modifications from earlier positions could remain
    in the string, causing multiple characters to differ from the
    original ballot.

    Restoring the character ensures that each trial changes only
    one position.

    ------------------------------------------------------------
    Step 7: Award a vote only for exactly one match
    ------------------------------------------------------------

        if (count == 1) votes[candidate]++;

    After all positions and all lowercase letters have been checked,
    `count` contains the total number of matching replacement strings
    that correspond to candidate names.

    If exactly one match exists, the stored candidate receives one
    vote.

    If `count` is zero or greater than one, no vote is awarded.

    This correctly implements the problem's rule that a replacement
    ballot is valid only when exactly one candidate can be obtained
    by changing one character.

    ------------------------------------------------------------
    Step 8: Read candidates and initialize their vote counts
    ------------------------------------------------------------

        int n, m;
        cin >> n >> m;

        vector<string> candidates(n);
        unordered_map<string, int> votes;

        for(int i = 0; i < n; i++) {
            cin >> candidates[i];
            votes[candidates[i]] = 0;
        }

    `n` is the number of candidates, and `m` is the number of ballots.

    The vector `candidates` stores candidate names in their original
    input order. This order is important because the output must
    contain one vote count per candidate in that same order.

    The map is initialized with every candidate name and a vote
    count of zero.

    For example:

        candidates = ["aoki", "sato", "kato"]

        votes:
            "aoki" -> 0
            "sato" -> 0
            "kato" -> 0

    The unordered_map provides average O(1) lookup for checking
    candidate names.

    ------------------------------------------------------------
    Step 9: Read all ballots
    ------------------------------------------------------------

        vector<string> ballots(m);
        for(int i = 0; i < m; i++) cin >> ballots[i];

    The vector `ballots` stores all M ballot strings.

    The solution reads them first and processes them afterward.

    ------------------------------------------------------------
    Step 10: Process each ballot
    ------------------------------------------------------------

        for(int i = 0; i < m; i++) {
            if(votes.find(ballots[i]) != votes.end())
                votes[ballots[i]]++;
            else
                match(votes, ballots[i]);
        }

    For each ballot, we first check whether its string exactly matches
    a candidate's name.

    CASE 1: Exact match

        if(votes.find(ballots[i]) != votes.end())

    If the ballot is already a key in `votes`, the candidate's name
    matches the ballot exactly.

    That candidate receives one vote immediately.

    An exact match takes priority over the one-character replacement
    rule, so the helper function is not called.

    CASE 2: No exact match

        else match(votes, ballots[i]);

    If the ballot does not exactly match any candidate, we call
    `match()` to check all possible one-character replacements.

    The helper awards a vote only if exactly one candidate matches.

    This cleanly separates exact matching from replacement matching.

    ------------------------------------------------------------
    Step 11: Print the vote counts
    ------------------------------------------------------------

        for(auto &x : candidates)
            cout << votes[x] << endl;

    We iterate through `candidates`, which preserves the original
    candidate order.

    For each candidate name `x`, we look up its accumulated vote
    count in `votes` and print it on a separate line.

    This ensures that the i-th output line corresponds to the
    i-th candidate in the input.

    ------------------------------------------------------------
    Detailed Example
    ------------------------------------------------------------

    Suppose the candidates are:

        ["a", "b"]

    And the ballots are:

        ["a", "b", "c", "a", "aa"]

    Initially:

        votes["a"] = 0
        votes["b"] = 0

    Ballot "a":

        Exact match with candidate "a".

        votes["a"] = 1

    Ballot "b":

        Exact match with candidate "b".

        votes["b"] = 1

    Ballot "c":

        No exact match.

        Replacing 'c' with 'a' produces candidate "a".
        Replacing 'c' with 'b' produces candidate "b".

        There are two matching candidates, so the ballot is invalid.

        votes["a"] = 1
        votes["b"] = 1

    Ballot "a":

        Exact match with candidate "a".

        votes["a"] = 2

    Ballot "aa":

        Candidate names have length 1, while the ballot has length 2.

        Changing one character cannot change the string's length,
        so neither candidate can match.

        The ballot is invalid.

    Final vote counts:

        Candidate "a" -> 2
        Candidate "b" -> 1

    Output:

        2
        1

    ------------------------------------------------------------
    Why does the algorithm work?
    ------------------------------------------------------------

    Every ballot is processed using the two rules in the required order.

    First, the map lookup checks whether the ballot exactly matches
    a candidate. If it does, exactly that candidate receives a vote.

    Otherwise, `match()` tries every character position and every
    lowercase letter. Because it restores the original character
    after each position, each generated string differs from the
    original ballot at no more than one position.

    Every candidate that differs at exactly one character position
    is found by the corresponding replacement. Since candidate names
    are distinct, each candidate can be matched by only one generated
    string for a ballot that has no exact match.

    Finally, a vote is awarded only when `count == 1`, so ballots
    with no matches or multiple matches do not affect any candidate.

    The final loop prints each candidate's accumulated votes in
    the required input order.

    ------------------------------------------------------------
    Complexity Analysis
    ------------------------------------------------------------

    Let:
        N = number of candidates
        M = number of ballots
        L = maximum string length, where L <= 10

    Building the candidate map:

        O(N * L) expected time

    Processing exact matches:

        O(M * L) expected time for hashing and comparing strings.

    Processing a ballot without an exact match:

        There are L character positions.
        For each position, 26 lowercase letters are tried.
        Each generated string is hashed/looked up in the map.

        O(26 * L * L) expected time per ballot,
        accounting for string hashing/copying and lookup.

    Overall expected time complexity:

        O(N * L + M * 26 * L^2)

    Since L <= 10 and the alphabet size is fixed at 26, this is
    efficient for the given constraints.

    Space Complexity:

        O(N * L + M * L)

    The candidate vector and vote map store N names, while the ballot
    vector stores M strings. The helper also uses a temporary ballot
    copy of length at most L.

    ------------------------------------------------------------
    Core Idea
    ------------------------------------------------------------

    Use a hash map to store each candidate's vote count.

    For every ballot:
        - Award a vote immediately if the name matches exactly.
        - Otherwise, try replacing each character with every lowercase
          letter and count the matching candidate names.
        - Award a vote only if exactly one candidate matches.

    Finally, print the vote count of each candidate in input order.
*/