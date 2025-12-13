#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int grid[1000][1000]; // Initialize a 1000x1000 grid with all values set to 0; 1 000 000 cells

int on = 1;
int off = 0;
int count = 0;

int main(){
    ifstream input("input.txt");
    string line;

    while (getline(input, line)){
        int x1, y1, x2, y2;
        if (line.substr(0, 7) == "turn on"){
            // sscanf is used to parse formatted input from a string
            sscanf(line.c_str(), "turn on %d,%d through %d,%d", &x1, &y1, &x2, &y2); // parse the coordinates
            for (int i = x1; i <= x2; i++){
                for (int j = y1; j <= y2; j++){
                    grid[i][j] += 1;
                }
            }
        }
        else if (line.substr(0, 8) == "turn off"){
            sscanf(line.c_str(), "turn off %d,%d through %d,%d", &x1, &y1, &x2, &y2); // parse the coordinates
            for (int i = x1; i <= x2; i++){
                for (int j = y1; j <= y2; j++){
                    grid[i][j] -= 1;
                    if (grid[i][j] < 0)
                        grid[i][j] = 0;
                }
            }
        }
        else if (line.substr(0, 6) == "toggle"){
            sscanf(line.c_str(), "toggle %d,%d through %d,%d", &x1, &y1, &x2, &y2);
            for (int i = x1; i <= x2; i++){
                for (int j = y1; j <= y2; j++){
                    grid[i][j] += 2;
                }
            }
        }
    }

    for (int i = 0; i < 1000; i++){
        for (int j = 0; j < 1000; j++){
            count += grid[i][j];
        }
    }
    cout << "Total brightness is: " << count << endl;

    cout << "\n\n--------END-----------\n\n";
    return 0;
}