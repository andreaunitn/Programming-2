#include <iostream>

using namespace std;

unsigned long int compute_probability(int tot_balls, int drawn_balls) {
    unsigned long int first_factor = 1;
    unsigned long int second_factor = 1;
    unsigned long int third_factor = 1;

    for(int i = tot_balls; i >= 1; i--) {
        first_factor *= i;
    }

    for(int i = (tot_balls - drawn_balls); i >= 1; i--) {
        second_factor *= i;
    }

    for(int i = drawn_balls; i >= 1; i--) {
        third_factor *= i;
    }

    return ((first_factor) / (second_factor * third_factor));
}

int main() {

    cout << "Enter the total number of lottery balls: ";

    int tot_balls;
    cin >> tot_balls;

    cout << "Enter the number of drawn balls: ";

    int drawn_balls;
    cin >> drawn_balls;

    if(tot_balls < 0 || drawn_balls < 0) {
        cout << "The number of balls must be a positive number." << endl;
        return 0;
    } else if(drawn_balls > tot_balls) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return 0;
    }

    unsigned long int res = compute_probability(tot_balls, drawn_balls);

    cout << "The probability of guessing all " << drawn_balls << " balls correctly is 1/" << res << endl;

    return 0;
}