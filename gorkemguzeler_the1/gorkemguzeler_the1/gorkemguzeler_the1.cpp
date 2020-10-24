//
//  main.cpp
//  gorkemguzeler_the1
//
//  Created by gorkemg on 3.07.2020.
//  Copyright © 2020 gorkemg. All rights reserved.
//  Gorkem Guzeler

//This program is a kind of puzzle. It checks whether the input word is in puzzle and calculate the points according to your performance.

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

//this function prints the matrix
void display_matrix(vector<vector<char> > &matrix)
{
    if(matrix.size() > 0)
    {
        for(int i = 0  ; i <= matrix.size()-1 ; i++)
        {
            if(matrix[0].size()>1)
            {for(int j = 0 ; j <= matrix[0].size()-2 ; j++)
            {
                cout<< matrix[i][j] << " ";
            }}
            cout<< matrix[i][matrix[0].size()-1];
            cout << endl;
            
        }
    }
}
//this function is used to capitalize all the letters of word input
void check_capitalize(string & s)
{
    for(int i=0; i<= s.length()-1 ; i++) {
        
        if(s[i]>= 'a' && s[i]<= 'z')
        {
            s[i]= s[i] + ('A' - 'a');
        }
    }
}

////this function search the word input in the puzzle and whenever it finds the word in any direction it makes the boolean variable true.
void puzzle_search(vector<vector<char> > &matrix, string word_input , bool &regular_horizontal, bool &reverse_horizontal,bool &regular_vertical, bool &reverse_vertical)
{
    int count = 1 ;
    int m = 0 ;
    int r_h, t_h, r_v, t_v;
    int rowErasePosition, columnErasePosition;
    int finish_searching;
    
    finish_searching = 0 ;
    //check if the word is found in regular horizontal direction
    for(int i = 0  ; i <= matrix.size()-1 && finish_searching ==0 ; i++)
    {
        for(int j = 0 ; j <= matrix[0].size()-1 && finish_searching ==0 ; j++)
        {
                     
            m = 0 ;
            
            if(matrix.size() != 0 && matrix[i][j] == word_input[m])
            {
                count = 1;
                r_h = j ;
                
                while(count <= word_input.length())
                {
                    
                    m++ ;
                    r_h++ ;
                    
                    if(r_h < matrix[0].size()){
                        if(matrix[i][r_h] == word_input[m])
                        {
                            count++ ;
                        }
                        else
                            count = 1250 ;
                    }
                    else{
                        count =1250;
                    }
                    
                    
                    
                    if(count == word_input.length())
                    {
                        
                        //erase row
                        rowErasePosition = i;
                        matrix.erase(matrix.begin() + rowErasePosition );
                        regular_horizontal = true;
                        finish_searching=1;
                        count = 1250;
                      
                    }
                }
            }
        }
    }
    //check if the word is found in reverse horizontal direction
    for(int i = 0  ; i <= matrix.size()-1 && finish_searching ==0 ; i++)
    {
        for(int j = 0 ; j <= matrix[0].size()-1 && finish_searching ==0 ; j++)
        {
            
            
            m = 0 ;
            
            if(matrix.size() != 0 && matrix[i][j] == word_input[m] && regular_horizontal == false)
            {
                
                count = 1;
                t_h = j ;
                
                while(count <= word_input.length())
                {
                    
                    m++ ;
                    t_h-- ;
                    
                    if(t_h >= 0 ){
                        if(matrix[i][t_h] == word_input[m])
                        {
                            count++ ;
                        }
                        else
                            count = 1250 ;
                        
                    }
                    
                    else{
                        count =1250;
                    }
                    
                    
                    if(count == word_input.length())
                    {
                        
                        rowErasePosition = i;
                        
                        matrix.erase(matrix.begin() + rowErasePosition );
                        
                        reverse_horizontal = true;
                        finish_searching=1;
                        count = 1250;
                        
                    }
                }
            }
        }
    }
    
    //check if the word is found in regular vertical direction
    for(int i = 0  ; i <= matrix.size()-1 && finish_searching ==0 ; i++)
    {
        for(int j = 0 ; j <= matrix[0].size()-1 && finish_searching ==0 ; j++)
        {
            
            m = 0 ;
            
            if(matrix.size() != 0 && matrix[i][j] == word_input[m] && regular_horizontal==false && reverse_horizontal==false)
            {
                
                count = 1;
                r_v = i;
                
                while(count <= word_input.length())
                {
                    
                    m++ ;
                    r_v++ ;
                    
                    if(r_v < matrix.size())
                    {
                        
                        if(matrix[r_v][j] == word_input[m])
                        {
                            
                            count++ ;
                        }
                        else
                            count = 1250 ;
                    }
                    
                    else{
                        count =1250;
                    }
                    
                    
                    if(count == word_input.length())
                    {
                        
                        //erase column
                        columnErasePosition = j;
                        
                        for (int i = 0; i < matrix.size(); i++)
                        {
                            matrix[i].erase(matrix[i].begin() + columnErasePosition);
                        }
                        if(matrix[0].size() == 0){
                            int size = (int)matrix.size();
                            for(int i= 0; i < size ;i++)
                            {
                                rowErasePosition = 0 ;
                                matrix.erase(matrix.begin() + rowErasePosition );
                                
                            }
                            
                        }
                        
                        regular_vertical = true;
                        finish_searching=1;
                        count = 1250;
                        //return regular_vertical;
                        
                    }
                }
            }
        }
    }
    
    
    //check if the word is found in reverse vertical direction
    for(int i = 0  ; i <= matrix.size()-1 && finish_searching ==0 ; i++)
    {
        for(int j = 0 ; j <= matrix[0].size()-1 && finish_searching ==0 ; j++)
        {
            m = 0 ;
            
            if( matrix.size() != 0 && matrix[i][j] == word_input[m] && regular_horizontal==false && reverse_horizontal==false && regular_vertical==false)
            {
                // cout << "DEBUG3" <<endl;
                
                count = 1;
                t_v = i;
                
                while(count <= word_input.length())
                {
                    
                    m++ ;
                    t_v-- ;
                    
                    
                    if (t_v >= 0)
                    {
                        if(matrix[t_v][j] == word_input[m])
                        {
                            count++ ;
                        }
                        else
                            count = 1250 ;
                        
                    }
                    else{
                        count =1250;
                    }
                    
                    if(count == word_input.length())
                    {
                        //erase column
                        columnErasePosition = j;
                        
                        for (int i = 0; i < matrix.size(); i++)
                        {
                            matrix[i].erase(matrix[i].begin() + columnErasePosition);
                        }
                        
                        if(matrix[0].size() == 0){
                            int size = (int)matrix.size();
                            for(int i= 0; i < size ;i++)
                            {
                                rowErasePosition = 0 ;
                                matrix.erase(matrix.begin() + rowErasePosition );
                                
                            }
                            
                        }
                        
                        reverse_vertical= true;
                        finish_searching=1;
                        count = 1250;
                    }
                }
            }
        }
    }
};

