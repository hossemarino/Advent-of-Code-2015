
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <cstring>

void printRow(const std::string &line, int &size)
{
    std::cout << std::left << std::setw(15) << line
              << std::setw(15) << size << "\n";
}
int main()
{

    std::ifstream inputFile("input.txt");
    if (!inputFile)
    {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }
    int part = 2;
    std::string line;
    int total_size = 0;
    int string_size = 0;

    // part 1
    while (std::getline(inputFile, line))
    {
        if (part == 1)
        // this decoedes the string literals
        {
            int lsize = line.size();
            int esc_size = 0;
            for (size_t i = 0; i < line.size(); ++i)
            {
                if (line[i] == '\\' && i + 1 < line.size())
                {
                    char next_char = line[i + 1];
                    if (next_char == '\"' || next_char == '\\')
                    {
                        esc_size += 1; // One escape sequence
                        ++i;           // Skip the next character
                    }
                    else if (next_char == 'x' && i + 3 < line.size() &&
                             isxdigit(line[i + 2]) && isxdigit(line[i + 3]))
                    {
                        esc_size += 3; // One hex escape sequence
                        i += 3;        // Skip the next three characters
                    }
                }
            }
            total_size = total_size + lsize;
            string_size = string_size + (lsize - esc_size - 2); // Subtract escapes and quotes
            continue;
        }
        else if (part == 2)
        // this encodes the string literals
        {
            // Part 2 logic would go here
            int lsize = line.size();
            int esc_size = 0;
            for (size_t i = 0; i < line.size(); ++i)
            {
                if (line[i] == '\"' || line[i] == '\\')
                {
                    esc_size += 1; // One escape sequence
                }
            }
            total_size = total_size + lsize + esc_size + 2; // Add escapes and quotes
            string_size = string_size + lsize;

        }


    }
    std::cout << "Total Size (with escapes): " << total_size << "\n";
    std::cout << "Parsed Size (in memory): " << string_size << "\n";
    std::cout << "total_size - parsed_size = " << (total_size - string_size) << "\n";
    std::cout << "--------------------------------\n";
    inputFile.close();

    return 0;
}