// lesson-04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class Person {
private:
    std::string name;
    std::string job;
public:
    std::string jobStatus() {
        return this->job;
    }
    Person() {
        this->name = "Random";
        this->job = "Unemployed";
    }
    Person(std::string newName, std::string newJob) {
        this->name = newName;
        this->job = newJob;
    }
    Person(std::string newName) : Person(newName, "Unemployed") {};
};

int main()
{
    Person Chad("Mieczyslaw", "Boss");
    Person Noname;
    Person OldLady("Barbara");

    std::cout << Chad.jobStatus() << "\n";
    std::cout << Noname.jobStatus() << "\n";
    std::cout << OldLady.jobStatus();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
