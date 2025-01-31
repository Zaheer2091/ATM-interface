#include <iostream>
#include <string>

using namespace std;

// ATM Account Class
class Account {
private:
    string accountNumber;
    string pin;
    double balance;

public:
    // Constructor to initialize account details
    Account(string accNum, string accPin, double bal) {
        accountNumber = accNum;
        pin = accPin;
        balance = bal;
    }

    // Verify PIN
    bool verifyPIN(string enteredPIN) {
        return enteredPIN == pin;
    }

    // Display Balance
    void displayBalance() {
        cout << "\n===== Mohmad Zaheer's ATM System =====\n";
        cout << "Account Number: " << accountNumber << endl;
        cout << "Current Balance: " << balance << endl;
    }

    // Deposit Money
    void deposit(double amount) {
        balance += amount;
        cout << "\nDeposit Successful! New Balance: " << balance << endl;
    }

    // Withdraw Money
    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "\nInsufficient funds! Transaction failed.\n";
            return false;
        }
        balance -= amount;
        cout << "\nWithdrawal Successful! New Balance: " << balance << endl;
        return true;
    }

    // Change PIN
    void changePIN(string newPIN) {
        pin = newPIN;
        cout << "\nPIN Changed Successfully!\n";
    }

    // Static function to create a new account if not found
    static Account createNewAccount(string accNum) {
        cout << "WELCOME TO SBI ATM.\n";
        return Account(accNum, "2091", 1000.0);  // Default PIN "2091"
    }
};

// ATM Menu
void atmMenu(Account &user) {
    int choice;
    do {
        cout << "\n===== Welcome to Mohmad Zaheer's ATM System =====\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Change PIN\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                user.displayBalance();
                break;
            case 2: {
                double amount;
                cout << "Enter amount to deposit: ";
                cin >> amount;
                user.deposit(amount);
                break;
            }
            case 3: {
                double amount;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                user.withdraw(amount);
                break;
            }
            case 4: {
                string newPIN;
                cout << "Enter new PIN: ";
                cin >> newPIN;
                user.changePIN(newPIN);
                break;
            }
            case 5:
                cout << "\nThank you for using Mohmad Zaheer's ATM System!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

// Main Function
int main() {
    string accNum, pin;

    // Input details
    cout << "\n===== Welcome to Mohmad Zaheer's ATM System =====\n";
    cout << "Please enter your account number: ";
    cin >> accNum;

    // If account exists, load it. If not, create a new account with details.
    Account user = Account::createNewAccount(accNum);

    // Input PIN
    cout << "Enter your PIN: ";
    cin >> pin;

    if (user.verifyPIN(pin)) {
        cout << "\nLogin Successful!\n";
        atmMenu(user);
    } else {
        cout << "\nIncorrect PIN. Access Denied!\n";
    }

    return 0;
}
