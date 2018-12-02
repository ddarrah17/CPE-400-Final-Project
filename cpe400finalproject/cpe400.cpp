#include<bits/stdc++.h>
#include<iostream>

using namespace std;

# define INF 0x3f3f3f3f

typedef pair<int, int> iPair;

class Graph
{
    int V;
    list< pair<int, int> > *adj;

  public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void shortestPath(int s, vector<int>& power);
    void test(int s,int dest, vector<int>& power);
};

Graph::Graph(int V)
{
  this->V = V;
  adj = new list<iPair> [V];
}

void Graph::addEdge(int u, int v, int w)
{
  adj[u].push_back(make_pair(v, w));
  adj[v].push_back(make_pair(u, w));
}

void Graph::shortestPath(int src, vector<int>& power)
{
  priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

  vector<int> dist(V, INF);

  pq.push(make_pair(0, src));
  dist[src] = 0;

  while (!pq.empty())
  {
    int u = pq.top().second;
    pq.pop();

    list< pair<int, int> >::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
      int v = (*i).first;
      int weight = (*i).second;

      if (dist[v] > dist[u] + weight)
      {
        dist[v] = dist[u] + weight;
        pq.push(make_pair(dist[v], v));
      }
    }
  }

  printf("Vertex   Distance from Source\n");
  for (int i = 0; i < V; ++i)
      printf("%d \t\t %d\n", i, dist[i]);
}

void Graph::test(int src,int dest, vector<int>& power)
{
  priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

  vector<int> dist(V, INF);

  pq.push(make_pair(0, src));
  dist[src] = 0;

  while (!pq.empty())
  {
    int u = pq.top().second;
    pq.pop();

    list< pair<int, int> >::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
      int v = (*i).first;
      int weight = (*i).second;

      if (dist[v] > dist[u] + weight)
      {
        dist[v] = dist[u] + weight;
        pq.push(make_pair(dist[v], v));
        cout<< " " << v << ",";
        power[v] = power[v] - 10;
      }
    }
  }

  printf("\nSource Node (%d)   Distance from node (%d)\n",src,dest);
      printf("%d \t\t      %d\n", src, dist[dest]);
}

int main()
{
  //VARIABLES
  int node_count=0;
  int src, dest, dist = 0;
  vector<int> power;

  //INPUT
  cout<<"Enter number of nodes for the network: ";
  cin>>node_count;
  Graph network(node_count);
  //MENU
  for(int index=0;index<node_count;index++)
  {
    cout<<"Enter Connection Details (Source Destination Distance): ";
    cin>>src>>dest>>dist;
    network.addEdge(src, dest, dist);
    power.push_back(100);
  }

  network.shortestPath(0, power);


  cout<<"Send a packet (Source Dest): ";
  cin>>src>>dest;
  cout<<"Route taken: ";
  network.test(src,dest,power);

  for(int i = 0 ; i < power.size() ; i++)
  {
    cout<<"Power remaining at node "<<i<< " :"<<power[i]<<endl;
  }
  return 0;
}