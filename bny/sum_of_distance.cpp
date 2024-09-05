///////////////////////////SUM OF DISTANCE///////////////////////////

#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>

using namespace std;

class Solution{
private:
    int miniShuffle(unordered_map<int, vector<pair<int, int>>>& graph, int node){
        int miniShuffleDistance = 0;

        for(auto neighbor : graph[node]){
            if(visitedmini.find(neighbor.first) == visitedmini.end()){
                miniShuffleDistance += neighbor.second + miniShuffle(graph, neighbor.first);
            }
        }
        return miniShuffleDistance;
    }

    int maxiShuffle(unordered_map<int, vector<pair<int, int>>>& graph, int node){
        int maxiShuffleDistance = 0;
        for(auto neighbor : graph[node]){
            if(visitedmaxi.find(neighbor.first) == visitedmaxi.end()){
                maxiShuffleDistance += neighbor.second + maxiShuffle(graph, neighbor.first);
            }
        }
        return maxiShuffleDistance;
    }
public:
    unordered_set<int> visitedmini;
    unordered_set<int> visitedmaxi;
    void solve(){
        int t;
        cout<<"No. of test cases: ";
        cin>>t;

        while(t--){
            int n;
            cout<<"No of nodes: ";
            cin>>n;

            vector<int> tree_from(n-1);
            vector<int> tree_to(n-1);

            cout<<"Enter the edges tree_from: ";
            for(int i=0; i<n-1; i++){
                cin>>tree_from[i];
            }

            cout<<"Enter the edges tree_to: ";
            for(int i=0; i<n-1; i++){
                cin>>tree_to[i];
            }

            unordered_map<int, vector<pair<int, int>>> graph;

            for(int i=0; i<n-1; i++){
                graph[tree_from[i]].push_back({tree_to[i], tree_to[i]});
                graph[tree_to[i]].push_back({tree_from[i], tree_from[i]});
            }

            vector<pair<int, int> > valmini;
            vector<pair<int, int> > valmaxi;

            for(int i=0; i<n; i++){
                int miniShuffleDistance = miniShuffle(graph,i+1);
                valmini.push_back({i+1, miniShuffleDistance});
                valmini.push_back({miniShuffleDistance, i+1});
                visitedmini.insert(i+1);
                visitedmini.insert(miniShuffleDistance);  



                int maxiShuffleDistance = maxiShuffle(graph,i+1);
                valmaxi.push_back({i+1, maxiShuffleDistance});
                valmaxi.push_back({maxiShuffleDistance, i+1});

                visitedmaxi.insert(i+1);
                visitedmaxi.insert(maxiShuffleDistance);
            }
            

            int miniDistance = 0 ;

            for(int i=0; i<valmini.size(); i++){
                miniDistance += abs(valmini[i].first - valmini[i].second);
            }

            int maxiDistance = 0;

            for(int i=0; i<valmaxi.size(); i++){
                maxiDistance += abs(valmaxi[i].first - valmaxi[i].second);
            }

            cout<<"Minimum Shuffle Distance: "<<miniDistance<<endl;
            cout<<"Maximum Shuffle Distance: "<<maxiDistance<<endl;
        }
    }
};

int main(){
    Solution obj;
    obj.solve();
}