//
//  main.cpp
//  gorkemguzeler_the4
//
//  Created by gorkemg on 10.08.2020.
//  Copyright © 2020 Gorkem Guzeler. All rights reserved.
//
#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <climits>
#include "Header.h"
#include "lowest_queue.h"
#include <thread>
#include <mutex>
#include <cmath>

using namespace std;

mutex coutMutex;

//each thread finds three districts with the lowest dissimilarity
void find_lowest(dynamicQueue &data_queue , lowest_queue &lowest_queue ,const queue_node &user_node)
{
    //search data queue with multithreads find 3 district with lowest dissimilarity
    queue_node n;
    int order = 0;
    
    vector<vector<double> > lowest_three(3, vector<double>(3));
    lowest_three[0][2] = INT_MAX;
    lowest_three[1][2] = INT_MAX;
    lowest_three[2][2] = INT_MAX;
    
    while(!data_queue.isEmpty())
    {
        coutMutex.lock();
        data_queue >> n;
        coutMutex.unlock();
        
        //comparison:
        double dissimilarity = sqrt(pow((abs(user_node.MedianHouseAge - n.MedianHouseAge)/26),2) + pow((abs(user_node.AverageRooms - n.AverageRooms)/10),2)+ pow((abs(user_node.AverageBedrooms - n.AverageBedrooms)/4),2) + pow((abs(user_node.Latitude - n.Latitude)),2) + pow((abs(user_node.Longitude - n.Longitude)),2)) ;
        
        //swap operations in the matrix in order to place newcomers correctly.
        if (lowest_three[0][2] > dissimilarity)
        {
           
            lowest_three[2][0]  =   lowest_three[1][0];
            lowest_three[2][1]  =   lowest_three[1][1];
            lowest_three[2][2]  =   lowest_three[1][2];
            
            lowest_three[1][0]  =   lowest_three[0][0];
            lowest_three[1][1]  =   lowest_three[0][1];
            lowest_three[1][2]  =   lowest_three[0][2];
            
            lowest_three[0][0]  = n.Id;
            lowest_three[0][1]  = n.MedianPrice;
            lowest_three[0][2]  = dissimilarity;
        }
        
        else if (lowest_three[1][2] > dissimilarity)
        {
          
            lowest_three[2][0]  =   lowest_three[1][0];
            lowest_three[2][1]  =   lowest_three[1][1];
            lowest_three[2][2]  =   lowest_three[1][2];
            
            lowest_three[1][0]  = n.Id;
            lowest_three[1][1]  = n.MedianPrice;
            lowest_three[1][2]  = dissimilarity;
        }
        
        else if (lowest_three[2][2] > dissimilarity)
        {
            lowest_three[2][0]  = n.Id;
            lowest_three[2][1]  = n.MedianPrice;
            lowest_three[2][2]  = dissimilarity;
        }
  

        if(order%1000 == 0 && order != 0)
        {
            coutMutex.lock();
            cout << "Thread with id " << this_thread::get_id() << " is processing its " << order << "th item." << endl;
            coutMutex.unlock();
        }
        order++;
    }
    
    coutMutex.lock();
    for (int i = 0 ; i < lowest_three.size() ; i++)
    {
        lowest_node myNode(lowest_three[i][0],lowest_three[i][1], lowest_three[i][2]);
        lowest_queue << myNode;
    }
    coutMutex.unlock();
    
    coutMutex.lock();
    cout << "Thread with id " << this_thread::get_id() << "is exiting." << endl;
    coutMutex.unlock();
}

