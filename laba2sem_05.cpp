#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_set>

using namespace std;

class BankLoan {
    string name;
    double loanAmount;
    string currencyType;
    double interestRate;
public:
    BankLoan() : name(""), loanAmount(0.0), currencyType(""), interestRate(0.0) {}
    BankLoan(string name, double loanAmount, string currencyType, double interestRate)
        : name(name), loanAmount(loanAmount), currencyType(currencyType), interestRate(interestRate) {}
    bool operator<(const BankLoan& other) const {
        return loanAmount < other.loanAmount;
    }
    bool operator==(const BankLoan& other) const {
        return name == other.name && loanAmount == other.loanAmount &&
            currencyType == other.currencyType && interestRate == other.interestRate;
    }
    friend ostream& operator<<(ostream& os, const BankLoan& loan) {
        os << "Name: " << loan.name << ", Loan Amount: " << loan.loanAmount
            << ", Currency Type: " << loan.currencyType << ", Interest Rate: " << loan.interestRate << "%";
        return os;
    }

    struct HashF {
        size_t operator()(const BankLoan& loan) const {
            return hash<string>()(loan.name) ^ hash<double>()(loan.loanAmount) ^
                hash<string>()(loan.currencyType) ^ hash<double>()(loan.interestRate);
        }
    };
};

int main() {
    vector<BankLoan> loans;
    set<BankLoan> setLoans;
    unordered_set<BankLoan, BankLoan::HashF> unorderedSetLoans;
    ifstream inputFile("input.txt");

    string name, currencyType;
    double loanAmount, interestRate;
    while (inputFile >> name >> loanAmount >> currencyType >> interestRate) {
        BankLoan loan(name, loanAmount, currencyType, interestRate);
        loans.emplace_back(loan);
        setLoans.insert(loan);
        unorderedSetLoans.insert(loan);
    }
    inputFile.close();
    sort(loans.begin(), loans.end());
    for (const auto& loan : loans) {
        cout << loan << endl;
    }
    ofstream outputFile("output.txt");
    for (const auto& loan : loans) {
        outputFile << loan << endl;
    }
    outputFile.close();
    for (const auto& loan : setLoans) {
        cout << loan << endl;
    }
    for (const auto& loan : unorderedSetLoans) {
        cout << loan << endl;
    }

    return 0;
}
