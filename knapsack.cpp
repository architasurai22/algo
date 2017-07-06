#include <bits/stdc++.h>
#define MAX(a,b) a>b?a:b

using namespace std;

struct node
{
       int n1,n2,cost;
       node *left;
       node *right;
};

void getLong(char *a, int n, long long *val1, long long *val2)
{
     int i,j;
     char ab[20];
     for(i=0; a[i]!=' '; i++) ab[i]=a[i];
     ab[i]='\0';
     *val1=atol(ab);
     for(j=0, i++; a[i]!='\n'; i++,j++) ab[j]=a[i];
     ab[j]='\0';
     *val2=atol(ab);
}

int main()
{
    char a[50];
    long long W, no_items, *w, *v, k=1;
    FILE *f=fopen("knapsack2.txt","r");
    fgets(a,50,f);
    getLong(a,strlen(a),&W,&no_items);
    w=new long long[no_items+1];
    v=new long long[no_items+1];
    long long *cal[2];
    for(int j=0; j<2; j++) cal[j]=new long long[W+1];
    while(fgets(a,50,f))
    {
        long long val, wt;
        getLong(a,strlen(a),&val,&wt);
        w[k]=wt;
        v[k++]=val;
    }
    fclose(f);
    for(long long j=0; j<=W; j++) cal[0][j]=0;
    for(int i=1; i<=no_items; i++)
    {
          for(long long x=0; x<=W; x++)
             if(x>=w[i])
                cal[1][x]=MAX(cal[0][x],cal[0][x-w[i]]+v[i]);
             else
                cal[1][x]=cal[0][x];
          for(long long j=0; j<=W; j++)
             cal[0][j]=cal[1][j];
    }
    cout<<"Optimal Solution: "<<cal[1][W]<<endl;
    return 0;
}

// 2493893
// 4243395
