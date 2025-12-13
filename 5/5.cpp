#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string vowels = "aeiou";
string bad_strings[4] = {"ab", "cd", "pq", "xy"};
string double_letters[26] = {"aa", "bb", "cc", "dd", "ee", "ff", "gg", "hh", "ii", "jj", "kk", "ll", "mm", "nn", "oo", "pp", "qq", "rr", "ss", "tt", "uu", "vv", "ww", "xx", "yy", "zz"};
string test_case = "ugknbfddgicrmopn"; // nice
int nice = 0;
int bad = 0;

bool is_nice(string s, int part = 1)
{
    int vowel_count = 0;
    bool double_letter = false;
    bool bad_combination = false;
    bool pair_repeats = false;
    bool repeat_with_one_between = false;
    if (part == 1){
        // Part 1 rules
        // Count vowels
        for (char c : s){
            if (vowels.find(c) != string::npos){
                vowel_count++;
            }
        }
        // Check for double letters
        for (string dl : double_letters){
            if (s.find(dl) != string::npos){
                double_letter = true;
            }
        }
        // Check for bad sub strings
        for (string bs : bad_strings){
            if (s.find(bs) != string::npos)
            {
                bad_combination = true;
            }
        }
    }
    else if (part == 2){
        // Part 2 rules

        // Check for pair that appears at least twice without overlapping
        for (size_t i = 0; i < s.length() - 1; i++){
            // Extract the pair of characters starting at position i
            // Check if this pair appears again in the string starting from position i + 2
            string pair = s.substr(i, 2);
            if (s.find(pair, i + 2) != string::npos){
                pair_repeats = true;
            }
        }

        // Check for letter that repeats with exactly one letter between
        for (size_t i = 0; i < s.length() - 2; i++){ 
            // Ensure we don't go out of bounds
            // Check if the character at position i is the same as the character at position i + 2
            if (s[i] == s[i + 2]){
                repeat_with_one_between = true;
            }
        }
    }

    // Final evaluation
    if (part == 1 && vowel_count >= 3 && double_letter && !bad_combination){
        return true;
    }
    else if (part == 2 && pair_repeats && repeat_with_one_between){
        return true;
    }
    else{
        return false;
    }
}

int main()
{
    // Open the input file
    ifstream inputFile("strings.txt");
    if (!inputFile.is_open())
    {
        cerr << "Error opening the file!" << endl;
        return 1;
    }
    // Read each line from the file and evaluate
    string line;
    while (getline(inputFile, line))
    {
        if (is_nice(line,2)){
            nice++;
        }
        else{
            bad++;
        }
    }
    inputFile.close(); // Close the file

    is_nice(test_case);
    cout << "Nice count: " << nice << "\n";
    cout << "Bad count: " << bad << "\n";
}