//this function takes 3*thread num districts as parameter in order to find 3 lowest dissimilarity.
void lowest_output(lowest_queue &lowest_queue)
{
    lowest_node m;
    class lowest_queue temp;
    
    lowest_node lowest_1(0,0,INT_MAX);
    lowest_node lowest_2(0,0,INT_MAX);
    lowest_node lowest_3(0,0,INT_MAX);
    
    while(!lowest_queue.isEmpty())
    {
        coutMutex.lock();
        lowest_queue >> m;
        coutMutex.unlock();
        
        if (lowest_1.Dissimilarity > m.Dissimilarity)
        {
            lowest_1 = m;
        }
        
        temp << m;
    }
    while(!temp.isEmpty())
    {
        
        temp >> m;
       
        if (lowest_2.Dissimilarity > m.Dissimilarity && m.Dissimilarity != lowest_1.Dissimilarity)
        {
            lowest_2 = m;
        }
        
        lowest_queue << m;
    }
    while(!lowest_queue.isEmpty())
    {
        
        lowest_queue >> m;
    
        if (lowest_3.Dissimilarity > m.Dissimilarity &&  m.Dissimilarity != lowest_1.Dissimilarity &&  m.Dissimilarity != lowest_2.Dissimilarity)
        {
            lowest_3 = m;
        }
        
        temp << m;
    }
    
    cout << endl;
    cout << "Closest three districts in terms of features have the following median prices:" << endl;
    cout << endl;
    
    cout << "Closest District 1" << endl;
    cout << "--------" << endl;
    cout << "Id: " << lowest_1.Id << endl;
    cout << "Median Price: ​" << lowest_1.MedianPrice << endl;
    cout << "Calculated Dissimilarity Metric: ​" << lowest_1.Dissimilarity  << endl;
    
    cout << endl;
    
    cout << "Closest District 2" << endl;
    cout << "--------" << endl;
    cout << "Id: " << lowest_2.Id << endl;
    cout << "Median Price: ​" << lowest_2.MedianPrice << endl;
    cout << "Calculated Dissimilarity Metric: ​" << lowest_2.Dissimilarity << endl;
    
    cout << endl;
    
    cout << "Closest District 3" << endl;
    cout << "--------" << endl;
    cout << "Id: " << lowest_3.Id << endl;
    cout << "Median Price: ​" << lowest_3.MedianPrice << endl;
    cout << "Calculated Dissimilarity Metric: ​" << lowest_3.Dissimilarity << endl;
    
    cout << endl;
    double average_mp = (lowest_3.MedianPrice + lowest_2.MedianPrice + lowest_1.MedianPrice)/3;
    cout << "Average median price of three closest districts: ​" << average_mp << endl;
}

int main()
{
    string line;
    
    ifstream data_input;
    
    string s = "data.tsv";
    
    data_input.open(s.c_str());
    
    
    dynamicQueue data_queue;
    
    lowest_queue lowest_queue;
    
    double Id, MedianHouseAge, AverageRooms, AverageBedrooms, Latitude, Longitude, MedianPrice ;
    
    getline(data_input, line); //skip the first line
    
    istringstream str(line);
    string k;
    
    
    while(getline(data_input, line)) //starting from the second line add nodes to queue until the eof.
    {
        
        istringstream str(line);
        
        while(str >> Id >> MedianHouseAge >> AverageRooms >> AverageBedrooms >> Latitude >> Longitude >> MedianPrice)
        {
            queue_node new_node( Id, MedianHouseAge, AverageRooms, AverageBedrooms, Latitude, Longitude, MedianPrice);
            
            data_queue  << new_node;
        }
    }
    
    //user inputs
    double thread_num, house_age, room_num, bedroom_num, latitude_num , longitude_num ;
    
    cout << data_queue.get_num_of_elements() << " districts have been loaded." << endl;
    
    cout << "How many threads?: " << endl;
    cin >> thread_num;
    
    cout << "What is the age of the house?: " << endl;
    cin >> house_age;
    
    cout << "How many rooms does the house have?: " << endl;
    cin >> room_num;
    
    cout << "How many bedrooms does the house have?: " << endl;
    cin >> bedroom_num;
    
    cout << "What is the latitude of the house?: ​" << endl;
    cin >> latitude_num;
    
    cout << "What is the longitude of the house?: " << endl;
    cin >> longitude_num;
    
    queue_node user_node(thread_num , house_age, room_num, bedroom_num, latitude_num, longitude_num,0 );//**thread_num is put instead of id**
    
    thread threads[(int)thread_num];
    for (int i=0; i < thread_num; i++){
        threads[i] = (thread(&find_lowest, ref(data_queue), ref(lowest_queue), ref(user_node) ));
    }
    
    for (int i=0; i < thread_num; i++){
        threads[i].join();
    }
    
    lowest_output(lowest_queue);
    
    return 0;
}
