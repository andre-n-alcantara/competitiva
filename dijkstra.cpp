#include<iostream>
#include<vector>
#include<utility>
#include<queue>
#include<climits>
using namespace std;
void dijkstra(vector<vector<pair<int,int>>> &graph,int src){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    vector<bool> visit(graph.size(),false);
    vector<int> dist(graph.size(),INT_MAX);
    dist[src]=0;
    pair<int,int> p=make_pair(0,src);
    pq.push(p);
    while(!pq.empty()){
        int u=pq.top().second;
        if(visit[u]){ pq.pop(); continue; }
        visit[u]=true;
        for(auto &adj:graph[u]){
            int v=adj.second;
            int w=adj.first;
            if(!visit[v]){
                if(dist[v]>dist[u]+w){
                    dist[v]=dist[u]+w;
                }
                pq.push(make_pair(dist[v],v));
            } 
        }
        pq.pop();
    }
    for(int &i:dist) cout<<i<<' ';
    cout<<'\n';
}
int main(){
    vector<vector<pair<int,int>>> graph;
    int nV,nE; cin>>nV>>nE;
    graph.resize(nV);
    for(int i=0;i<nE;i++){
        int u,v,w; cin>>u>>v>>w;
        graph[u].push_back(make_pair(w,v));
        graph[v].push_back(make_pair(w,u));
    }
    int src=0;
    dijkstra(graph,src);
    return 0;
}