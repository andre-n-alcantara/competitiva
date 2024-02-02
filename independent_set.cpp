#include<bits/stdc++.h>
using namespace std;
vector<vector<int>> g(100,vector<int>());
vector<int> mxIndSet;
int nv,ne;
void getIndSet(int u,vector<int> &vec){
    vec.push_back(u);
    if(vec.size()>mxIndSet.size()){ mxIndSet=vec; }
    for(int v=u+1;v<nv;v++){
        bool skip=false;
        for(int u1=vec.size()-1;u1>=0;u1--){
            auto it=find(g[vec[u1]].begin(),g[vec[u1]].end(),v);
            if(it!=g[vec[u1]].end()){ skip=true; break;}
        }
        if(skip) continue;
        getIndSet(v,vec);
    }
    vec.pop_back();
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int nCase; cin>>nCase;
    for(int c=0;c<nCase;c++){
         cin>>nv>>ne;
         for(auto &i:g) i.clear();
        for(int e=0;e<ne;e++){
            int v1,v2; cin>>v1>>v2; v1--;v2--;
            g[v1].push_back(v2);
            g[v2].push_back(v1);
        }
        mxIndSet.clear();
        vector<int> vec;
        for(int u=0;u<nv;u++){
            getIndSet(u,vec);
            vec.clear();
        }
        
    }
    return 0;
}