//
//  main.cpp
//  gorkemguzeler_the2
//
//  Created by gorkemg on 13.07.2020.
//  Copyright © 2020 Gorkem Guzeler. All rights reserved.
//

#include <iostream>

using namespace std;

struct doubly_node
{
    
    doubly_node* left;
    string party_name;
    int vote_num;
    doubly_node* right;
    
    
    doubly_node(doubly_node* l=nullptr, string m="" ,int i=0, doubly_node* r=nullptr): left(l), party_name(m) ,vote_num(i), right(r) {}
    
};


void make_choice()
{
    cout << "Please make a choice from the following menu: " << endl;
    cout << "1. Enter votes," << endl;
    cout << "2. Remove votes," << endl;
    cout << "3. Display current standings (from best to worst)," << endl;
    cout << "4. Display current standings (from worst to best)," << endl;
    cout << "5. Finish." << endl;
    cout << "" << endl;
}

void add_votes(doubly_node* &head,string name ,int number)
{
    
    doubly_node* p = head;
    if(head == nullptr)
    {
        head = new doubly_node(nullptr, name, number, nullptr);
    }
    
    else
    {
        while (p->party_name != name && p->right != nullptr )
        {
            p = p->right;
            
        }
        
        if(p->party_name == name) // if there is already a node called name, we add number and change the position
        {
            p->vote_num = p->vote_num + number ;
            //check if new vote number is higher than left nodes?
            doubly_node* temp = p;
            while (temp->left != nullptr && temp->left->vote_num < p->vote_num)
            {
                temp = temp->left;
            }
      
            //if vote numbers are equal look at the alphabetic order, arrange temp
            if(temp->left != nullptr && temp->left->vote_num == p->vote_num )
            {
                while(temp->left != nullptr && temp->left->party_name > p->party_name && temp->left->vote_num == p->vote_num ) // alfabe check
                {
                    temp = temp->left;
                    
                }
                
            }
            
            
            //if p and temp are not on the same node,
            if(temp->party_name != p->party_name)
            {
                if(p->left != nullptr )
                    p->left->right = p->right;
                
                if(p->right != nullptr )
                    p->right->left = p->left;
                
                p->right = temp;
                p->left = temp->left;
                temp->left = p;
                
                
                if(p->left != nullptr)
                {
                    p->left->right = p;
                }
                
                
                if(head->left != nullptr) //check if head is changed
                    head = head->left;
                
            }
        }
        else //add a new node since there is no node with a given party name
        {
            if (head->vote_num <= number) //insert a node next to head
            {
                
                if(head->vote_num == number)
                {
                    
                    doubly_node* temp4 ;
                    temp4= head;
                    while(temp4->right != nullptr && temp4->party_name  < name && temp4->vote_num == number)
                        temp4= temp4->right;
                    
                    
                    doubly_node * temp3 = new doubly_node(temp4->left ,name ,number,temp4); //inserting left side of temp4
                    
                    if(temp4->left != nullptr)
                        temp4->left->right = temp3;
                    
                    temp4->left = temp3;
                }
                
                
                else //insert left of head since it is bigger
                {
                    doubly_node* newNode = new doubly_node(nullptr ,name, number, head);
                    head->left = newNode;
                    head = newNode;
                }
                
            }
            
            
            else{ //insert a node to the middle or to the end
                p = head;
                while (p->right != nullptr && p->right->vote_num > number)
                {
                    p = p->right;
                }
                
                
                while(p->right != nullptr && p->right->party_name < name && p->right->vote_num == number ) // alfabe check
                {
                    p = p->right;
                    
                }
                doubly_node * store_next2;
                store_next2= p->right;
                p->right = new doubly_node(p ,name ,number,p->right);
                if (store_next2 != nullptr)
                    store_next2->left = p->right;
                
            }
        }
       
    }
    
}

