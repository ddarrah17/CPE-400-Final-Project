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

struct Integers
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
  vector<Integers> paths;
  vector<Integers> weights; 
  vector<int> temp; 
  vector<int> tempWeight; 
  vector<int> traversed;
  vector<int> vertex; 


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
          cout << endl << dist[u] << " + " << weight << endl;  
          weights.push_back({dist[u], weight, 0});
          pq.push(make_pair(dist[v], v));
          paths.push_back({u, v, dist[v]});
          cout<<u<<","<<v<<","<<dist[v]<<endl;
          //1power[v] -= 5;
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
  
  int j = 0; 
  int k = 0; 

 // Need to check for this first step of the vector looks like this: {0, X, 0} 
 // Looking to see where the X went into the next portion like this: {X, Y, 0}
    
  while(weights[j].x == 0){
    temp.push_back(weights[j].y);
    j++; 
  }

  for(int i = 0; i < j; i++){
    if(temp[k] != weights[j].x){
      k++; 
    } else {
      //we know first path contained temp[k]
      //cout << "First Path contained " << temp[k] << endl;
      tempWeight.push_back(temp[k]);
      break;
    }
  }

  for(int i = 0; i < paths.size() - j; i++){
   if(tempWeight[0] == weights[i + j].x){
    tempWeight.push_back(weights[i+j].x + weights[i+j].y); 
   }
     //cout << "weights: " << weights[i].x << " " << weights[i].y << " " << weights[i].z << endl; 
    // cout << "paths: " << paths[i].x << " " << paths[i].y << " " << paths[i].z << endl; 
  }

  int s = 0; 
  for(int i = 0; i < paths.size(); i++){
    if(tempWeight[s] == paths[i].z){
       vertex.push_back(i); 
       s++; 
    }
  }

  for(int i = 0; i < vertex.size(); i++){
    int t = vertex[i];
    traversed.push_back(paths[t].x); 
    traversed.push_back(paths[t].y);
  }

  sort(traversed.begin(), traversed.end());
  traversed.erase( unique(traversed.begin(), traversed.end()));

  for(int i = 0; i < traversed.size(); i++){
    cout << traversed[i] << " " ;
  }
  cout << endl; 

  if(remaining==false)
  { 
    for(int i = 0; i<power.size(); i++)
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
      for(int i = 0; i < traversed.size(); i++){
        power[i] -= 10; 
        //cout<<traversed.size()<<endl;
      }
  }
}

int main()
{
  //VARIABLES
  int node_count=0;
  int src, dest, dist = 0;
  bool remaining = true;
  vector<int> power;
  int choice = 0;

  //INPUT


    cout << "\nPlease select an option" << endl;
    cout << "1. Simulation 1" << endl;
    cout << "2. Simulation 2"<< endl;
    cout << "3. Create Your Own Network"<<endl;

    cin>>choice;

    if(choice == 1)
    {
      node_count = 3;
      cout<<"creating 3 nodes"<<endl;
      cout<<"Src Dest Weight"<<endl;
      cout<<" 0     1     2"<<endl;
      cout<<" 0     2     6"<<endl;
      cout<<" 1     2     3"<<endl;
    }
    else if(choice == 2)
    {
      node_count = 7;
      cout<<"creating 7 nodes"<<endl;
      cout<<"Src Dest Weight"<<endl;
      cout<<" 0     5     1"<<endl;
      cout<<" 0     1     3"<<endl;
      cout<<" 0     3     2"<<endl;

      cout<<" 1     6     6"<<endl;
      cout<<" 2     1     2"<<endl;
      cout<<" 3     2     1"<<endl;
      cout<<" 4     3     3"<<endl;
      cout<<" 5     4     4"<<endl;
      cout<<" 6     5     2"<<endl;
    }
    else if(choice == 3)
    {
      cout<<"Enter number of nodes for the network: ";
      cin>>node_count;
    }
    else
    {
      cout<<"invalid input ending program"<<endl;
      return 0;
    }

  Graph network(node_count);

  if(choice == 1)
  {
    network.addEdge(0,1,2);
    network.addEdge(0,2,6);
    network.addEdge(1,2,3);
    for(int index=0;index<node_count;index++)
    {
      power.push_back(100);
    }
  }

  if(choice == 2)
  {
    network.addEdge(0,5,1);
    network.addEdge(0,1,3);
    network.addEdge(0,3,2);

    network.addEdge(1,6,6);
    network.addEdge(2,1,2);
    network.addEdge(3,2,1);
    
    
    network.addEdge(5,4,4);
    network.addEdge(4,3,3);
    network.addEdge(6,5,2);
    
    for(int index=0;index<node_count;index++)
    {
      power.push_back(100);
    }
  }

  if(choice == 3)
  {
    for(int index=0;index<node_count;index++)
    {
      cout<<"Enter Connection Details (Source Destination Distance): ";
      cin>>src>>dest>>dist;
      network.addEdge(src, dest, dist);
      power.push_back(100);
    }
  }


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