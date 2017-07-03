#include <bits/stdc++.h>

using namespace std;

struct node
{
       int wt,len,diff;
       node *left;
       node *right;
}*root;

void getInt(char *a, int n, int *wt, int *len)
{
     int i,j;
     char ab[10];
     for(i=0; a[i]!=' '; i++) ab[i]=a[i];
     ab[i]='\0';
     *wt=atoi(ab);
     for(j=0, i++; a[i]!='\n'; i++,j++) ab[j]=a[i];
     ab[j]='\0';
     *len=atoi(ab);
}

void swap(int *p, int*q)
{
     int temp;
     temp=*p; *p=*q; *q=temp;
}

long long inorder(node *root)
{
     static long long swct;
     static long long time;
     if(root==NULL) return 0;
     inorder(root->left);
     time+=root->len;
     swct+=(root->wt*time);
     inorder(root->right);
     return swct;
}

int main()
{
    char a[50];
    FILE *f=fopen("jobs.txt","r");
    fgets(a,10,f);
    int no_jobs=atoi(a);
    int wt,len;
    cout<<no_jobs<<endl;
    root=new node;
    fgets(a,50,f);
    getInt(a,strlen(a),&wt,&len);
    root->wt=wt; root->len=len; root->diff=wt-len; root->left=NULL; root->right=NULL;
    while(fgets(a,50,f)!=NULL)
    {
            getInt(a,strlen(a),&wt,&len);
            node *nn=new node;
            nn->wt=wt; nn->len=len; nn->diff=wt-len; nn->left=NULL; nn->right=NULL;
            node *temp=root,*t2;
            while(temp!=NULL)
            {
                   t2=temp;
                   if(nn->diff<temp->diff) temp=temp->right;
                   else if(nn->diff==temp->diff)
                   {
                       if(nn->wt<temp->wt)
                       {
                            swap(&nn->wt,&temp->wt);
                            swap(&nn->diff,&temp->diff);
                            swap(&nn->len,&temp->len);
                       }
                       temp=temp->left;
                   }
                   else temp=temp->left;
            }
            if(nn->diff<t2->diff) t2->right=nn;
            else t2->left=nn;
    }
    cout<<"Sum of Weighted Completion Times: "<<inorder(root)<<endl;
    fclose(f);
    
    return 0;
}
// 69119377652