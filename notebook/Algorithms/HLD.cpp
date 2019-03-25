#include<bits/stdc++.h>
using namespace std;

int chainNo = 0;  // index of current chain (last chain started)
int chainHead[N]; // head of the chain (entry point)
int chainPos[N];  // the position of the node in the chain
int chainInd[N];  // the chain index of each node
int chainSize[N]; // the size of each chain

void hld(int cur) {
    if(chainHead[chainNo] == -1) {
        chainHead[chainNo]=cur;
    }
    chainInd[cur] = chainNo;
    chainPos[cur] = chainSize[chainNo];
    chainSize[chainNo]++;
    int ind = -1, mai = -1;
    for (int i = 0; i < adj[cur].sz; i++) {
        if (subsize[ adj[cur][i] ] > mai) {
            mai = subsize[ adj[cur][i] ];
            ind = i;
        }
    }
    if (ind >= 0) {
        hld(adj[cur][ind]);
    }
    for(int i = 0; i < adj[cur].sz; i++) {
        if (i != ind) {
            chainNo++;
            hld(adj[cur][i]);
        }
    }
}
