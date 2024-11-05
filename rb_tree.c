#include<stdio.h>
#include<string.h>

#define MAXN 501
//MAXN is the maximum number of internal nodes in the red-black tree
#define MOD 1000000007
//Since the answer may be very large, we output the answer modulo 1000000007
long long  r_tree[MAXN][MAXN];
//r_tree[i][j]represent the number of the different red rooted red-black trees with black height i and j internal nodes
long long  b_tree[MAXN][MAXN];
//b_tree[i][j]represent the number of the different black rooted red-black trees with black height i and j internal nodes

int main(){
    int n;
    scanf("%d",&n);
    r_tree[1][1] = 1;
    b_tree[2][1] = 1;
    b_tree[2][2] = 2;
    // there are some simple cases

    for(int i = 1; i < 30; i++){
        for( int j = 2; j <= n; j++){
            for( int k=1; k < j; k++ ){
                r_tree[i][j+1] += (b_tree[i][k]%MOD) * (b_tree[i][j-k]%MOD)%MOD;
                b_tree[i+1][j+1] += (r_tree[i][k]%MOD + b_tree[i][k]%MOD)*(r_tree[i][j-k]%MOD + b_tree[i][j-k]%MOD)%MOD;
            }
        }
    }
    long long  sum=0;
    for( int i = 0; i < 30; i++){
        sum+=b_tree[i][n];
        sum%=MOD;
    }
    printf("%lld\n",sum);
    return 0;
}