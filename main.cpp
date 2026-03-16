#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

class Person {
    private:
        string firstName;
        string surName;
        vector<int> homeWork;
        int exam;
        double finalGrade;

    public:
        Person(); // constructor
        Person(const Person& other); // copy constructor
        Person& operator=(const Person& other); // assignment constructor
        ~Person(); // destructor

        // calculation methods
        double calculateAverage() const;
        double calculateMedian () const;
        double calculateFinalGrade(int choice) const;

        friend istream& operator>>(istream& in, Person& p); // input op
        friend ostream& operator<<(ostream& out, const Person& p); // output op

};

Person::Person() { // Constructor
    firstName = "";
    surName = "";
    exam = 0;
    // finalGrade = 0.0;
}

Person::Person(const Person& other){ // Copy Constructor
    firstName = other.firstName;
    surName = other.surName;
    homeWork = other.homeWork;
    exam = other.exam;
    // finalGrade = other.finalGrade;
}

Person& Person::operator=(const Person& other){ // assignment operator
    if (this != &other) {
        firstName = other.firstName;
        surName = other.surName;
        homeWork = other.homeWork;
        exam = other.exam;
        // finalGrade = other.finalGrade;
    }
    return *this;
}

Person::~Person() {} // Destructor

double Person::calculateAverage() const { // calculate homework average
    double sum = 0;
    for (int i =0; i < homeWork.size(); i++) {
        sum += homeWork[i];
    }
    return sum / homeWork.size();
}

double Person::calculateMedian() const { // calculate homework median
    vector<int> temp = homeWork;
    sort(temp.begin(), temp.end());
    int n = temp.size();
    if(n % 2 == 1)
        return temp[n/2];
    else
        return (temp[n/2 - 1] + temp[n/2]) / 2.0;
}

double Person::calculateFinalGrade(int choice) const {
    double hw;
    if(choice == 1)
        hw = calculateAverage();
    else
        hw = calculateMedian();

    return 0.4 * hw + 0.6 * exam;

}

istream& operator>>(istream& in, Person& p) { // input operator
    cout << "Enter name and surname: ";
    in >> p.firstName >> p.surName;

    p.homeWork.clear();

    char choice;
    cout << "Generate grades randomly? (y/n): ";
    in >> choice;
    if (choice == 'y')
    {
        cout << "Generated Homework grades: ";
        for (int i = 0; i < 5; i++)
        {
            int grade = rand() % 10 + 1;
            p.homeWork.push_back(grade);

            cout << grade << " ";

        }

        cout << endl;

        p.exam =  rand() % 10 + 1;

        cout << "Generated exam grade: " << p.exam << endl;

    }
    else
    {
        int grade;
        cout<<"Enter  homework grades (-1 to stop): ";

        while(true)
        {
            in >> grade;
            if(grade == -1)
                break;

            p.homeWork.push_back(grade);
        }
        cout << "Enter examgrade: ";
        in >> p.exam;
    }


    return in;

}


ostream& operator<<(ostream& out, const Person& p)
{
    int choice;

    cout<< "choose calculating method:\n";
    cout<<"1 - Average\n";
    cout<<"2 - Median\n";
    cin >> choice;

    double grade = p.calculateFinalGrade(choice);

    out << setw(12) << p.firstName
        << setw(12) << p.surName;

    if(choice == 1)
    {
        out << setw(20) << fixed << setprecision(2) << grade << " (Average)";
    }
    else
    {
        out << setw(20) << fixed << setprecision(2) << grade << " (Median)";
    }

    return out;
}

int main()
{
    srand(time(NULL));

    Person student;
    cin >> student;
    cout << endl;
    cout << setw(12) << "Name"
         << setw(12) << "surname"
         << setw(15) << " Final_Point(Aver.)" <<endl;

    cout << "-----------------------------------" << endl;
    cout << student << endl;

    return 0;
};
