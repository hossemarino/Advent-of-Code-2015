#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int grid[1000][1000];

int on = 1;
int off = 0;
int count = 0;

string instructions = "turn on 0,0 through 999,999\n"
                      "toggle 0,0 through 999,0\n"
                      "turn off 499,499 through 500,500";
string instructions_1 = "turn on 0,0 through 999,999\n";
int main()
{
    ifstream input("input.txt");
    string line = instructions_1;
    
    
       
        string command;
        int x1, y1, x2, y2;
        if (line.substr(0, 7) == "turn on") {
            command = "turn on";
            sscanf(line.c_str(), "turn on %d,%d through %d,%d", &x1, &y1, &x2, &y2);
            for (int i = x1; i <= x2; i++) {
                for (int j = y1; j <= y2; j++) {
                    grid[i][j] = 1;
                }
            }

        }
        else if (line.substr(0, 8) == "turn off") {
            command = "turn off";
            sscanf(line.c_str(), "turn off %d,%d through %d,%d", &x1, &y1, &x2, &y2);
            for (int i = x1; i <= x2; i++) {
                for (int j = y1; j <= y2; j++) {
                    grid[i][j] = 0;
                }
            }
        }
        else if (line.substr(0, 6) == "toggle") {
            command = "toggle";
            sscanf(line.c_str(), "toggle %d,%d through %d,%d", &x1, &y1, &x2, &y2);
            for (int i = x1; i <= x2; i++) {
                for (int j = y1; j <= y2; j++) {
                    if (grid[i][j] == 1)
                        grid[i][j] = 0;
                    else grid[i][j] = 1;
                }
            }
        }



    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (grid[i][j] == 1)
                count++;
        }
    }  
    cout << "Total lights on: " << count << endl;
    


    cout << "\n\n--------END-----------\n\n";
    return 0;
}