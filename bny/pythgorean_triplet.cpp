#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <climits>

using namespace std;

class Solution {
private:
    vector<int> bfs(const vector<vector<int>>& graph, int source) {
        vector<int> dist(graph.size(), INT_MAX);
        queue<int> q;

        dist[source] = 0;
        q.push(source);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor : graph[node]) {
                if (dist[neighbor] == INT_MAX) {  // Unvisited
                    dist[neighbor] = dist[node] + 1;
                    q.push(neighbor);
                }
            }
        }

        return dist;
    }

public:
    int countPythagoreanTriples(int tree_nodes, vector<int>& tree_from, vector<int>& tree_to, int x, int y, int z) {
        vector<vector<int>> graph(tree_nodes);

        // Build the graph
        for (int i = 0; i < tree_from.size(); ++i) {
            graph[tree_from[i]].push_back(tree_to[i]);
            graph[tree_to[i]].push_back(tree_from[i]);
        }

        // BFS from nodes x, y, z
        vector<int> dist_x = bfs(graph, x);
        vector<int> dist_y = bfs(graph, y);
        vector<int> dist_z = bfs(graph, z);

        int count = 0;

        for (int i = 0; i < tree_nodes; ++i) {
            if (i != x && i != y && i != z) {
                vector<int> distances = {dist_x[i], dist_y[i], dist_z[i]};
                sort(distances.begin(), distances.end());

                if ((distances[0] * distances[0] + distances[1] * distances[1]) == distances[2] * distances[2]) {
                    count++;
                }
            }
        }

        return count;
    }
};

int main() {
    Solution obj;
    int tree_nodes = 9;
    vector<int> tree_from = {0, 1, 2, 3, 4, 5, 6, 7};
    vector<int> tree_to = {1, 2, 3, 4, 5, 6, 7, 8};
    int x = 3;
    int y = 4;
    int z = 5;

    int result = obj.countPythagoreanTriples(tree_nodes, tree_from, tree_to, x, y, z);
    cout << "Number of Pythagorean triples: " << result << endl;

    return 0;
}
