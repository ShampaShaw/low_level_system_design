#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    static const int N = 2e5 + 200;

private:
    int wallet_denomination(vector<int>& denominations) {
        vector<int> hash(N, 0);

        for (int it = 0; it < denominations.size(); it++) {
            int left=it+1;
            int right=it*2;
            int dollar=1;
            while(left<=right && right<N){
                hash[left]+=dollar;
                hash[right+1]-=dollar;
                left=right+1;
                right=right*2;
                dollar++;
            }
            right=min(right,200000);
            hash[left]+=dollar;
            hash[right+1]-=dollar;

            left=it/2 + (it&1);
            right=it-1;
            dollar=1;
            while(left<=right && left>1){
                hash[left]+=dollar;
                hash[right+1]-=dollar;
                right=left-1;        
                left=left/2 + (left&1);
                dollar++;    
            }
            hash[left]+=dollar;
            hash[right+1]-=dollar;  
        }
        
        for(int i=1;i<N;i++)hash[i]+=hash[i-1];
        
        int ans=1e9;
        for(int i=1;i<=200000;i++)ans=min(ans,hash[i]);
        return ans;
    }

public:
    void solve() {
        int t;
        cin >> t;

        while (t--) {
            int n;
            cout << "Enter the number of denominations: ";
            cin >> n;

            vector<int> denominations(n);
            cout << "Enter the denominations: ";

            for (int i = 0; i < n; i++) {
                cin >> denominations[i];
            }

            int amount = wallet_denomination(denominations);
            cout << "Amount: " << amount << endl;
        }
    }
};

int main() {
    Solution obj;
    obj.solve();
    return 0;
}
