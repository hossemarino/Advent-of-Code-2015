// NOT MINE: Solution to Advent of Code 2015 Day 7 in C++17
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <string>

// Define operation types
enum OPS {
    OP_ERR, OP_AND, OP_OR, OP_NOT, OP_LSHIFT, OP_RSHIFT, OP_STORE 
};
// Check if a string is a number
bool isnumber(const std::string &n) {
    return std::all_of(n.begin(), n.end(), ::isdigit);
}

// Convert string to OPS enum
OPS stoop(const std::string s) {
    if (s == "AND")
        return OP_AND;
    else if (s == "OR")
        return OP_OR;
    else if (s == "LSHIFT")
        return OP_LSHIFT;
    else if (s == "RSHIFT")
        return OP_RSHIFT;
    else
        return OP_ERR;
}

// Use 16-bit unsigned integers for wire signals
using stype = std::uint16_t;

// Define a gate structure
struct gate {
    OPS op;             // Operation type
    std::string lhs;    // Left-hand side operand
    std::string rhs;    // Right-hand side operand (if applicable)
    bool memoized;      // Whether the value has been computed
    stype val;          // Computed value
    gate(void) : op(OP_ERR), lhs(""), rhs(""), memoized(false), val(0) {} // Constructor
};

// Define a logic circuit class
class logic {
        std::map<std::string, gate> circuit;    // Map of wire names to gates
        stype output_of(const std::string &);   // Get output of a wire or number
    public:
        stype find_output(const std::string &); // Find output of a wire
        void dump(void);                        // Dump all wire values
        void reset(void);                       // Reset memoization
        std::map<std::string, gate>::size_type size(void) { return circuit.size(); } // Get number of gates
        void add(const std::string &wire, gate g) { circuit[wire] = g; }             // Add a gate
        gate& find_gate(const std::string &wire) { return circuit[wire]; }          // Find a gate
};  

// Get output of a wire or number
stype logic::output_of(const std::string &num_or_wire) {
    if (isnumber(num_or_wire))
        return std::stoi(num_or_wire); // Direct number
    else
        return find_output(num_or_wire); // Wire output
}

stype logic::find_output(const std::string &wire) {
    if (circuit.find(wire) == circuit.end()) {
        std::cerr << "Unknown wire '" << wire << "'\n";
        return 0;
    }

    gate &g = circuit[wire];
    if (g.memoized) {
        return g.val;
    } else {
        stype r;
        switch (g.op) {
            case OP_ERR:
                std::cerr << "Unknown gate operation for wire " << wire << '\n';
                return 0;
            case OP_STORE:
                r = output_of(g.lhs);
                break;
            case OP_AND:
                r = output_of(g.lhs) & output_of(g.rhs);
                break;
            case OP_OR:
                r = output_of(g.lhs) | output_of(g.rhs);
                break;
            case OP_LSHIFT:
                r = output_of(g.lhs) << output_of(g.rhs);
                break;
            case OP_RSHIFT:
                r = output_of(g.lhs) >> output_of(g.rhs);
                break;
            case OP_NOT:
                r = ~output_of(g.lhs);
                break;
        }
        g.memoized = true;
        g.val = r;
        return r;
    }
}

void logic::dump(void) {
    for (auto &wires : circuit)
        std::cout << wires.first << ": " << find_output(wires.first) << '\n';
}

void logic::reset(void) {
    for (auto &gate : circuit)
        gate.second.memoized = false;
}

int main(void) {
    std::string command;
    logic circuit;
    std::regex assign_op{ "(\\w+) -> (\\w+)" };
    std::regex not_op{ "NOT (\\w+) -> (\\w+)" };
    std::regex binary_op{ "(\\w+) (AND|OR|LSHIFT|RSHIFT) (\\w+) -> (\\w+)" };
    
    std::ifstream input("input.txt");
    std::string line;

    while (std::getline(input, line)) {
        std::smatch fields;
        gate g;
        if (std::regex_match(line, fields, assign_op)) {
            g.op = OP_STORE;
            g.lhs = fields[1];
            circuit.add(fields[2], g);
        } else if (std::regex_match(line, fields, not_op)) {
            g.op = OP_NOT;
            g.lhs = fields[1];
            circuit.add(fields[2], g);
        } else if (std::regex_match(line, fields, binary_op)) {
            g.op = stoop(fields[2]);
            g.lhs = fields[1];
            g.rhs = fields[3];
            circuit.add(fields[4], g);
        } else {
            std::cerr << "Unknown gate: " << command << '\n';
        }
    }
    
    std::cout << "There are a total of " << circuit.size() << " gates.\n";
    
    stype a = circuit.find_output("a");
    std::cout << "Initial value of a: " << a << '\n';
    
    circuit.reset();
    gate b;
    b.op = OP_STORE;
    b.lhs = std::to_string(a);
    b.memoized = true;
    b.val = a;
    circuit.add("b", b);
    
    a = circuit.find_output("a");
    std::cout << "New value of a: " << a;
    
    return 0;
}