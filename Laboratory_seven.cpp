#include <iostream>
#include <cmath>
#include <stdexcept>
#include <windows.h>
using namespace std;

class EmptyException {};

class ParamException {
public:
    double A, B;
    ParamException(double A, double B) : A(A), B(B) {}
};

class MyException : public std::exception {
    double A, B;
public:
    MyException(double A, double B) : A(A), B(B) {}
    const char* what() const noexcept override {
        return "MyException: A = 0 і B = 0 — пряма не існує";
    }
};

double distance1(double A, double B, double C, double x, double y) {
    if (A == 0 && B == 0)
        throw runtime_error("A = 0 і B = 0 — пряма не існує");
    return fabs(A * x + B * y + C) / sqrt(A * A + B * B);
}

double distance2(double A, double B, double C, double x, double y) throw() {
    if (A == 0 && B == 0)
        throw EmptyException();
    return fabs(A * x + B * y + C) / sqrt(A * A + B * B);
}

double distance3(double A, double B, double C, double x, double y) throw(invalid_argument) {
    if (A == 0 && B == 0)
        throw invalid_argument("A = 0 і B = 0");
    return fabs(A * x + B * y + C) / sqrt(A * A + B * B);
}

double distance4(double A, double B, double C, double x, double y) throw(MyException) {
    if (A == 0 && B == 0)
        throw MyException(A, B);
    return fabs(A * x + B * y + C) / sqrt(A * A + B * B);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    double A, B, C, x, y;

    cout << "Введіть коефіцієнти прямої A, B, C: ";
    cin >> A >> B >> C;

    cout << "Введіть координати точки x y: ";
    cin >> x >> y;

    try {
        cout << "distance1 = " << distance1(A, B, C, x, y) << endl;
    }
    catch (runtime_error& e) {
        cout << "Перехоплено runtime_error: " << e.what() << endl;
    }

    try {
        cout << "distance2 = " << distance2(A, B, C, x, y) << endl;
    }
    catch (EmptyException&) {
        cout << "Перехоплено EmptyException" << endl;
    }

    try {
        cout << "distance3 = " << distance3(A, B, C, x, y) << endl;
    }
    catch (invalid_argument& e) {
        cout << "Перехоплено invalid_argument: " << e.what() << endl;
    }

    try {
        cout << "distance4 = " << distance4(A, B, C, x, y) << endl;
    }
    catch (MyException& e) {
        cout << "Перехоплено MyException: " << e.what() << endl;
    }

    return 0;
}
