#include <iostream>
#include <string>
using namespace std;

class Payment {
private:
    string lname, fname, mname;
    double salary;
    int yearStart;
    double bonus;
    int workDays;
    int totalDays;
    double accrued;
    double withheld;
    double tax;
    int currentYear;

public:
    void Init(string ln, string fn, string mn, double s, int y, double b, int wd, int td, int curY) {
        lname = ln;
        fname = fn;
        mname = mn;
        salary = s;
        yearStart = y;
        bonus = b;
        workDays = wd;
        totalDays = td;
        currentYear = curY;
        tax = 13;
        accrued = 0;
        withheld = 0;
    }

    void Read() {
        cout << "Enter last name: ";
        cin >> lname;
        cout << "Enter first name: ";
        cin >> fname;
        cout << "Enter middle name: ";
        cin >> mname;
        cout << "Enter base salary: ";
        cin >> salary;
        cout << "Enter year of employment: ";
        cin >> yearStart;
        cout << "Enter bonus percent: ";
        cin >> bonus;
        cout << "Enter worked days: ";
        cin >> workDays;
        cout << "Enter total days in month: ";
        cin >> totalDays;
        cout << "Enter current year: ";
        cin >> currentYear;
        tax = 13;
    }

    int Experience() {
        return currentYear - yearStart;
    }

    void CalcAccrued() {
        double perDay = salary / totalDays; 
        double base = perDay * workDays;    
        double bonusSum = base * bonus / 100; 
        accrued = base + bonusSum;           
    }

    void CalcWithheld() {
        double pension = accrued * 0.01;          
        double incomeTax = (accrued - pension) * tax / 100;
        withheld = pension + incomeTax;           
    }


    double CalcNet() {
        return accrued - withheld;
    }

    void Display() {
        cout << "\nEmployee: " << lname << " " << fname << " " << mname << endl;
        cout << "Experience: " << Experience() << " years" << endl;           
        cout << "Accrued: " << accrued << endl;                                
        cout << "Withheld: " << withheld << endl;                               
        cout << "Net: " << CalcNet() << endl;                                     
    }
};

int main() {
    Payment p;                // створюємо об’єкт класу Payment
    p.Read();                 // викликаємо метод введення даних
    p.CalcAccrued();          // обчислюємо нараховану суму
    p.CalcWithheld();         // обчислюємо утримання
    p.Display();              // виводимо всі результати
    return 0;                 // завершуємо програму
}
