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

    // Sets to track unique positions visited by Santa and Robo-Santa
    set<pair<int, int>> positions_santa;      // Santa's positions
    set<pair<int, int>> positions_robo_santa; // robo-Santa's positions
    set<pair<int, int>> all_positions;        // Combined positions

    positions_santa.insert(make_pair(SIP_X, SIP_Y));        // Starting position (0,0)
    positions_robo_santa.insert(make_pair(RSIP_X, RSIP_Y)); // Starting position (0,0)

    int houses_visited = 1; // Starting with the initial house visited

    int total_gifts = 2; // Starting with one gift at the initial position
    int index = 0;

    char ch;
    while (inputFile.get(ch))
    {
        // Process each character read from the file
        // Alternate between Santa and Robo-Santa based on the index
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

    // Combine positions visited by both Santa and Robo-Santa and count unique houses, i.e. union of both sets
    // counting each house only once
    all_positions.insert(positions_santa.begin(), positions_santa.end());
    all_positions.insert(positions_robo_santa.begin(), positions_robo_santa.end());

    cout << "------------------------------------------------------------------------------------" << endl;
    cout << "Gifts delivered by Santa: " << total_gifts / 2 <<"\n";
    cout << "Gifts delivered by Robo-Santa: " << total_gifts / 2 << "\n";
    cout << "final position of Santa: (" << SIP_X << ", " << SIP_Y << ")" << "\n";
    cout << "final position of Robo-Santa: (" << RSIP_X << ", " << RSIP_Y << ")" << "\n";
    cout << "Houses visited by Santa: " << positions_santa.size() << "\n";
    cout << "Houses visited by Robo-Santa: " << positions_robo_santa.size() << "\n";
    cout << "------------------------------------------------------------------------------------" << "\n";
    cout << "Total gifts delivered: " << total_gifts << "\n";
    cout << "Total houses visited: " << housesVisited(positions_santa) + housesVisited(positions_robo_santa) - 1 << "\n";
    cout << "------------------------------------------------------------------------------------" << "\n";
    cout << "Total unique houses visited (combined): " << all_positions.size() << "\n";
    inputFile.close();
    return 0;
}