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
        cout << "Enter salary: ";
        cin >> salary;
        cout << "Enter start year: ";
        cin >> yearStart;
        cout << "Enter bonus %: ";
        cin >> bonus;
        cout << "Enter worked days: ";
        cin >> workDays;
        cout << "Enter total days in month: ";
        cin >> totalDays;
        cout << "Enter current year: ";
        cin >> currentYear;
        tax = 13;
    }

    int Experience() const {
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

    double CalcNet() const {
        return accrued - withheld;
    }

    void Display() const {
        cout << "\nEmployee: " << lname << " " << fname << " " << mname << endl;
        cout << "Experience: " << Experience() << " years" << endl;
        cout << "Accrued: " << accrued << endl;
        cout << "Withheld: " << withheld << endl;
        cout << "Net: " << CalcNet() << endl;
    }

    // Оператор +
    Payment operator+(const Payment& other) const {
        Payment temp = *this;
        temp.accrued = this->accrued + other.accrued;
        temp.withheld = this->withheld + other.withheld;
        return temp;
    }

    // Оператор >
    bool operator>(const Payment& other) const {
        return this->CalcNet() > other.CalcNet();
    }

    // Оператор ==
    bool operator==(const Payment& other) const {
        return this->salary == other.salary;
    }

    // Оператор <<
    friend ostream& operator<<(ostream& out, const Payment& p) {
        out << p.lname << " " << p.fname << " " << p.mname
            << "\nAccrued: " << p.accrued
            << "\nWithheld: " << p.withheld
            << "\nNet: " << p.CalcNet();
        return out;
    }
};

int main() {
    Payment p1, p2;

    cout << "Enter details for first employee:\n";
    p1.Read();
    p1.CalcAccrued();
    p1.CalcWithheld();
    p1.Display();

    cout << "\nEnter details for second employee:\n";
    p2.Read();
    p2.CalcAccrued();
    p2.CalcWithheld();
    p2.Display();

    cout << "\nComparison by net salary: ";
    cout << (p1 > p2 ? "First employee earns more" : "Second employee earns more") << endl;

    Payment total = p1 + p2;
    cout << "\nTotal combined payment:\n" << total << endl;

    return 0;
}

