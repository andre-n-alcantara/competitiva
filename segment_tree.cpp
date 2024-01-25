#include<iostream>
#include<vector>
#include<cmath>
#include<set>
#include<climits>
using namespace std;
class mimx{
    public:
    int mi,mx,imi,imx;
    mimx(){
        mi=INT_MAX;
        mx=INT_MIN;
    }
};
class ST{ //use a new mimx for every query
    private:
        vector<mimx> seg;
        vector<int> lazy;
        int size;
        void pushUp(int node){
            if(seg[node*2].mi>seg[node*2+1].mi){
                seg[node].mi=seg[node*2+1].mi; 
                seg[node].imi=seg[node*2+1].imi;
            }
            else{
                seg[node].mi=seg[node*2].mi; 
                seg[node].imi=seg[node*2].imi;
            }
            if(seg[node*2].mx<seg[node*2+1].mx){
                seg[node].mx=seg[node*2+1].mx; 
                seg[node].imx=seg[node*2+1].imx;
            }
            else{
                seg[node].mx=seg[node*2].mx; 
                seg[node].imx=seg[node*2].imx;
            }
        }
        void pushDown(int node,int l,int r){
            if(lazy[node]!=INT_MIN){
                seg[node].mi=seg[node].mx=lazy[node];
                seg[node].imi=seg[node].imx=l;
                if(l!=r) lazy[node*2]=lazy[node*2+1]=lazy[node];
            }
            lazy[node]=INT_MIN;
        }
    public:
        void build(const vector<int> &arr,int node,int l,int r){
            if(node==1){ size=arr.size(); seg.resize(2*pow(2,floor(log2(arr.size()))+1)); lazy.resize(seg.size(),INT_MIN); }
            if(l==r){ seg[node].mi=seg[node].mx=arr[l]; seg[node].imi=seg[node].imx=l; return; }
            build(arr,node*2,l,(l+r)/2);
            build(arr,node*2+1,(l+r)/2+1,r);
            pushUp(node);
        }
        void update(int i,int j,int v,int node,int l,int r){
            pushDown(node,l,r);
            if(r<i || j<l) return;
            if(i<=l && r<=j){
                lazy[node]=v;
                pushDown(node,l,r);
                return;
            }
            //if(l==r) return; //if condition above is modified
            update(i,j,v,node*2,l,(l+r)/2);
            update(i,j,v,node*2+1,(l+r)/2+1,r);
            pushUp(node);
        }
        void query(mimx &ans,int i,int j,int node,int l,int r){
            if(r<i || j<l) return;
            pushDown(node,l,r);
            if(i<=l && r<=j){
                if(seg[node].mi<ans.mi){
                    ans.mi=seg[node].mi;
                    ans.imi=seg[node].imi;
                }
                if(seg[node].mx>ans.mx){
                    ans.mx=seg[node].mx;
                    ans.imx=seg[node].imx;
                }
                return;
            }
            query(ans,i,j,node*2,l,(l+r)/2);
            query(ans,i,j,node*2+1,(l+r)/2+1,r);
        }
};
class STSum{
    private:
        vector<int> seg;
        vector<int> lazy;
        int size;
        void pushUp(int node){
            seg[node]=seg[node*2]+seg[node*2+1];
        }
        void pushDown(int node,int l,int r){
            if(lazy[node]!=INT_MIN){
                seg[node]=(r-l+1)*lazy[node];
                if(l!=r) lazy[node*2]=lazy[node*2+1]=lazy[node];
            }
            lazy[node]=INT_MIN;
        }
    public:
        void build(const vector<int> &arr,int node,int l,int r){
            if(node==1){ size=arr.size(); seg.resize(2*pow(2,floor(log2(arr.size()))+1)); lazy.resize(seg.size(),INT_MIN); }
            if(l==r){ seg[node]=arr[l]; return; }
            build(arr,node*2,l,(l+r)/2);
            build(arr,node*2+1,(l+r)/2+1,r);
            pushUp(node);
        }
        void update(int i,int j,int v,int node,int l,int r){
            pushDown(node,l,r);
            if(r<i || j<l) return;
            if(i<=l && r<=j){
                lazy[node]=v;
                pushDown(node,l,r);
                return;
            }
            //if(l==r) return; //if condition above is modified
            update(i,j,v,node*2,l,(l+r)/2);
            update(i,j,v,node*2+1,(l+r)/2+1,r);
            pushUp(node);
        }
        int query(int i,int j,int node,int l,int r){
            if(r<i || j<l) return 0;
            pushDown(node,l,r);
            if(i<=l && r<=j){
                return seg[node];
            }
            int lv=query(i,j,node*2,l,(l+r)/2);
            int rv=query(i,j,node*2+1,(l+r)/2+1,r);
            return lv+rv;
        }
};
class STDistinct{  //use a new set for every query
    private:
        vector<set<int>> seg;
        vector<int> lazy;
        int size;
        void pushUp(int node){
            seg[node].insert(seg[node*2].begin(),seg[node*2].end());
            seg[node].insert(seg[node*2+1].begin(),seg[node*2+1].end());
        }
        void pushDown(int node,int l,int r){
            if(lazy[node]!=INT_MIN){
                seg[node].clear();
                seg[node].insert(lazy[node]);
                if(l!=r) lazy[node*2]=lazy[node*2+1]=lazy[node];
            }
            lazy[node]=INT_MIN;
        }
    public:
        void build(const vector<int> &arr,int node,int l,int r){
            if(node==1){ size=arr.size(); seg.resize(2*pow(2,floor(log2(arr.size()))+1)); lazy.resize(seg.size(),INT_MIN); }
            if(l==r){ seg[node].insert(arr[l]); return; }
            build(arr,node*2,l,(l+r)/2);
            build(arr,node*2+1,(l+r)/2+1,r);
            pushUp(node);
        }
        void update(int i,int j,int v,int node,int l,int r){
            pushDown(node,l,r);
            if(r<i || j<l) return;
            if(i<=l && r<=j){
                lazy[node]=v;
                pushDown(node,l,r);
                return;
            }
            //if(l==r) return; //if condition above is modified
            update(i,j,v,node*2,l,(l+r)/2);
            update(i,j,v,node*2+1,(l+r)/2+1,r);
            pushUp(node);
        }
        void query(set<int> &s,int i,int j,int node,int l,int r){
            if(r<i || j<l) return;
            pushDown(node,l,r);
            if(i<=l && r<=j){
                s.insert(seg[node].begin(),seg[node].end());
                return;
            }
            query(s,i,j,node*2,l,(l+r)/2);
            query(s,i,j,node*2+1,(l+r)/2+1,r);
        }
};
int main(){
    
    return 0;
}