#include <bits/stdc++.h>

using namespace std;

struct node
{
       int wt,len;
       float rat;
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
    root=new node;
    fgets(a,50,f);
    getInt(a,strlen(a),&wt,&len);
    root->wt=wt; root->len=len; root->rat=1.0*wt/len; root->left=NULL; root->right=NULL;
    while(fgets(a,50,f)!=NULL)
    {
            getInt(a,strlen(a),&wt,&len);
            node *nn=new node;
            nn->wt=wt; nn->len=len; nn->rat=1.0*wt/len; nn->left=NULL; nn->right=NULL;
            node *temp=root,*t2;
            while(temp!=NULL)
            {
                   t2=temp;
                   if(nn->rat<=temp->rat) temp=temp->right;
                   else temp=temp->left;
            }
            if(nn->rat<=t2->rat) t2->right=nn;
            else t2->left=nn;
    }
    cout<<"Sum of Weighted Completion Times: "<<inorder(root)<<endl;
    fclose(f);
    
    return 0;
}
// 67311454237