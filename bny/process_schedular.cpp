#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Solution{
public:
    void solve(){
        int t;
        cout << "No. of test cases: ";
        cin >> t;

        while (t--) {
            int n;
            cout << "Enter the number of processes: ";
            cin >> n;

            vector<int> startPoint(n);
            vector<int> endPoint(n);

            cout << "Enter the start : ";
            for (int i = 0; i < n; i++) {
                cin >> startPoint[i];
            }

            cout << "Enter the end : ";
            for (int i = 0; i < n; i++) {
                cin >> endPoint[i];
            }

            cout << process_schedular(startPoint, endPoint) << endl;
        }
    }
private: 
    int process_schedular(vector<int>& startPoint, vector<int>& endPoint) {
        int n = startPoint.size();

        // Sort processes by their start times
        vector<pair<int, int> > processes;
        for (int i = 0; i < n; i++) {
            processes.push_back(make_pair(startPoint[i], endPoint[i]));
        }
        sort(processes.begin(), processes.end());

        // Min-heap to track the end time of processes that are currently scheduled
        priority_queue<int, vector<int>, greater<int> > pq;
        int ans = 1;

        // Start scheduling the first process
        pq.push(processes[0].second);

        for (int i = 1; i < n; i++) {
            int start = processes[i].first;
            int end = processes[i].second;

            // If the process can start after the earliest finishing process, reuse the CPU
            if (pq.top() >= start) {
                ans++;
            }

            // Schedule the current process
            pq.push(end);
        }

        // The size of the heap represents the minimum number of CPUs needed
        return ans;
    }
};

int main() {
    Solution Obj;
    Obj.solve();
    return 0;
}
