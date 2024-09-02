////////////n = 3
//arr[] = [757],[145],[986]
//output = 9 + 8 + 7 = 24

#include<iostream>
#include<vector>
#include<map>
#include<climits>


using namespace std;

class Solution{
public:
    void solve(){
        int n;
        cin>>n;
        vector<string> arr(n);

        for(int i=0; i<n; i++){
            cin>>arr[i];
        }
        map<int,int> mp;
        int m = arr[0].size();

        for(int i=0; i<m; i++) mp[i] = INT_MIN;

        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                mp[j] = max(mp[j],arr[i][j]-'0');
            }
        }

        int sum = 0;

        for(int i=0; i<mp.size(); i++){
            sum += mp[i];
        }

        cout<<sum<<endl;
    }
};

int main(){
    int t;
    cin>>t;

    while(t--){
        Solution obj;
        obj.solve();
    }

    return 0;
}