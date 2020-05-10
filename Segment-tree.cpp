# code-of-sigment-tree

#include<bits/stdc++.h>
using namespace std;
void buildtree(int* arr,int* tree , int start , int end, int tree_node){
    if(start == end){
        tree[tree_node]=arr[start];
        return;
    }
    int mid=(start+end)/2;
    buildtree(arr,tree,start,mid,2*tree_node);
    buildtree(arr,tree,mid+1,end,2*tree_node+1);
    tree[tree_node]=min(tree[2*tree_node],tree[2*tree_node+1]); 
}
int min_query(int*arr, int* tree, int start,int end,int tree_node,int left,int right) 
    //completely outside the range*******
    if(start> right || end < left){
        return 0; 
    }  
    // completely overlape
    if(start>=left && end <=right){
       // cout<<"mj "<<tree[tree_node];
         return tree[tree_node];
    }
    //partially ovrlapped
    int mid=start+( end-start)/2;
    int ans1=min_query(arr,tree,start,mid,2*tree_node,left,right);
    int ans2=min_query(arr,tree,mid+1,end,2*tree_node+1,left,right);
   // cout<<ans1<<" "<<ans2<<endl;
    if(ans1==0)
        return ans2;
    else if(ans2==0)
        return ans1;
    else
    return min(ans1 , ans2);

}
void update_query(int* arr,int* tree,int start,int end,int tree_node,int idx,int value){
    if(start==end)
    {
        arr[idx]=value;
        tree[tree_node]=value;
        return;
    }
    int mid=(start+end)/2;
    if(mid<idx){  
        update_query(arr,tree,mid+1,end,2*tree_node+1,idx,value);
    }
    else
    {
           update_query(arr,tree,start,mid,2*tree_node,idx,value);
    }  
    tree[tree_node]=min(tree[2*tree_node] , tree[2*tree_node+1]);
}
int main() {
     int n,q;
    cin>>n>>q;
    int* arr=new int[n+1];
    for(int i=0;i<n;i++)
        cin>>arr[i];
    int size = 4*n;
    int* tree = new int[size];
    buildtree(arr,tree,0,n-1,1);
    for(int i=0;i<q;i++){
        char Q;
        int a,b;
        cin>>Q>>a>>b;
        if(Q=='q'){
            cout<<min_query(arr,tree,0,n-1,1,a-1,b-1)<<endl; 
        }
        else if(Q=='u'){
            update_query(arr,tree,0,n-1,1,a-1,b);
        }
    }
    return 0;
}
