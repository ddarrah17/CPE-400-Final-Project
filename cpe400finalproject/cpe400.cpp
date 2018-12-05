#include <utility>
#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <algorithm>

using namespace std;

    /**************************************************************************************
    Creating a struct to act as the edges for each node created                           *
    int to, holds an integer value to the node the edge it is connected to                *
    int length, holds an integer value of the length to the node the edge is connected to *
    **************************************************************************************/
    struct edge
    {
      int to;
      int length;
    };
    
    

    using node = vector<edge>;
    using graph = vector<node>;

    /*******************************************************************************************************
    Function: add_edge                                                                                     *
    Variables:                                                                                             *
    graph & g is a graph passed by reference that will hold all the nodes, the graph will be the nextwork  *
    int start is the index of the starting node AKA the source nodes                                       *
    int finish is the index of the last node AKA the destination                                           *
    int length is the length it takes to get from start to finish                                          *
                                                                                                           *
    Functionality: the purpose of this function is to add a node and eddge to the graph to build           *
    the network.                                                                                           *
    *******************************************************************************************************/
    void add_edge( graph& g, int start, int finish, int length ) 
    {
      if ((int)g.size() <= (max)(start, finish))
      {
        g.resize( (max)(start,finish)+1 );
      }
      g[start].push_back( {finish, length} );
      g[finish].push_back( {start, length} );
    }
    
    using path = vector<int>;
    
    /**************************************************************************************
    Creating a struct to hold the result of the shortest path based on weig               *
    int distance, holds an integer value of the shortest combined path                    *
    path p,is a vector of ints that holds all the nodes that are used in the              *
    shortest path                                                                         *
    **************************************************************************************/
    struct result 
    {
      int distance;
      path p;
    };

    /****************************************************************************************************
    Function: dijkstra                                                                                  *
    Variables:                                                                                          *
    graph &graph, is a graph passed by reference that acts as the Network                               *
    int source, the source node to where the user specifies                                             *
    int target, the target/destination node to where the user specifies                                 *
    vector <int> & power, a power vector passed by reference holding the power to each individual node  *
    vector <int> & powerIndex, a vector of indexes to hold the possible "edge to" values, this vector   *
    contains all possible next moves.                                                                   *
                                                                                                        *
    Functionality:                                                                                      *
    If the power at all possible moves is the same it will take the shortest path based on the edge     *
    weights. However, if the shortest path on the edge weights has a less power remaining then a move   *
    that has a larger weight cost;the algorithm will take the path that has the highest power remaining *
    but also removes the least amount of power from the system. The only nodes that lose power are the  *
    source nodes and nodes in the path. The target node does not lose any power for receiving a packet  *
    ****************************************************************************************************/

    result dijkstra(const graph &graph, int source, int target, vector <int> & power, vector <int> & powerIndex) {
      
      /**************************************************************************************************
      variable declarations:                                                                            *
      min_distance, vector of intance to contain the minimum distance fro source to target              *
      active_vertices, a pair that connects the current shortest path together of the active vertices   *
      or the possible paths                                                                             *
      **************************************************************************************************/

      vector<int> min_distance( graph.size(), INT_MAX );
      min_distance[ source ] = 0;
      set< pair<int,int> > active_vertices;
      active_vertices.insert( {0,source} );


      //while there are vertices actives and target has not been reached
      while (!active_vertices.empty()) 
      {
        //set the vetices to the beginning, use -> second to get the "edge to value"
        int where = active_vertices.begin()->second;

        //checking to see if where the current node is the target, if it is good to back track
        if (where == target)
        {

          //get the cost and create a path from where target
          int cost = min_distance[where];
          path p{where};

          //check to see if we have hit the source, otherwise continue in the graph
          while (where != source) {
            
            //ensures that the next variable is set to where in case we are at or 1 away from source
            int next = where;

            //in range for loop to look at all edges in the graph from current position
            for (edge e : graph[where])
            {
              //push back all posible moves in to the power index
              powerIndex.push_back(e.to);

              //if there is one move continue
              if (min_distance[e.to] == INT_MAX)
              {
                continue;
              }
              
              //if there are multiple moves that do not equal min_distance and the power at shortest move is greater continue
              if (e.length + min_distance[e.to] != min_distance[where] && power[powerIndex[0]] <= power[powerIndex[1]])
              {
                continue;
              }

              //decerement the power based on weight
              power[e.to] = power[e.to] - e.length;

                //set power to 0 if negative as we cannot have negative power
                if(power[e.to]<=0)
                {
                  power[e.to]=0;
                }

              //finalize next move and push it into the shortest path
              next = e.to;
              p.push_back(next);
              
              
              break;
            }

            //if where equals next break as the source will have been met
            if (where==next)
            {
              break;
            }
            //otherwise continue moving in the path;
            where = next;
          }

          //reverse the path of p as the algorithm backtracked from the target
          reverse( p.begin(), p.end() );

          //return the result with the cost and the move
          return {cost, move(p)};
        }

        // used to finalize the cost and desired path for shortest edge if one move
        active_vertices.erase( active_vertices.begin() );
        for (auto ed : graph[where]) 
          if (min_distance[ed.to] > min_distance[where] + ed.length) 
          {
            active_vertices.erase( { min_distance[ed.to], ed.to } );
            min_distance[ed.to] = min_distance[where] + ed.length;
            active_vertices.insert( { min_distance[ed.to], ed.to } );
          }
      }
      //returns INT_MAX if node doesn't exist 
      return {INT_MAX};
    }
    
    int main()
    {
      //variable declarations
      graph g;
      int choice,src,dest,weight,nodecount = 0;
      vector <int> power;
      vector <int> powerIndex;
      vector <int> nodes;
      
    //initial simulation menu
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
    //choice 3 is create your own network, details on how to do so in techinical report
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
  //menu select once a network has been created
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
        auto distance = dijkstra(g,src,dest,power,powerIndex);
        
        cout<<endl<<"Route Taken: ";
       
        //used to find all the nodes in the shortest path
        for (int i:distance.p) 
        {
          cout << i << " ";
          nodes.push_back(i);
        }

        //checking if all nodes are still online
        for (int i=0; i<power.size();i++)
        {
          if(power[i]<=0)
          {
            cout<<endl<<"No Power Remaining in node: "<<i<<" network is down, ending program"<<endl;
            
            for(int j=0;j<power.size();j++)
            {
              cout<<"Final Power remaining at node "<<j+1<<":"<<power[j]<<endl;
            }

            selection=3;
          }
        }

        nodes.clear();
        powerIndex.clear();
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