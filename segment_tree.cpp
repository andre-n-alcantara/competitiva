#include<bits/stdc++.h>
using namespace std;
int STsize;
class mimx{
    public:
    int mi,mx,imi,imx;
    mimx(){
        mi=INT_MAX;
        mx=INT_MIN;
    }
};
class STmimx{ //use a new mimx for every query
    private:
        vector<mimx> seg;
        vector<int> lazy;
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
        void build(const vector<int> &arr,int node=1,int l=0,int r=STsize-1){
            if(node==1){ STsize=arr.size(); r=STsize-1; seg.resize(2*pow(2,floor(log2(arr.size()))+1)); lazy.resize(seg.size(),INT_MIN); }
            if(l==r){ seg[node].mi=seg[node].mx=arr[l]; seg[node].imi=seg[node].imx=l; return; }
            build(arr,node*2,l,(l+r)/2);
            build(arr,node*2+1,(l+r)/2+1,r);
            pushUp(node);
        }
        void update(int i,int j,int v,int node=1,int l=0,int r=STsize-1){
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
        void query(mimx &ans,int i,int j,int node=1,int l=0,int r=STsize-1){
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
class STsum{
    private:
        vector<int> seg;
        vector<int> lazy;
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
        void build(const vector<int> &arr,int node=1,int l=0,int r=STsize-1){
            if(node==1){ STsize=arr.size(); r=STsize-1; seg.resize(2*pow(2,floor(log2(arr.size()))+1)); lazy.resize(seg.size(),INT_MIN); }
            if(l==r){ seg[node]=arr[l]; return; }
            build(arr,node*2,l,(l+r)/2);
            build(arr,node*2+1,(l+r)/2+1,r);
            pushUp(node);
        }
        void update(int i,int j,int v,int node=1,int l=0,int r=STsize-1){
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
        int query(int i,int j,int node=1,int l=0,int r=STsize-1){
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
struct mxsum{
    int p,s,t,m; //preffix, suffix, total, max
};
class STmxsum{
    private:
        vector<mxsum> seg;
        void merge(mxsum &md,mxsum &ml,mxsum &mr){
            md.p = max(ml.p, ml.t + mr.p);
            md.s = max(mr.s, mr.t + ml.s);
            md.t = ml.t + mr.t;
            md.m = max(ml.s + mr.p, max(ml.m, mr.m));
        }
        void pushUp(int node){
            merge(seg[node],seg[node*2],seg[node*2+1]);
        }
    public:
        void build(const vector<int> &arr,int node=1,int l=0,int r=STsize-1){
            if(node==1){ STsize=arr.size(); r=STsize-1; seg.resize(2*pow(2,floor(log2(arr.size()))+1)); }
            if(l==r){ seg[node].p=seg[node].s=seg[node].t=seg[node].m=arr[l]; return; }
            build(arr,node*2,l,(l+r)/2);
            build(arr,node*2+1,(l+r)/2+1,r);
            pushUp(node);
        }
        void update(int i,int v,int node=1,int l=0,int r=STsize-1){
            if(l==r){
                seg[node].p=seg[node].s=seg[node].t=seg[node].m=v;
                return;
            }
            if(i<=(l+r)/2) update(i,v,node*2,l,(l+r)/2);
            else update(i,v,node*2+1,(l+r)/2+1,r);
            pushUp(node);
        }
        mxsum query(int i,int j,int node=1,int l=0,int r=STsize-1){
            if(i<=l && r<=j){
                return seg[node];
            }
            if(j<=(l+r)/2)
                return query(i,j,node*2,l,(l+r)/2);
            else if(i>(l+r)/2)
                return query(i,j,node*2+1,(l+r)/2+1,r);
            mxsum ans, ml=query(i,j,node*2,l,(l+r)/2), mr=query(i,j,node*2+1,(l+r)/2+1,r);
            merge(ans, ml, mr);
            return ans;
        }
};
class STdistinct{  //use a new set for every query
    private:
        vector<set<int>> seg;
        vector<int> lazy;
        void pushUp(int node){
            if(seg[node*2+1].size()==1){
                seg[node]=seg[node*2];
                seg[node].insert(seg[node*2+1].begin(),seg[node*2+1].end());
            }
            else{
                seg[node]=seg[node*2+1];
                seg[node].insert(seg[node*2].begin(),seg[node*2].end());
            }
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
        void build(const vector<int> &arr,int node=1,int l=0,int r=STsize-1){
            if(node==1){ STsize=arr.size(); r=STsize-1; seg.resize(2*pow(2,floor(log2(arr.size()))+1)); lazy.resize(seg.size(),INT_MIN); }
            if(l==r){ seg[node].insert(arr[l]); return; }
            build(arr,node*2,l,(l+r)/2);
            build(arr,node*2+1,(l+r)/2+1,r);
            seg[node].insert(seg[node*2].begin(),seg[node*2].end());
            seg[node].insert(seg[node*2+1].begin(),seg[node*2+1].end());
        }
        void update(int i,int j,int v,int node=1,int l=0,int r=STsize-1){
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
        void query(set<int> &s,int i,int j,int node=1,int l=0,int r=STsize-1){
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
class STgcd{
    private:
        vector<int> seg;
        vector<int> lazy;
        void pushUp(int node){
            seg[node]=__gcd(seg[node*2],seg[node*2+1]);
        }
        void pushDown(int node,int l,int r){
            if(lazy[node]!=INT_MIN){
                seg[node]=lazy[node];
                if(l!=r) lazy[node*2]=lazy[node*2+1]=lazy[node];
            }
            lazy[node]=INT_MIN;
        }
    public:
        void build(const vector<int> &arr,int node=1,int l=0,int r=STsize-1){
            if(node==1){ STsize=arr.size(); r=STsize-1; seg.resize(2*pow(2,floor(log2(arr.size()))+1)); lazy.resize(seg.size(),INT_MIN); }
            if(l==r){ seg[node]=arr[l]; return; }
            build(arr,node*2,l,(l+r)/2);
            build(arr,node*2+1,(l+r)/2+1,r);
            pushUp(node);
        }
        void update(int i,int j,int v,int node=1,int l=0,int r=STsize-1){
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
        int query(int i,int j,int node=1,int l=0,int r=STsize-1){
            if(r<i || j<l) return -1;
            pushDown(node,l,r);
            if(i<=l && r<=j){
                return seg[node];
            }
            int lv=query(i,j,node*2,l,(l+r)/2);
            int rv=query(i,j,node*2+1,(l+r)/2+1,r);
            if(lv==-1) return rv;
            if(rv==-1) return lv;
            return __gcd(lv,rv);
        }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    return 0;
}
