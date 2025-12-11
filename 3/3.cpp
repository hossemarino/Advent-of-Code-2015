// clang-format on
#include <fstream>
#include <iostream>
#include <set>
#include <utility> // for std::pair

using namespace std;

// Function to calculate the number of unique houses visited
int housesVisited(set<pair<int, int>> positions)
{
    int unique_houses = positions.size();
    return unique_houses;
}

int main()
{
    ifstream inputFile("directions.txt");
    if (!inputFile.is_open())
    {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    int SIP_X = 0, SIP_Y = 0;   // Santa's starting position
    int RSIP_X = 0, RSIP_Y = 0; // Robo-Santa's starting position
    set<pair<int, int>> positions_santa;
    set<pair<int, int>> positions_robo_santa;

    positions_santa.insert(make_pair(SIP_X, SIP_Y));        // Starting position (0,0)
    positions_robo_santa.insert(make_pair(RSIP_X, RSIP_Y)); // Starting position (0,0)

    int houses_visited = 1; // Starting with the initial house visited

    int total_gifts = 2; // Starting with one gift at the initial position
    int index = 0;

    char ch;
    while (inputFile.get(ch))
    { // Process each character read from the file
        if (index % 2 == 0)
        {
            // Santa's turn
            if (ch == '^')
            {
                total_gifts++;
                SIP_Y++;
            }
            else if (ch == 'v')
            {
                total_gifts++;
                SIP_Y--;
            }
            else if (ch == '<')
            {
                total_gifts++;
                SIP_X--;
            }
            else if (ch == '>')
            {
                total_gifts++;
                SIP_X++;
            }

            positions_santa.insert({SIP_X, SIP_Y});
        }
        else
        {
            // Robo-Santa's turn
            if (ch == '^')
            {
                total_gifts++;
                RSIP_Y++;
            }
            else if (ch == 'v')
            {
                total_gifts++;
                RSIP_Y--;
            }
            else if (ch == '<')
            {
                total_gifts++;
                RSIP_X--;
            }
            else if (ch == '>')
            {
                total_gifts++;
                RSIP_X++;
            }

            positions_robo_santa.insert({RSIP_X, RSIP_Y});
        }
        index++;
    }
    cout << "Total gifts delivered: " << total_gifts << endl;
    cout << "Total houses visited: " << housesVisited(positions_santa) + housesVisited(positions_robo_santa) - 1
         << endl;
    inputFile.close();
    return 0;
}