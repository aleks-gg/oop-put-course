// lesson-06.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <memory>

class Sequence {
public:
    virtual int Length() = 0;
    class FakeSequence;
};

class Sequence::FakeSequence : public Sequence {
public:
    int Length() override {
        return 100;
    }
};

class Gene {
public:
    Gene(std::shared_ptr<Sequence> newSeq, std::string newName) {
        this->seq = std::move(newSeq);
        this->name = newName;
    };
    std::string JSON() {
        std::stringstream stream;
        stream << "{\n  \"name\": \"" << this->name << "\",\n  \"length\": \"" << this->seq->Length() << "\",\n}";
        std::string str = stream.str();
        return str;
    }
private:
    std::shared_ptr<Sequence> seq;
    std::string name;
};

int main()
{
    std::shared_ptr<Sequence> af56 = std::make_shared<Sequence::FakeSequence>();
    Gene myGene(af56, "RandomName");
    std::cout << myGene.JSON();
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
