#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";

    int number;
    cin >> number;

    int factor1 = 0;
    int factor2 = 0;

    if(number <= 0) {
        cout << "Only positive numbers accepted" << endl;
    } else {
        for(int i = 1; i <= number; i++) {
            if(number % i == 0) {
                factor1 = i;
                factor2 = number / i;

                if((factor2 - factor1) <= 1) {
                    break;
                }
            }
        }

        int first_factor = min(factor1, factor2);
        int second_factor = max(factor1, factor2);
        cout << number << " = " << first_factor << " * " << second_factor << endl;
    }

    return 0;
}
