#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    // Helper function to precompute counts of numbers divisible by each unique value in the array
    unordered_map<int, int> precomputeDivisibilityCounts(const vector<int>& arr) {
        unordered_map<int, int> countMap;
        for (int num : arr) {
            for (int i = 1; i * i <= num; ++i) {
                if (num % i == 0) {
                    countMap[i]++;
                    if (i != num / i) {
                        countMap[num / i]++;
                    }
                }
            }
        }
        return countMap;
    }

    vector<int> solveQueries(const vector<int>& arr, const vector<pair<int, int> >& queries) {
        unordered_map<int, int> countMap = precomputeDivisibilityCounts(arr);
        vector<int> ans(queries.size());

        for (size_t i = 0; i < queries.size(); ++i) {
            int l = queries[i].first;
            int r = queries[i].second;

            int cnt0 = countMap[l];
            int cnt1 = countMap[r];

            int cnt = (cnt0 * cnt0) + (cnt1 * cnt1);
            ans[i] = cnt;
        }

        return ans;
    }

public:
    void solve() {
        int t;
        cout << "Enter the number of test cases: ";
        cin >> t;

        while (t--) {
            int n;
            cout << "Enter the number of elements in the array: ";
            cin >> n;

            vector<int> arr(n);
            cout << "Enter the elements of the array: ";
            for (int i = 0; i < n; ++i) {
                cin >> arr[i];
            }

            int q;
            cout << "Enter the number of queries: ";
            cin >> q;

            vector<pair<int, int> > queries(q);
            for (int i = 0; i < q; ++i) {
                cout << "Enter the " << i + 1 << "th query: ";
                cin >> queries[i].first >> queries[i].second;
            }

            vector<int> ans = solveQueries(arr, queries);
            cout << "The answers are: ";
            for (int value : ans) {
                cout << value << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Solution s;
    s.solve();
    return 0;
}
