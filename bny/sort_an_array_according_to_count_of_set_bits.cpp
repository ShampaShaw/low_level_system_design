#include<bits/stdc++.h>

using namespace std;
#define int long long
bool cm (pair <int,int> a, pair <int, int> b){
if(a.first == b.first) return a.second <
b.second;
return a.first > b.first;
}
int32_t main() {
ios_base::sync_with_stdio(false);
cin.tie(NULL);
int n ; cin >> n;
vector <int> arr(n) ;
for(auto & it : arr) cin >> it;
vector <pair<int,int>> vec;
for(int i = 0 ; i < n ; i++)
{
int cnt = 0 ;
for(int j = 31 ; j >= 0; j--) {
int mask = (1 << j);
cnt +=((arr[i] & mask) != 0 );
}
vec.push_back({cnt, i});
}
sort(vec.begin(), vec.end(), cm);
for(auto & it : vec) {
cout << arr[it.second] << " ";
}
cout << "\n";
}