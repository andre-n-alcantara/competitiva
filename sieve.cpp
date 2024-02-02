#include<bits/stdc++.h>
using namespace std;
int MAXN=101; //0-100
bitset<10000> isprime; 
void seive(){
    isprime.set();
    isprime[0]=isprime[1]=0;
    for(int n=2;n*n<MAXN;n++)
        if(isprime[n])
            for(int i=n*n;i<MAXN;i+=n)
                isprime[i]=0;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    return 0;
}