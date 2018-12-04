#include<bits/stdc++.h>
#include<iostream>
#include<queue>

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
    void test(int s,int dest, vector<int>& power, bool reamining);
};

struct integers
{
  int x,y,z; 
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

void Graph::test(int src,int dest, vector<int>& power,bool remaining)
{
  int edges = 0;
  priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

  vector<int> dist(V, INF);
  vector<integers> paths;

  pq.push(make_pair(0, src));
  dist[src] = 0;

  while (!pq.empty())
  {
    //cout<<src<<", ";
    int u = pq.top().second;
    pq.pop();

    list< pair<int, int> >::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
      int v = (*i).first;
      //cout << "V:" << v << endl; 
      int weight = (*i).second;
      if(power[v]>0)
      {
        //cout << endl << "v: "<< v << endl << "u: "<< u << endl; 
        //cout << "Dist v: " << dist[v] << " " << "Dist u:" << dist[u] << endl;
        if (dist[v] > dist[u] + weight)
        {
          dist[v] = dist[u] + weight;
          cout << dist[u] << " + " << weight << endl;  
          pq.push(make_pair(dist[v], v));
          cout << u << ", " << v << ", " << dist[v] << endl; 
          paths.push_back({u, v, dist[v]});

          //pair <int, int> top = pq.top();
          //cout << endl << top.first << " " << top.second << endl; 
        }
      }
      if(power[v]<=0 && remaining == false)
      {
        cout<<"no power remaining at requested node: ";
      }
    }
    //cout<<endl;
  }

  if(remaining==false)
  {
    for(int i =0; i<power.size(); i++)
    {
      if(power[i]==0)
      {
        cout<<" "<<i<<",";
      }
    }
    cout<<endl;
  }
  if(remaining==true)
  {
      printf("\nSource Node (%d)   Distance from node (%d)\n\n",src,dest);
      printf("%d \t\t      %d\n", src, dist[dest]);
      power[src]=power[src]-10;
      power[dest]=power[dest]-10;
  }
}

int main()
{
  //VARIABLES
  int node_count=0;
  int src, dest, dist = 0;
  bool remaining = true;
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


  int selection = 0;
  do
  {
    cout << "\nPlease select an option" << endl;
    cout << "1. Send a packet" << endl;
    cout << "2. View Power Remaining"<< endl;
    cout << "3. Exit Program"<<endl;
    cin >> selection;
    cout << endl;

    switch(selection)
    {
      case 1:
        cout<<endl<<"Send a packet (Source Dest): ";
        cin>>src>>dest;
        if(remaining==true)
        {
          cout<<"Route taken: ";
        }
        network.test(src,dest,power,remaining);
        for(int i = 0 ; i < power.size() ; i++)
          {
            if(power[i]==0)
            {
              remaining = false;
            }
          }
        break;

      case 2:

        for(int i = 0 ; i < power.size() ; i++)
        {
          cout<<"Power remaining at node "<<i<< " :"<<power[i]<<endl;
        }
        break;

      case 3:

        cout<<endl<<"Goodbye."<<endl;
        break;

      default:

        cout<<"Invalid Input try again"<<endl;
    }
  } while (selection !=3);

  //run using 3 nodes
  //create network using
  // 0 1 2
  // 0 2 6
  // 1 2 3
  // it will find shortest path which is a weight of 5 which is correct
  // I updated the power vector for the source and dest node
  // I cannot update the power vector for the node inbetween
  // basically it finds shortest path, but I cannot update identfiy the nodes inbetween the shortest path
  return 0;
}