void remove_votes(doubly_node * to_be_deleted, doubly_node * &head)
{
    
    doubly_node * ptr;
    doubly_node * k;
    doubly_node * m;
    
    m=head;
    
    while(m != nullptr && m->right != nullptr)
        m = m->right;
    
    if (to_be_deleted->party_name == m->party_name) // If the node to be deleted is the last node
    {
        cout << "Success!" << endl;
        cout << endl;
        m->vote_num = m->vote_num - to_be_deleted->vote_num;
        
        if (m->vote_num <= 0)
        {
            if(head->right == nullptr)
            {
                head = nullptr;
                delete head;
            }
            
            else
            {
                k = m;
                if(m->left!=nullptr)
                    m = m->left;
                m->right = nullptr;
                delete k;
            }
            
        }
        
    }
    else{  // If the node to be deleted is not at the end
        ptr = head;
        while (ptr->party_name != to_be_deleted->party_name && ptr->right != nullptr ) //nullptr -> error
            ptr = ptr->right;
        
        
        if (to_be_deleted->party_name == ptr->party_name)  //go to the removal part
        {
            cout << "Success!" << endl;
            cout << endl;
            ptr->vote_num = ptr->vote_num - to_be_deleted->vote_num;
            
            if(ptr->vote_num <= 0) //if vote number is equal or lower than 0, delete ptr
            {
                if(ptr->left == nullptr)
                    head = head->right;
                
                if(ptr->left != nullptr)
                    ptr->left->right = ptr->right;
                if(ptr->right != nullptr)
                    ptr->right->left = ptr->left;
                
                ptr->left = nullptr;
                ptr->right = nullptr;
                
                delete ptr;
            }
            
            else //change the location according to order
            {
                
                doubly_node* temp = ptr;
                
                while (temp->right != nullptr && temp->right->vote_num > ptr->vote_num)
                {
                    temp = temp->right;
                }
                
                
                while(temp->right != nullptr && temp->right->party_name < ptr->party_name && temp->right->vote_num == ptr->vote_num ) // alfabe check
                {
                    temp = temp->right;
                    
                }

                //if ptr and temp are not on the same node, inserting right side of temp
                if(ptr->party_name != temp->party_name)
                {
                    if(ptr->left == nullptr)
                        head = head->right;
                    
                    if(ptr->left != nullptr)
                        ptr->left->right = ptr->right;
                    if(ptr->right != nullptr)
                        ptr->right->left = ptr->left;
                    
                    ptr->right = temp->right;
                    ptr->left = temp;
                    
                    if(ptr->right != nullptr)
                        temp->right->left = ptr;
                    temp->right = ptr;
                    
                }
          
            }
            
        }
        else //Given party does not exist.
        {
            cout << "Given party does not exist." << endl;
            cout << endl;
        }
        
    }
}


void best_to_worst(doubly_node * head)
{
    
    //if there is no node
    if (head == nullptr )
    {
        cout << "There aren't any records." << endl;
        cout << endl;
    }
    
    else
    {
        doubly_node* temp = head;
    
        while (temp->right != nullptr)
        {
            cout <<  temp->party_name << "\t" << temp->vote_num << endl;
            temp = temp->right;
        }
        cout <<  temp->party_name << "\t" << temp->vote_num << endl;
        
        cout << endl;
    }
    
}

void worst_to_best(doubly_node * head)
{
    //if there is no node
    if (head == nullptr)
    {
        cout << "There aren't any records." << endl;
        cout << endl;
    }
    
    else
    {
        doubly_node * ptr = head;
        while(ptr->right != nullptr)
            ptr = ptr->right;
        
        doubly_node *temp = ptr;
        
        while (temp!=nullptr){
            cout << temp->party_name << "\t" << temp->vote_num;
            cout << endl;
            temp = temp->left;
        }
        cout << endl;
        
    }
}
// delete all nodes at the end
void delete_doubly_nodes(doubly_node* &head){
    doubly_node* temp;
    while (head != nullptr){
        temp = head->right;
        delete head;
        head = temp;
    }
}


int main()
{
    int answer,vote_number;
    string party_name;
    
    cout << "Welcome to the Election Sheet." << endl;
    
    make_choice();
    
    cin >> answer;
    
    doubly_node* head = nullptr;
    
    doubly_node * to_be_deleted = new doubly_node();
    
    while(answer != 5)
    {
        
        if (answer == 1)
        {
            cout << endl;
            cout << "Please enter party name and votes to add: " ;
            
            
            cin >> party_name >> vote_number ;
            
            cout << "Success!" << endl;
            cout << endl;
            
            
            add_votes(head, party_name , vote_number);
            
            make_choice();
            
            cin >> answer;
         
        }
        
        else if (answer == 2)
        {
            cout << endl;
            cout << "Please enter party name and votes to remove: " ;
            cin >> party_name >> vote_number ;
            
            to_be_deleted->party_name = party_name;
            to_be_deleted->vote_num = vote_number;
            
            remove_votes(to_be_deleted , head);
            
            make_choice();
            
            cin >> answer;
       
        }
        
        else if (answer == 3)
        {
            cout << endl;
            best_to_worst(head);
            
            make_choice();
      
            cin >> answer;
   
        }
        
        else if (answer == 4)
        {
            cout << endl;
            worst_to_best(head);
            
            make_choice();
            
            cin >> answer;
          
        }
        
        else
        {
            cout <<  "Please enter a valid option!" << endl; ;
            
            cout << endl;
            
            cin >> answer;
            
        }
        
    }
    
    //delete all nodes
    delete_doubly_nodes(head);
    
    cout << endl;
    cout <<  "Program exiting.." << endl;
    return 0;
}
