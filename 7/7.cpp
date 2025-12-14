#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main()
{

    std::string example = "123 -> x\n"
                          "456 -> y\n"
                          "x AND y -> d\n"
                          "x OR y -> e\n"
                          "x LSHIFT 2 -> f\n"
                          "y RSHIFT 2 -> g\n"
                          "NOT x -> h\n"
                          "NOT y -> i";

    std::string assign_delimiter = " -> ";
    std::string op_and = " AND ";
    std::string op_or = " OR ";
    std::string op_lshift = " LSHIFT ";
    std::string op_rshift = " RSHIFT ";
    std::string op_not = "NOT ";
    size_t pos = 0;
    int index = 0;

    std::map<char, int> var_map; // Map variable names to their values

    std::cout << "Parsing example instructions:\n";
    std::ifstream input("input.txt");
    std::string line;

    while (getline(input, line))
    {
        pos = line.find('\n');

        line = line.substr(0, pos);
        size_t delim_pos = line.find(assign_delimiter);
        if (delim_pos != std::string::npos)
        {
            std::string expression = line.substr(0, delim_pos);
            std::string variable = line.substr(delim_pos + assign_delimiter.length());
            std::cout << "Variable: " << variable << ", Expression: " << expression << std::endl;

            // Determine operation type
            if (expression.find(op_and) != std::string::npos)
            {
                var_map[variable[0]] = var_map[expression.substr(0, expression.find(op_and))[0]] & var_map[expression.substr(expression.find(op_and) + op_and.length())[0]]; //  AND operation
                //std::cout << "  Operation: AND" << std::endl;
            }
            else if (expression.find(op_or) != std::string::npos)
            {
                var_map[variable[0]] = var_map[expression.substr(0, expression.find(op_or))[0]] | var_map[expression.substr(expression.find(op_or) + op_or.length())[0]]; //  OR operation
                //std::cout << "  Operation: OR" << std::endl;
            }
            else if (expression.find(op_lshift) != std::string::npos)
            {
                var_map[variable[0]] = var_map[expression.substr(0, expression.find(op_lshift))[0]] << stoi(expression.substr(expression.find(op_lshift) + op_lshift.length())); //  LSHIFT operation
                //std::cout << "  Operation: LSHIFT" << std::endl;
            }
            else if (expression.find(op_rshift) != std::string::npos)
            {
                var_map[variable[0]] = var_map[expression.substr(0, expression.find(op_rshift))[0]] >> stoi(expression.substr(expression.find(op_rshift) + op_rshift.length())); //  RSHIFT operation
                //std::cout << "  Operation: RSHIFT" << std::endl;
            }
            else if (expression.find(op_not) != std::string::npos)
            {
                var_map[variable[0]] = var_map[expression.substr(op_not.length())[0]] ^ 0xFFFF; //  NOT operation
                //std::cout << "  Operation: NOT" << std::endl;
            }
            else
            {
                if (isalpha(expression[0]))
                    var_map[variable[0]] = var_map[expression[0]]; // Variable assignment
                else{
                    var_map[variable[0]] = stoi(expression); // Direct assignment
                }
                //std::cout << "  Operation: ASSIGN" << std::endl;
            }
        }
        // example.erase(0, pos + 1);
        index++;
    }
    std::cout << "\nVariable Values:\n";
    for (const auto &pair : var_map)
    {
        std::cout << pair.first << " = " << pair.second << std::endl;
    }

    std::cout << "\n\nBitwise Operations Examples:" << std::endl;
    int v1 = 123; // Example value
    int v2 = 456; // Example value
    std::cout << "v1 AND v2 = " << (v1 & v2) << std::endl;
    std::cout << "v1 OR v2 = " << (v1 | v2) << std::endl;
    std::cout << "v1 XOR v2 = " << (v1 ^ v2) << std::endl;
    std::cout << "NOT v1 = " << (~v1) << std::endl;
    std::cout << "v1 shifted left by 2 = " << (v1 << 2) << std::endl;
    std::cout << "v1 shifted right by 2 = " << (v1 >> 2) << std::endl;
    std::cout << "~0 = " << (~0) << std::endl;
    std::cout << "\n\n--------END-----------\n\n";
    return 0;
}