//this function is used to get word input, to call check capitalize and puzzle_search functions and to give the required outputs.
int search_word( vector<vector<char> > &matrix) {
    
    string word_input ;
    int add_point ;
    cout << "Please enter a word: " ;
    cin >> word_input;
    
    check_capitalize(word_input) ;
    
    
    int points = 0 ;
    
    bool regular_horizontal;
    bool reverse_horizontal;
    bool regular_vertical;
    bool reverse_vertical;
    
    
    while(word_input.length() > 2 && matrix.size() > 0 )
    {
        //search that word in the matrix
        //if not found lose 5 points (false)
        
        int number_of_chars = (int)word_input.length() ;
        
        regular_horizontal = false;
        reverse_horizontal = false;
        regular_vertical = false;
        reverse_vertical = false;
        
        puzzle_search(matrix, word_input, regular_horizontal , reverse_horizontal, regular_vertical ,reverse_vertical) ;
        
        if (regular_horizontal == false)
        {
            if (reverse_horizontal == false )
            {
                if (regular_vertical == false)
                {
                    
                    if (reverse_vertical == false)
                    {
                        cout << "The word cannot be found in the puzzle." << endl;
                        cout << "5 points are deducted." << endl;
                        points= points - 5 ;
                        cout << "Total points: " << points << "." << endl;
                        
                    }
                    else
                    {
                        cout << "Word " << word_input << " is found." << endl;
                        add_point = (2*number_of_chars) + 2 ;
                        cout << add_point << " points are earned." << endl ;
                        points = points + add_point;
                        cout << "Total points: " << points << "." << endl;
                        
                        if( matrix.size() > 0 )
                        {cout << "Puzzle:" << endl;
                            display_matrix(matrix);}
                    }
                }
                else
                {
                    cout << "Word " << word_input << " is found." << endl;
                    add_point = number_of_chars + 2;
                    cout << add_point << " points are earned." << endl ;
                    points = points + add_point;
                    cout << "Total points: " << points << "." << endl;
                    
                    if( matrix.size() > 0 )
                    {cout << "Puzzle:" << endl;
                        display_matrix(matrix);}
                }
                
            }
            
            else
            {
                cout << "Word " << word_input << " is found." << endl;
                add_point = (2*number_of_chars);
                cout << add_point << " points are earned." << endl ;
                points = points + add_point;
                cout << "Total points: " << points << "." << endl;
                
                if( matrix.size() > 0 )
                {cout << "Puzzle:" << endl;
                    display_matrix(matrix);}
            }
        }
        else
        {
            cout << "Word " << word_input << " is found." << endl;
            add_point = (number_of_chars);
            cout << add_point << " points are earned." << endl ;
            points = points + add_point;
            cout << "Total points: " << points << "." << endl;
            if( matrix.size() > 0 )
            {cout << "Puzzle:" << endl;
                display_matrix(matrix);}
        }
        
        
        if( matrix.size() > 0 )
        {
            cout << "Please enter a word: " ;
            cin >> word_input;
            check_capitalize(word_input) ;
        }
        
    }
    
    //if puzzle cleared by user, add 20 points
    if(matrix.size() == 0){
        points = points + 20 ;
        cout << "Puzzle is cleared. 20 extra points are earned." << endl ;
        cout << "Total points: " << points << "." << endl;
    }
    
    
    cout << "Game has ended." << endl;
    cout << "Total points: " << points << "." << endl;
    
    return 0;
};


int main()
{
    string file_name, line;
    ifstream file_input;
    int row_num ;
    int column_num ;
    
    cout << "Welcome to Word Seek." << endl;
    
    cout << "Please enter a filename for the puzzle: " ;
    cin >> file_name;
    file_input.open(file_name.c_str());
    
    
    //while input file cannot be opened keep asking for a txt file
    
    while(file_input.fail())
    {
        cout << "Failed.." << endl;
        
        cout << "Please enter another filename for the puzzle: " ;
        cin >> file_name;
        file_input.open(file_name.c_str());
    }
    
    cout << "Success!" << endl;
    
    cout << "Puzzle:" << endl;
    
    getline(file_input, line);
    {
        istringstream input(line);
        input >> row_num >> column_num ;
    }
    
    vector<vector<char> > matrix;
    
    while(getline(file_input, line))
    {
        istringstream str(line);
        
        
        char ch;
        
        vector<char> temp;
        
        while(str >> ch)
        {
            
        temp.push_back(ch);
            
        }
        matrix.push_back(temp);
    }
    
    display_matrix(matrix);
    
    search_word(matrix);
    
    return 0;
}
