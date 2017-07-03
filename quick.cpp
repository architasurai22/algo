#include<bits/stdc++.h>
#include <stdio.h>
using namespace std;
long long int partition1(int arr[], int l, int r)
{
	if(r-l<1)
		return 0;
	long long int count = r-l;
	//cout<<count<<endl;
	int pivot = arr[l];
	int i = l+1, j = l+1,temp;
	for(j=l+1;j<=r;j++)
	{
		if(arr[j]<pivot)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
		}
	}
	temp = arr[i-1];
	arr[i-1] = arr[l];
	arr[l] = temp;
	count+= partition1(arr,l,i-2);
	count+= partition1(arr,i,r);
	return count;
}

long long int partition2(int arr[], int l, int r)
{
	if(r-l<1)
		return 0;
	long long int count = r-l;
	int temp = arr[l];
	arr[l]=arr[r];
	arr[r]=temp;
	int pivot = arr[l];
	int i = l+1, j = l+1;
	for(j=l+1;j<=r;j++)
	{
		if(arr[j]<pivot)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
		}
	}
	temp = arr[i-1];
	arr[i-1] = arr[l];
	arr[l] = temp;
	count+= partition2(arr,l,i-2);
	count+= partition2(arr,i,r);
	return count;
}

long long int partition3(int arr[], int l, int r)
{
	if(r-l<1)
		return 0;
	long long int count = r-l;
	int t1,t2,t3,temp,n;
	n=r-l+1;
	t1=l;
	if(n%2)
		t2=n/2;
	else
		t2=(n/2)-1;
	t2=l+t2;
	t3=r;
	if((arr[t1]>=arr[t2]&&arr[t1]<=arr[t3])||(arr[t1]<=arr[t2]&&arr[t1]>=arr[t3]))
	{
		temp = arr[t1];
		arr[t1]=arr[l];
		arr[l]=temp;
	}
	else if((arr[t2]>=arr[t1]&&arr[t2]<=arr[t3])||(arr[t2]<=arr[t1]&&arr[t2]>=arr[t3]))
	{
		temp = arr[t2];
		arr[t2]=arr[l];
		arr[l]=temp;
	}
	else
	{
		temp = arr[t3];
		arr[t3]=arr[l];
		arr[l]=temp;
	}
	int pivot = arr[l];
	int i = l+1, j = l+1;
	for(j=l+1;j<=r;j++)
	{
		if(arr[j]<pivot)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
		}
	}
	temp = arr[i-1];
	arr[i-1] = arr[l];
	arr[l] = temp;
	count+= partition3(arr,l,i-2);
	count+= partition3(arr,i,r);
	return count;
}


int main()
{
	char buf[10];
	FILE *f;
	int i =0;
	int arr[10000];
	f=fopen("quicktxt.txt", "r");
    if (!f)
    {	
    	cout<<"error\n";
        return 1;
    }
	while (fscanf(f,"%s\n",buf)!=EOF)
        arr[i++] = atoi(buf);
    

    //long long int count1 = partition1(arr,0,9999);
    //cout<<count1<<endl;
   
    //long long int count2 = partition2(arr,0,9999);
    //cout<<count2<<endl;
    
    long long int count3 = partition3(arr,0,9999);
    cout<<count3<<endl;
    
    
	return 0;
}
//162085
//164123
//138382
