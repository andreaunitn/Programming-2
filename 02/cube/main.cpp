#include <iostream>

using namespace std;

int main() {

    cout << "Enter a number: ";

    int number;
    cin >> number;

    int res = number * number * number;

    if(res == 0) {
        cout << "The cube of " << number << " is " << res << "." << endl;
    } else if(res % number != 0) {
        cout << "Error! The cube of " << number << " is not " << res << "." << endl;
    } else {
        cout << "The cube of " << number << " is " << res << "." << endl;
    }

    return EXIT_SUCCESS;
}
