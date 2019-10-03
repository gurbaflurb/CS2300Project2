/*
Sean Chen
Last modified: Sept. 22, 2019
Written for CS 2300 Sec. 002
source.cpp

This program is given a file that contains a target boxs' lower left coordinate, target box size, and info on describing a line in parametric form.
Using this info, the program will then plot the line using character output.
Input files are formatted in the form: llx lly d p1 p2 v1 v2.
where, 
(llx, lly) are the lower left coordinates of the target box,
d is the size of the coordinate box (in both coordinates),
p1, p2 are a point on the line, and  
v1, v2 are the vector on the line.  
*/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <tuple>

/*
readData function
This function takes in a string for the file path and returns seven integers as a tuple
*/
std::tuple<int, int, int, int, int, int, int> 
           readData(std::string filePath)
{
    std::fstream file;
    std::string line;

    int llx, lly, d, p1, p2, v1, v2;
    file.open(filePath);

    if(file.is_open())
    {
        std::getline(file, line, ' ');
        llx = stoi(line);
        std::getline(file, line, ' ');
        lly = stoi(line);
        std::getline(file, line, ' ');
        d = stoi(line);
        std::getline(file, line, ' ');
        p1 = stoi(line);
        std::getline(file, line, ' ');
        p2 = stoi(line);
        std::getline(file, line, ' ');
        v1 = stoi(line);
        std::getline(file, line, ' ');
        v2 = stoi(line);
    }
    else
    {
        std::cout << "Failed to open file!\nQuitting!" << std::endl;
        throw std::invalid_argument("Missing or Invalid file");
    }
    file.close();
    return std::make_tuple(llx, lly, d, p1, p2, v1, v2);
}

/*
checkPoint function
This function takes in a known point(px py), and  a point to test (x and y) and a vector (v1, v2)
*/
bool checkPoint(int px, int py, int x, int y, int v1, int v2)
{
    if(v1 == 0)
    {
        if(px == x)
        {
            return true;
        }  
    }
    else
    {
        double slope = float(v2)/float(v1);
        int b = py - (slope * px);
        if(0 == (slope*x)+b-y || (slope*x)+b-y < 0.0001 && (slope*x)+b-y > -0.0001)
        {
            return true;
        }
    }
    return false;
}

/*
printBoard function
This function takes in the data that is read from readData and prints the board to the screen
*/
void printBoard(int llx, int lly, int d, int p1, int p2, int v1, int v2)
{
    for(int cY = lly + d; cY > lly-1; cY--)
    {
        if(cY > 9 || cY < 0)
        {
            if(cY < -9)
            {
                std::cout << cY;
            }
            else
            {
                std::cout << cY << ' ';
            }
        }
        else
        {
            std::cout << ' ' << cY << ' ';
        }
        
        for(int cX = llx; cX < llx+d+1; cX++)
        {
            if(checkPoint(p1, p2, cX, cY, v1, v2))
            {
                std::cout<< "*";
            }
            else if(cY == 0)
            {
                std::cout << '-';
            }
            else if(cX == 0)
            {
                std::cout << '|';
            }
            else
            {
                std::cout << ' ';
            }
            
        }
        std::cout << std::endl;
    }
    if(v1 == 0)
    {
        std::cout << "Implicit Form: y="<<v2<<'/'<<v1<<"x+0"<< std::endl;
    }
    else
    {
        float b = p2 - (float(v2)/float(v1) * p1);
        std::cout << "Implicit Form: y="<<v2<<'/'<<v1<<"x+"<<b<< std::endl;
    }
}

int main()
{
    int llx, lly, d, p1, p2, v1, v2;
    std::cout<<"Board 1" << std::endl;
    std::tie(llx, lly, d, p1, p2, v1, v2) = readData("line1-1.txt");
    printBoard(llx, lly, d, p1, p2, v1, v2);

    std::cout<<"Board 2" << std::endl;
    std::tie(llx, lly, d, p1, p2, v1, v2) = readData("line2.txt");
    printBoard(llx, lly, d, p1, p2, v1, v2);

    std::cout<<"Board 3" << std::endl;
    std::tie(llx, lly, d, p1, p2, v1, v2) = readData("line3.txt");
    printBoard(llx, lly, d, p1, p2, v1, v2);

    std::cout<<"Board 4" << std::endl;
    std::tie(llx, lly, d, p1, p2, v1, v2) = readData("line4.txt");
    printBoard(llx, lly, d, p1, p2, v1, v2);

    std::cout<<"Board 5" << std::endl;
    std::tie(llx, lly, d, p1, p2, v1, v2) = readData("line5.txt");
    printBoard(llx, lly, d, p1, p2, v1, v2);

    return 0;
}