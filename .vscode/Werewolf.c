#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>

int ans[101];
int now[101];


int flag;
int M,N,L;
void dfs(int num_wolf, int id){

    if(num_wolf==N||id==0){
        if(num_wolf==N){
            int liers=0,wolf_liers=0;
            for(int j=1;j<=M;j++){
                if(now[ans[j]]!=ans[j]){
                    liers++;
                    if(now[j]==-j)wolf_liers++;
                }
            }
            if(liers==L&&wolf_liers>0&&wolf_liers<N){
                flag=1;
            }
        }
        return;
    }
        now[id]=-now[id];
    num_wolf++;
    dfs(num_wolf,id-1);
    if(flag==1)return;
    now[id]=-now[id];
    num_wolf--;
    dfs(num_wolf,id-1);
    return;
}; 

int main(){

    scanf("%d %d %d",&M,&N,&L);
    int i;
    for( i=1;i<=M;i++){
        scanf("%d",&ans[i]);
        now[i]=i;
    }  
    flag=0;
    dfs(0,M);
    if(flag==0)printf("No Solution");
    else{
        int num=0;
        for(int j=M;j>=1;j--){
            if(now[j]==-j){
                num++;
                printf("%d",j);
                if(num<N)printf(" ");
            }
        }
    }
    return 0;

}