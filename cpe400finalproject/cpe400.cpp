#include <utility>
#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <algorithm>

using namespace std;

    struct edge
    {
      int to;
      int length;
    };
    
    using node = vector<edge>;
    using graph = vector<node>;
    void add_edge( graph& g, int start, int finish, int length ) {
      if ((int)g.size() <= (max)(start, finish))
        g.resize( (max)(start,finish)+1 );
      g[start].push_back( {finish, length} );
      g[finish].push_back( {start, length} );
    }
    
    using path = vector<int>;
    
    struct result {
      int distance;
      path p;
    };

    result dijkstra(const graph &graph, int source, int target, vector <int> & power) {
      vector<int> min_distance( graph.size(), INT_MAX );
      min_distance[ source ] = 0;
      set< pair<int,int> > active_vertices;
      active_vertices.insert( {0,source} );
      int temp = 0;
      
      while (!active_vertices.empty()) {
        int where = active_vertices.begin()->second;
        if (where == target)
        {
          int cost = min_distance[where];
          // std::cout << "cost is " << cost << std::endl;
          path p{where};
          while (where != source) {
            int next = where;
            for (edge e : graph[where])
            {
              // std::cout << "examine edge from " << where << "->" << e.to << " length " << e.length << ":";
              
              if (min_distance[e.to] == INT_MAX)
              {
                // std::cout << e.to << " unexplored" << std::endl;
                continue;
              }
              
              if (e.length + min_distance[e.to] != min_distance[where])
              {
                continue;
              }
              power[e.to] = power[e.to] - e.length;

              //cout<<"e.to after if: "<<e.to<<endl;
              //cout<<"temp after if: "<<e.to<<endl;
               /*if (e.length + min_distance[e.to] != min_distance[where] && power[e.length] < power[e.to])
              {
                // std::cout << e.to << " not on path" << std::endl;
              }*/

              next = e.to;
              cout<<"next: " <<next<<endl;
              p.push_back(next);
              
              // std::cout << "backtracked to " << next << std::endl;
              break;
            }
            if (where==next)
            {
              // std::cout << "got lost at " << where << std::endl;
              break;
            }
            where = next;
          }
          reverse( p.begin(), p.end() );
          return {cost, move(p)};
        }
        active_vertices.erase( active_vertices.begin() );
        for (auto ed : graph[where]) 
          if (min_distance[ed.to] > min_distance[where] + ed.length) 
          {
            active_vertices.erase( { min_distance[ed.to], ed.to } );
            min_distance[ed.to] = min_distance[where] + ed.length;
            active_vertices.insert( { min_distance[ed.to], ed.to } );
          }
      }
      return {INT_MAX};
    }
    
    int main()
    {
      graph g;
      int choice,src,dest,weight,nodecount = 0;
      vector <int> power;
      vector <int> nodes;
      
    cout << "\nPlease select an option" << endl;
    cout << "1. Simulation 1" << endl;
    cout << "2. Simulation 2"<< endl;
    cout << "3. Create Your Own Network"<<endl;

    cin>>choice;

    if(choice == 1)
    {
      cout<<"creating 3 nodes"<<endl;
      cout<<"Src Dest Weight"<<endl;
      cout<<" 0     1     2"<<endl;
      cout<<" 0     2     6"<<endl;
      cout<<" 1     2     3"<<endl;

      add_edge(g, 0, 1, 2);
      add_edge(g, 0, 2, 6);
      add_edge(g, 1, 2, 3);

        for(int index=0;index<3;index++)
        {
          power.push_back(100);
        }
    }
    else if(choice == 2)
    {
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

      add_edge(g, 0, 5, 1);
      add_edge(g, 0, 1, 3);
      add_edge(g, 0, 3, 2);
      add_edge(g, 1, 6, 6);
      add_edge(g, 2, 1, 2);
      add_edge(g, 3, 2, 1);
      add_edge(g, 5, 4, 4);
      add_edge(g, 4, 3, 3);
      add_edge(g, 6, 5, 2);

        for(int index=0;index<7;index++)
        {
          power.push_back(100);
        }
    }
    else if(choice == 3)
    {
      cout<<"Enter number of nodes for the network: ";
      cin>>nodecount;
        for(int index=0; index<nodecount;index++)
        {
          cout<<"Enter node details (Source Dest Weight): ";
          cin>>src>>dest>>weight;
          add_edge(g,src,dest,weight);
          power.push_back(100);
        }
    }
    else
    {
      cout<<"invalid input ending program"<<endl;
      return 0;
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
      {
        cout<<endl<<"Send a packet (Source Dest): "<<endl;
        cin>>src>>dest;
        auto distance = dijkstra(g,src,dest,power);
        
        cout<<"Route Taken: ";
       
        //used to find all the nodes in the shortest path
        for (int i:distance.p) 
        {
          cout << i << " ";
          nodes.push_back(i);
        }

        //used to update the power vector
        for (int i=0; i<nodes.size();i++)
        {
          //power[nodes[i]]= power[nodes[i]] - 10;
        }

        nodes.clear();
        break;
      }

      case 2:
      {
        //output the power vector
        for(int i = 0 ; i < power.size() ; i++)
        {
          cout<<"Power remaining at node "<<i<< " :"<<power[i]<<endl;
        }

        break;
      }
      case 3:
      {
        //exit program
        cout<<endl<<"Goodbye."<<endl;
        break;
      }
      default:
      {
        cout<<"Invalid Input try again"<<endl;
      }
    }
  } while (selection !=3);




      
      return 0;
}
    
