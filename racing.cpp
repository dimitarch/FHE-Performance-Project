#include <iostream>
#include <cmath>
using namespace std;

int a[1024]={};
int n, i;
long dp[1024][3]={};

int main(){
    cin>>n;
    for(i=0;i<n;i++)
        cin>>a[i];

    dp[0][0]=a[0];
    dp[0][1]=0;
    dp[0][2]=0;

    for(i=1;i<n;i++){
        dp[i][0]=min(dp[i-1][0],min(dp[i-1][1],dp[i-1][2]))+a[i];
        dp[i][1]=dp[i-1][0];
        dp[i][2]=dp[i-1][1];
    }
    cout<<min(dp[n-1][0],min(dp[n-1][1],dp[n-1][2]))<<endl;
    return 0;
}
