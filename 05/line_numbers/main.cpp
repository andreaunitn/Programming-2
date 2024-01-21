#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    // Reading input and output file names
    cout << "Input file: ";
    
    string input_file_name;
    cin >> input_file_name;

    cout << "Output file: ";

    string output_file_name;
    cin >> output_file_name;

    // Opening input file
    ifstream input_file(input_file_name);

    // Check if opening was successfull
    if(!input_file)
    {
        cout << "Error! The file " << input_file_name << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    // Opening output file
    ofstream output_file(output_file_name);

    // Reading from input file and writing to output file
    int line_number = 1;
    string line;
    while(getline(input_file, line))
    {
        output_file << line_number << " " << line << endl;
        line_number++;
    }

    input_file.close();
    output_file.close();
    
    return 0;
}