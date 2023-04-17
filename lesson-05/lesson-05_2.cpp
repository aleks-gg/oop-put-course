#include <iostream>
#include <map>

class Cantor {
public:
    Cantor() = default;
    virtual ~Cantor() = default;

    virtual double Rate(const std::string& abbreviation) const = 0;
};

class FakeUsdCantor : public Cantor {
public:
    FakeUsdCantor() {
        // rates_ map with values for ten most popular currencies relative to USD
        rates_ = {
          {"EUR", 0.85},
          {"JPY", 110.66},
          {"GBP", 0.73},
          {"CHF", 0.91},
          {"CAD", 1.25},
          {"AUD", 1.34},
          {"CNY", 6.47},
          {"HKD", 7.78},
          {"NZD", 1.44},
          {"KRW", 1153.89}
        };
    }

    double Rate(const std::string& abbreviation) const override {
        auto it = rates_.find(abbreviation);
        if (it != rates_.end()) {
            return it->second;
        }
        // Handle error case when currency abbreviation is not found
        return 0.0;
    }

private:
    std::map<std::string, double> rates_;
};

class Currency {
public:
    Currency() = default;
    virtual ~Currency() = default;

    virtual double ConvertedToDollars(const Cantor& cantor) const = 0;
    virtual std::string Abbreviation() const = 0;
    virtual double Amount() const = 0;
};

// Solution below
class Won : public Currency {
public:
    explicit Won(std::string abbrev, double amount);
    double ConvertedToDollars(const Cantor& cantor) const override;
    std::string Abbreviation() const override;
    double Amount() const override;
private:
    std::string abbreviation;
    double amount;
};

Won::Won(std::string abbrev, double amt) {
    this->abbreviation = abbrev;
    this->amount = amt;
}

double Won::ConvertedToDollars(const Cantor& cantor) const {
    return this->amount / cantor.Rate(this->abbreviation);
}

double Won::Amount() const {
    return this->amount;
}

std::string Won::Abbreviation() const {
    return this->abbreviation;
}

int main() {
    FakeUsdCantor MyCantor;

    Won *KRaccount = new Won("KRW", 95671);
    std::cout << "Balance: " << KRaccount->Amount() << "\n";
    std::cout << "Currency: " << KRaccount->Abbreviation() << "\n";
    std::cout << "Balance in USD: " << KRaccount->ConvertedToDollars(MyCantor);
    return 0;
}