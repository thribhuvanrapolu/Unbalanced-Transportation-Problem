#include <bits/stdc++.h>

using namespace std;

void addEdge(vector<int> adj[], int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void printGraph(vector<int> adj[], int V)
{
    for (int v = 0; v < V; ++v) {
        cout << "\n Adjacency list of vertex " << v
             << "\n head ";
        for (auto x : adj[v])
            cout << "-> " << x;
        printf("\n");
    }
}

// void DFS(struct Graph* graph, int vertex) {
//   struct node* adjList = graph->adjLists[vertex];
//   struct node* temp = adjList;

//   graph->visited[vertex] = 1;
//   printf("Visited %d \n", vertex);

//   while (temp != NULL) {
//     int connectedVertex = temp->vertex;

//     if (graph->visited[connectedVertex] == 0) {
//       DFS(graph, connectedVertex);
//     }
//     temp = temp->next;
//   }
// }
vector<bool>visited(7,false);
deque<int>temp;
bool dfs(int node,int par)
{
    visited[node]=true;
    temp.push_back(node);

    for(int v:ar[node])
    {
        if(visited[v]==false)
        {
            if(dfs(v,node)==true)
            return true;

            else if(par!=v)
            {
                temp.push_back(v);
                return true;
            }
        }
    }
    temp.pop_back();
    return false;
    
}

int main()
{
    int source_num=3;
    int dest_num=4;
    vector<vector<int>>cycle(source_num,vector<int>(dest_num,0));
    cycle={{0,1,0,0},{1,1,1,0},{0,1,1,1}};
    
    int V = source_num+dest_num;
    vector<int> adj[V];

    for(int i=0;i<source_num;i++)
    {
        for(int j=source_num;j<source_num+dest_num;j++)
        {
            if(cycle[i][j-source_num]==1)
            addEdge(adj,i,j);
        }
    }
    printGraph(adj, V);

    

    
}