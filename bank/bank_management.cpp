#include <iostream>
#include <vector>
#include <memory> // For smart pointers

using namespace std;

class Account {
protected:
    string accountHolderName;
    int accountNumber;
    double balance;
    string accountType;

public:
    Account(string name, int num, double bal, string type)
        : accountHolderName(name), accountNumber(num), balance(bal), accountType(type) {}

    // Getters
    string getAccountHolderName() const { return accountHolderName; }
    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    string getAccountType() const { return accountType; }

    // Setters
    void setAccountHolderName(const string& name) { accountHolderName = name; }
    void setAccountNumber(int num) { accountNumber = num; }
    void setBalance(double bal) { balance = bal; }
    void setAccountType(const string& type) { accountType = type; }

    // Virtual function for polymorphism
    virtual void displayAccount() const {
        cout << "Account Holder Name: " << accountHolderName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << balance << endl;
        cout << "Account Type: " << accountType << endl;
    }

    virtual ~Account() = default; // Virtual destructor for proper cleanup of derived classes
};

class SavingAccount : public Account {
private:
    double interestRate;

public:
    SavingAccount(string name, int num, double bal, string type, double ir)
        : Account(name, num, bal, type), interestRate(ir) {}

    double getInterestRate() const { return interestRate; }
    void setInterestRate(double ir) { interestRate = ir; }

    void displayAccount() const override {
        Account::displayAccount();
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};

class JointAccount : public Account {
private:
    string secondAccountHolderName;
    double interestRate;

public:
    JointAccount(string name1, string name2, int num, double bal, string type, double ir)
        : Account(name1, num, bal, type), secondAccountHolderName(name2), interestRate(ir) {}

    string getSecondAccountHolderName() const { return secondAccountHolderName; }
    double getInterestRate() const { return interestRate; }

    void setSecondAccountHolderName(const string& name2) { secondAccountHolderName = name2; }
    void setInterestRate(double ir) { interestRate = ir; }

    void displayAccount() const override {
        Account::displayAccount();
        cout << "Second Account Holder Name: " << secondAccountHolderName << endl;
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};

class Branch {
private:
    string branchName;
    string ifscCode;
    string branchCode;
    vector<shared_ptr<Account> > accounts; // Use smart pointers for memory management

public:
    Branch(string bn, string ifsc, string bc)
        : branchName(bn), ifscCode(ifsc), branchCode(bc) {}

    void addAccount(shared_ptr<Account> account) {
        accounts.push_back(account);
    }

    void displayAccounts() const {
        cout << "Branch Name: " << branchName << endl;
        cout << "IFSC Code: " << ifscCode << endl;
        cout << "Branch Code: " << branchCode << endl;
        cout << "Accounts in this Branch:" << endl;
        for (const auto& account : accounts) {
            account->displayAccount();
            cout << "--------------------------" << endl;
        }
    }
};

class Bank {
private:
    string bankName;
    string bankCode;
    vector<shared_ptr<Branch> > branches;

public:
    Bank(string bn, string bc) : bankName(bn), bankCode(bc) {}

    void addBranch(const string& bn, const string& ifsc, const string& bc) {
        branches.push_back(make_shared<Branch>(bn, ifsc, bc));
    }

    void addAccountToBranch(int branchIndex, shared_ptr<Account> account) {
        if (branchIndex >= 0 && branchIndex < branches.size()) {
            branches[branchIndex]->addAccount(account);
        } else {
            cout << "Invalid branch index!" << endl;
        }
    }

    void displayBranches() const {
        for (const auto& branch : branches) {
            branch->displayAccounts();
        }
    }
};

int main() {
    Bank myBank("My Bank", "1234");

    // Add branches
    myBank.addBranch("SBI", "SBIN0001", "SBI001");
    myBank.addBranch("PNB", "PNB0001", "PNB001");

    // Add accounts
    myBank.addAccountToBranch(0, make_shared<SavingAccount>("Rahul", 1234, 1000, "Saving", 5.0));
    myBank.addAccountToBranch(0, make_shared<JointAccount>("Rohit", "Rohan", 1235, 2000, "Joint", 6.0));
    myBank.addAccountToBranch(1, make_shared<SavingAccount>("Raj", 1236, 3000, "Saving", 7.0));

    // Display bank details
    myBank.displayBranches();

    return 0;
}
