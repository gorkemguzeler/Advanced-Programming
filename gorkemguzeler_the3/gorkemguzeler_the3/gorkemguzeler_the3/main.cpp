//
//  main.cpp
//  gorkemguzeler_the3
//
//  Created by gorkemg on 30.07.2020.
//  Copyright © 2020 Gorkem Guzeler. All rights reserved.
//
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <climits>

#include "queue.h"

using namespace std;

int next_queue_index( const vector<dynamicQueue> &routers , const vector<string> &forward_connections )
{
    //we will send the packet to the router that has the least populated queue, among the connected routers of the current router. If two or more connected routers have the same queue size, the packet is sent to the one that occurs the first in the respective line of the current router.
    
    int min_queue = INT_MAX ;
    int r = 0, index_num = INT_MAX;
    
    for (int i=0; i<forward_connections.size() ; i++)
    {
        if(forward_connections[i] == "T") //if it is T, go to last queue
        {
            
            if (routers[routers.size()-1].get_num_elements() < min_queue) //eşitlik durumunda ilk gelen alınır
            {
                min_queue = routers[routers.size()-1].get_num_elements();
                r = (int)routers.size()-1 ;
            }
        }
        
        else //if it is an integer, find least populated connection
        {
            index_num = stoi(forward_connections[i]) ; //atoi, strutils
            index_num--;
            
            if (routers[index_num].get_num_elements() < min_queue)
            {
                min_queue = routers[index_num].get_num_elements();
                r = index_num;
            }
        }
    }
    return r;
}

int main()
{
    string router_name, line;
    string packet_name;
    ifstream packet_input , router_input;
    
    
    cout << "Please enter the name of the file for routers: ";
    cin >> router_name ;
    router_input.open(router_name.c_str());
    
    
    cout << "Please enter the name of the file for packets: ";
    cin >> packet_name;
    packet_input.open(packet_name.c_str());
    
    cout << "Packets are displayed in the order they arrive in the terminal router, along with their router visit history:" << endl;
    
    int router_num;
    
    getline(router_input, line);
    {
        istringstream input(line);
        input >> router_num;
    }
    
    vector<dynamicQueue> routers(router_num + 1); //for T queue
    
    vector<vector<string> > connections;
    
    vector<string> m;
    
    string ch , dash;
    string forward_connection;
    
    while(getline(router_input, line)) //creating connections matrix by pushing back m vectors
    {
        istringstream str(line);
        
        while(str >> ch >> dash)
        {
            
            while(str >> forward_connection)
            {
                m.push_back(forward_connection);
            }
            
            connections.push_back(m);
            m.clear();
            
        }
    }
    
    int index_num1 ;
    while(getline(packet_input, line)) //reading packets file while pushing back E and id. then, place them to their first queue.
    {
        istringstream str2(line);
        string word;
        string w;
        
        while(str2 >> word)
        {
            w = word;
            Packet word;
            word.id = w;
            (word.routerHistory).push_back("E");
            
            if(connections.size() != 0)
            {
                index_num1 = next_queue_index(routers,connections[0]);
                index_num1++;
                
                if(index_num1 == routers.size())
                {
                    string m = "T" ;
                    (word.routerHistory).push_back(m);
                    routers[routers.size()-1] << word ;
                }
                else
                {
                    (word.routerHistory).push_back(to_string(index_num1));
                    index_num1--;
                    routers[index_num1] << word ;
                }
            }
        }
    }
    
    Packet packets;
    vector<string> forward_connections;
    
    int k = 0;
    
    for(int i=0 ; i < routers.size() - 1 ;i++) //since we do not want to dequeue T (last element of routers).
    {
        while(! routers[i].isEmpty())
        {
            
            for(int p = 0; p < connections[i+1].size(); p++)
            {
                forward_connections.push_back(connections[i+1][p]);
            }
            
            routers[i] >> packets;
            if (forward_connections.size() != 0)
            {
                k = next_queue_index(routers,forward_connections);
                k++;
                
                if(k == routers.size())
                {
                    string m = "T" ;
                    (packets.routerHistory).push_back(m);
                    routers[routers.size()-1] << packets ;
                }
                else
                {
                    (packets.routerHistory).push_back(to_string(k));
                    k--;
                    routers[k] << packets ;
                }
            }
            forward_connections.clear();
        }
    }
    
    //T queue cout
    cout << routers[routers.size()-1];
    
    return 0;
}
