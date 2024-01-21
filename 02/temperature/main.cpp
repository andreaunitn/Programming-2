#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";

    float temp;
    cin >> temp;

    cout << temp << " " << "degrees Celsius is" << " " << 1.8 * temp + 32 << " " << "degrees Fahrenheit" << endl;
    cout << temp << " " << "degrees Fahrenheit is" << " " << (temp - 32)/1.8 << " " << "degrees Celsius" << endl;

    return 0;
}
