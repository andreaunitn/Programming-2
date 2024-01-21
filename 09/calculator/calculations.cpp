// Note that there is no need for "using namespace std",
// since no C++ standard libraries are used.

double addition(double left, double right) {
    return left + right;
}


double subtraction(double left, double right) {
    return left - right;
}


double multiplication(double left, double right) {
    return left * right;
}


double division(double left, double right) {
    return left / right;
}

double exp(double left, double right) {

    double res = 1.0;
    for(int i = 0; i < right; i++)
    {
        res *= left;
    }

    return res;
}
