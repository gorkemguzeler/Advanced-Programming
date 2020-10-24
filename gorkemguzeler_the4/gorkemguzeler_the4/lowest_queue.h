//
//  lowest_queue.h
//  gorkemguzeler_the4
//
//  Created by gorkemg on 13.08.2020.
//  Copyright © 2020 Gorkem Guzeler. All rights reserved.
//

#ifndef lowest_queue_h
#define lowest_queue_h

#include <iostream>

using namespace std;

struct lowest_node{
    double Id;
    double MedianPrice;
    double Dissimilarity;
    lowest_node* next;
    
    lowest_node(double i= 0, double p=0, double d=0 , lowest_node* n=nullptr): Id(i), MedianPrice(p), Dissimilarity(d) ,next(n) {}
};


class lowest_queue{
public:
    lowest_queue(void);
    ~lowest_queue(void); //destructor
    bool isEmpty(void) const;
//    void clear(void);
    void operator << (lowest_node myPacket);   //enqueue
    void operator >> (lowest_node &  newPacket);   //dequeue
    int get_num_of_elements();
    void get_three_lowest();
    
private:
    lowest_node* front;
    lowest_node* rear;
    int num_of_elements = 0;
};

lowest_queue::lowest_queue(void) {
    front = nullptr;
    rear = nullptr;
//    cout << "Constructor is invoked" << endl;
}

lowest_queue::~lowest_queue(void){
//    cout << "Destructor is invoked" << endl;
    lowest_node n;
    while(!isEmpty())
    {
        *this >> n;
    }
    rear = nullptr;
    front = nullptr;
}

int lowest_queue::get_num_of_elements()
{
    return num_of_elements;
}

void lowest_queue::get_three_lowest()
{
    //queue yu gez en küçük üçlüyü bastır
}

bool lowest_queue::isEmpty(void) const{
    return front == nullptr;
}

//void lowest_queue::clear(void){
//    lowest_node n;
//
//    while(!isEmpty())
//        *this >> n;
//
//    rear = nullptr;
//}

void lowest_queue::operator << (lowest_node myPacket){ // enqueue
    if (isEmpty()){
        front = new lowest_node;
        front->Id = myPacket.Id;
        front->MedianPrice = myPacket.MedianPrice;
        front->Dissimilarity = myPacket.Dissimilarity;
        
        rear = front;
    }
    else{
        rear->next = new lowest_node;
        rear->next->Id = myPacket.Id;
        rear->next->MedianPrice = myPacket.MedianPrice;
        rear->next->Dissimilarity = myPacket.Dissimilarity;
        
        rear= rear->next;
    }
    num_of_elements++;
}

void lowest_queue::operator >> (lowest_node & newPacket){ // dequeue
    if (isEmpty())
    {
//        cout << "Queue is empty" << endl;
    }
    else
    {
        newPacket.Id = front->Id;
        newPacket.MedianPrice = front->MedianPrice;
        newPacket.Dissimilarity = front->Dissimilarity;
        
        lowest_node* temp = front;
        front = front->next;
        delete temp;
        num_of_elements--;
        
        if(num_of_elements == 0)
        {
            rear = nullptr;
            front = nullptr;
        }
    }
}

#endif /* lowest_queue_h */
