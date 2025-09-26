#include<stdio.h>
#define n 7
void swap(int *a,int *b)
{
    int tmp=*a;
    *a=*b;
    *b=tmp;
}
int partition(int S[],int l,int r)
{
    int pivot=S[r];
    int left=l;
    int right=r-1;
    while(left<=right)
    {
        while(left<=right&&S[left]>pivot)
            left+=1;
        while(left<=right&&S[right]<pivot)
            right-=1;
        if(left<right)
        {
            swap(&S[left],&S[right]);
            left+=1;
            right-=1;
        }
    }
    swap(&S[left],&S[r]);
    return left;
}
void qsort(int S[],int l,int r)
{
    if(l<r)
    {
        int pivot=partition(S,l,r);
        qsort(S,l,pivot-1);
        qsort(S,pivot+1,r);
    }
}
int main()
{
    int S[n]={12,10,7,20,8,5,3};
    qsort(S,0,n-1);
    for(int i=0;i<3;i++)
        printf("%d ",S[i]);

}