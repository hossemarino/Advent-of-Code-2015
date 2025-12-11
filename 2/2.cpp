#include<iostream>
#include<algorithm>
#include<fstream>
#include<string>
using namespace std;

int main(){
    cout << "Hello, World!" << endl;
    int l,w,h; // Declare length, width, height
    int surface_area,extra_paper,ribbon_length,min_perimeter;
    long total_paper = 0; // part 1 asks for total wrapping paper
    long total_ribbon = 0; //  part 2 asks for total ribbon length
    
    ifstream inputFile("boxes");
    if (!inputFile.is_open())
    {
        cerr << "Error opening the file!" << endl;
        return 1;
    }
    string line;
    while(getline(inputFile, line)){
        // Process each box dimensions read from the file
        
        sscanf(line.c_str(), "%dx%dx%d", &l, &w, &h); // Parse dimensions from the line 

        //cout << "Box dimensions: " << l << "x" << w << "x" << h << endl;
        surface_area = 2*l*w + 2*w*h + 2*h*l; // Calculate surface area
        extra_paper = min({l*w, w*h, h*l}); // Calculate area of smallest side for extra paper
        min_perimeter = 2 * (l + w + h - max({l, w, h})); // Smallest perimeter around the box
    
        ribbon_length = min_perimeter + (l * w * h); // Total ribbon length
        cout << "Ribbon length for this box: " << ribbon_length << " units" << endl;    
        total_ribbon += ribbon_length;
        //cout << "Surface area: " << surface_area << ", Extra paper: " << extra_paper << endl;
        int total_box_paper = surface_area + extra_paper; // Total wrapping paper needed
        total_paper += total_box_paper;

        //cout << "Total wrapping paper needed: " << total_box_paper << " square units" << endl;

    }
    inputFile.close();

    cout << "Total wrapping paper needed for all boxes: " << total_paper << " square units" << endl;
    cout << "Total ribbon length needed for all boxes: " << total_ribbon << " units" << endl;

    // Added optimization and stripping in the build process.
    return 0;
}
