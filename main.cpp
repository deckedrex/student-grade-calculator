#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

class Person {
    private:
        string firstName;
        string surName;
        vector<int> homeWork;
        int exam;
        double finalGrade;

    public:
        double calculateAverage() const
    {
        double sum = 0;

        for(size_t i = 0; i < homeWork.size(); i++)
            sum += homeWork[i];

        return sum / homeWork.size();
    }

    double calculateMedian() const
    {
        vector<int> temp = homeWork;

        sort(temp.begin(), temp.end());

        int n = temp.size();

        if(n % 2 == 1)
            return temp[n/2];
        else
            return (temp[n/2-1] + temp[n/2]) / 2.0;
    }

    double calculateFinalGrade(int choice) const
    {
        double hw;

        if(choice == 1)
            hw = calculateAverage();
        else
            hw = calculateMedian();

        return 0.4 * hw + 0.6 * exam;
    }

    bool operator<(const Person& other) const
    {
        return surName < other.surName;
    }

    friend istream& operator>>(istream& in, Person& p);
    friend ostream& operator<<(ostream& out, const Person& p);


};


istream& operator>>(istream& in, Person& p)
{
    p.homeWork.clear();

    in >> p.firstName >> p.surName;

    for(int i = 0; i < 15; i++)
    {
        int grade;
        in >> grade;
        p.homeWork.push_back(grade);
    }

    in >> p.exam;

    return in;
}


ostream& operator<<(ostream& out, const Person& p)
{
    double avg = p.calculateFinalGrade(1);
    double med = p.calculateFinalGrade(2);

    out << left << setw(12) << p.firstName
        << setw(12) << p.surName
        << setw(15) << fixed << setprecision(2) << avg
        << "| "
        << setw(10) << med;

    return out;
}

int main()
{
    ifstream file("students10000.txt");

    if(!file)
    {
        cout << "File could not be opened." << endl;
        return 1;
    }

    vector<Person> students;
    Person student;

    string line;
    getline(file, line); // skip header

    while(file >> student)
    {
        students.push_back(student);
    }

    sort(students.begin(), students.end());

    cout << left << setw(12) << "Name"
     << setw(12) << "Surname"
     << setw(15) << "Final (Avg.)"
     << "| "
     << "Final (Med.)" << endl;

    cout << "----------------------------------------------------" << endl;

    for(const Person& s : students)
        cout << s << endl;

    return 0;
};
