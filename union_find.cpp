#include<iostream>
#include<vector>
using namespace std;
class UnionFind{
    private:
        vector<int> rep,setSize;
        int size,nSets;
    public:
        UnionFind(int _size):size(_size),nSets(_size){
            rep.resize(size); setSize.resize(size);
            for(int i=0;i<size;i++){
                rep[i]=i+1;
                setSize[i]=1;
            }
        }
        int getSetNum(){
            return nSets;
        }
        int findSet(int i){
            if(rep[i-1]==i) return i;
            rep[i-1]=findSet(rep[i-1]);
            return rep[i-1];
        }
        int getSetSize(int i){
            return setSize[findSet(i)-1];
        }
        bool isSameSet(int i,int j){
            return findSet(i)==findSet(j);
        }
        bool merge(int i,int j){
            if(isSameSet(i,j)) return false;
            nSets--;
            int iset=findSet(i),jset=findSet(j);
            rep[iset-1]=jset;
            setSize[jset-1]+=setSize[iset-1];
            return true;
        }
        
};
int main(){

    return 0;
}