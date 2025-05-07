#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int minVertex(vector<int> &key, vector<bool> &mst){
    int v=mst.size();
    int minval=INT_MAX;
    int ind=-1;

    for(int i=0;i<v;i++){
        if(key[i]<minval && !mst[i]){
            minval=key[i];
            ind=i;
        }
    }
    return ind;
}

void primMST(vector<vector<int>> &graph){
    int v=graph.size();

    vector<int> parent(v,-1);
    vector<int> key(v,INT_MAX);
    vector<bool> mst(v,false);

    int cost=0;
    key[0]=0;

    for(int i=0;i<v-1;i++){
        int u=minVertex(key,mst);
        mst[u]=true;

        for(int a=0;a<v;a++){
            if(graph[u][a]>0 && !mst[a] && key[a]>graph[u][a]){
                key[a]=graph[u][a];
                parent[a]=u;
            }
        }

    }
    cout<<"\nEdges \tWeight\n";
    for(int i=1;i<v;i++){
        cout<<parent[i]+1<<"-"<<i+1<<"\t"<<key[i]<<endl;
        cost+=key[i];
    }
    cout<<"Total cost: "<<cost<<endl;
    
}

int main(){
    int V,E;
    cout<<"Enter number of vertices: ";
    cin>>V;
    cout<<"Enter number of edges: ";
    cin>>E;
    
    vector<vector<int>> graph(V,vector<int>(V,0));

    cout<<"Enter edges: (E.g: u v weight)\n";
    for(int i=0;i<E;i++){
        int u,v,w;
        cin>>u>>v>>w;
        u--;v--;
        
        graph[u][v]=w;
        graph[v][u]=w;
    }

    primMST(graph);
    return 0;
}