///////////STRING MODIFICATION////////////

#include <iostream>
#include <vector>

using namespace std;

class Solution{
private:
    int string_modification(int i,int prev,bool matched,int n,string &s){
        if(i==n){
            if(matched){
                return 0;
            }
            else{
                return 1e9;
            }
        }

        if(dp[prev][matched]!=-1){
            return dp[prev][matched];
        }

        int ans = 1e9;

        if(matched == 0){
            int val = s[i]-'a';
            int cost = abs(static_cast<double>(prev - val));

            ans = cost+ min(string_modification(i+1,prev,1,n,s),string_modification(i+1,val,1,n,s));
        }
        else{
            for(int j=0; j<26; j++){
                int val = s[i]-'a';
                int cost = abs(prev - val);
                ans = min(ans, cost+string_modification(i+1,val,1,n,s));
            }
        }

        dp[prev][matched] = ans;

        return ans;

    }

public:
    int dp[26][2];

    void solve(){
        int t;
        cin>>t;

        while(t--){
            int n;
            cout<<"No. of elements: ";
            cin>>n;

            string s;
            cout<<"Enter the string: ";
            cin>>s;

            memset(dp, -1, sizeof(dp));
            int ans = 1e9;
            for(int i=0; i<26; i++){
                int val = s[0]-'a';
                int cost = abs(i-val);
                ans = min(ans, cost+string_modification(1,i,0,n,s));
            }
            cout<<ans<<endl;
        }
    }
};

int main(){
    Solution obj;
    obj.solve();
    return 0;
}





/////"aca" -> input
/////"aaa" -> 2 moves 
/////2 -> output