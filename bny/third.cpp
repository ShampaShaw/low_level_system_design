#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
private:
    unordered_set<int> not_path;

    int dijkstra(int dest, unordered_map<int, vector<pair<int, int> > > &graph) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        heap.push(make_pair(0, 1));  
        unordered_set<int> visited;

        while (!heap.empty()) {
            int dist = heap.top().first;
            int node = heap.top().second;
            heap.pop();

            if (visited.find(node) != visited.end()) {
                continue;
            }
            visited.insert(node);

            if (node == dest) {
                return dist;
            }

            for (auto &neighbor : graph[node]) {
                int adj = neighbor.first;
                int wt = neighbor.second;

                if (visited.find(adj) == visited.end() && not_path.find(adj) == not_path.end()) {
                    heap.push(make_pair(dist + wt, adj));
                }
            }
        }

        return -1;  
    }

public:
    vector<int> findAnswer(int n, int m, vector<int> &t, vector<int> &endpoint1, vector<int> &endpoint2, vector<int> &edgeLength) {
        unordered_map<int, vector<pair<int, int> > > graph;

        for (int i = 0; i < m; i++) {
            graph[endpoint1[i]].push_back(make_pair(endpoint2[i], edgeLength[i]));
            graph[endpoint2[i]].push_back(make_pair(endpoint1[i], edgeLength[i]));
        }

        vector<int> ans(n, -1);
        ans[0] = 0; 
        for (int i = 1; i <= n; i++) {
            if (not_path.find(i) != not_path.end()) {
                continue;
            }
            int distance = dijkstra(i, graph);
            if (distance == -1 || distance >= t[i - 1]) {
                not_path.insert(i);
            } else {
                ans[i - 1] = distance;
            }
        }

        return ans;
    }
};

int main() {
    Solution obj;
    int n = 4;
    int m = 4;
    vector<int> t = {1, 2, 7, 9};
    vector<int> endpoint1 = {1, 2, 3, 4};
    vector<int> endpoint2 = {2, 4, 1, 3};
    vector<int> edgeLength = {2, 1, 5, 3};

    vector<int> result = obj.findAnswer(n, m, t, endpoint1, endpoint2, edgeLength);

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
