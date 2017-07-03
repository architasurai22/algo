#include<bits/stdc++.h>
#include <stdio.h>
using namespace std;
#define array_size 100000
long long int arr[100000];
long long int  _mergeSort(long long int temp[], long long int left, long long int right);
long long int merge(long long int temp[], long long int left, long long int mid, long long int right);
/* This function sorts the input array and returns the
   number of inversions in the array */
long long int mergeSort()
{
    long long int *temp = (long long int *)malloc(sizeof(long long int)*array_size);
    return _mergeSort(temp, 0, array_size - 1);
}
 
/* An auxiliary recursive function that sorts the input array and
  returns the number of inversions in the array. */
long long int _mergeSort(long long int temp[], long long int left, long long int right)
{
  long long int mid, inv_count = 0;
  if (right > left)
  {
    /* Divide the array into two parts and call _mergeSortAndCountInv()
       for each of the parts */
    mid = (right + left)/2;
 
    /* Inversion count will be sum of inversions in left-part, right-part
      and number of inversions in merging */
    inv_count  = _mergeSort(temp, left, mid);
    inv_count += _mergeSort(temp, mid+1, right);
 
    /*Merge the two parts*/
    inv_count += merge(temp, left, mid+1, right);
  }
  return inv_count;
}
/* This funt merges two sorted arrays and returns inversion count in
   the arrays.*/
long long int merge(long long int temp[], long long int left, long long int mid, long long int right)
{
  long long int i, j, k;
  long long int inv_count = 0;
 
  i = left; /* i is index for left subarray*/
  j = mid;  /* j is index for right subarray*/
  k = left; /* k is index for resultant merged subarray*/
  while ((i <= mid - 1) && (j <= right))
  {
    if (arr[i] <= arr[j])
    {
      temp[k++] = arr[i++];
    }
    else
    {
      temp[k++] = arr[j++];
 
     /*this is tricky -- see above explanation/diagram for merge()*/
      inv_count = inv_count + (mid - i);
    }
  }
 
  /* Copy the remaining elements of left subarray
   (if there are any) to temp*/
  while (i <= mid - 1)
    temp[k++] = arr[i++];
 
  /* Copy the remaining elements of right subarray
   (if there are any) to temp*/
  while (j <= right)
    temp[k++] = arr[j++];
 
  /*Copy back the merged elements to original array*/
  for (i=left; i <= right; i++)
    arr[i] = temp[i];
 
  return inv_count;
}
int main()
{
	char buf[10];
	FILE *f;
	int i =0;
	f=fopen("invint.txt", "r");
    if (!f)
    {	
    	cout<<"error\n";
        return 1;
    }
	while (fscanf(f,"%s\n",buf)!=EOF)
        arr[i++] = atoi(buf);
    cout<<arr[99999]<<endl;
    long long int inv = mergeSort();
    cout<<inv<<endl;
	//printf(" Number of inversions are %ld \n", mergeSort());
    // 2407905288
	return 0;
}