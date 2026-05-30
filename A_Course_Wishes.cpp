#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    
    vector<int> a(k + 2, 0);
    for (int i = 1; i <= k; ++i) {
        cin >> a[i];
    }
    //// Level k + 1 has an infinite capacity limit
    a[k + 1] = n + 1; 

    vector<int> b(n + 1);
    vector<int> current_count(k + 2, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        current_count[b[i]]++;
    }

    vector<int> operations;
    bool progressed = true;

    while (progressed) {
        progressed = false;
        //? Scan from level k down to 1
        for (int level = k; level >= 1; --level) {
            // TODO: Check if the next level has available capacity
            if (current_count[level] > 0 && current_count[level + 1] < a[level + 1]) {
                // * Find a course currently at this level
                for (int i = 1; i <= n; ++i) {
                    if (b[i] == level) {
                        //! Perform the operation
                        b[i]++;
                        current_count[level]--;
                        current_count[level + 1]++;
                        operations.push_back(i);
                        progressed = true;
                        break; //? Break to re-evaluate from the highest level again
                    }
                }
            }
            if (progressed) break;
        }
    }

    //! Check if all courses successfully reached level k + 1
    if (current_count[k + 1] == n) {
        cout << operations.size() << "\n";
        for (int i = 0; i < operations.size(); ++i) {
            cout << operations[i] << (i == operations.size() - 1 ? "" : " ");
        }
        cout << "\n";
    } else {
        cout << -1 << "\n";
    }
   
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}