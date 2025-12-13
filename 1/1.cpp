#include <iostream>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    int current_floor = 0;
    int index = 0;
    ifstream inputFile("directions.txt");
    if (!inputFile.is_open())
    {
        cerr << "Error opening the file!\n";
        return 1;
    }

    char ch;
    while (inputFile.get(ch))
    {
        index++;
        if (ch == '(')
        {
            current_floor++;
        }
        else if (ch == ')')
        {
            current_floor--;
        }

        if (current_floor == -1)
        {
            cout << "\nEntered basement at character index: " << index << "\n";
            break; // Exit the loop once basement is reached. remove line to continue processing all characters

        }


       
    }
    inputFile.close();
    cout << "\nFinal Floor: " << current_floor << "\n";
    return 0;
}
