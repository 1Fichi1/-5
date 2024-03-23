#include <iostream>
#include <stdexcept>
#include <limits>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;

    void validateAmount(double amount, const string& errorMessage) const {
        if (amount <= 0) {
            throw invalid_argument(errorMessage);
        }
    }

public:
    BankAccount(int accNumber, double initBalance) : accountNumber(accNumber), balance(initBalance), interestRate(0) {
        if (initBalance < 0) {
            throw invalid_argument("Начальный баланс не может быть отрицательным.");
        }
    }

    void deposit(double amount) {
        validateAmount(amount, "Сумма депозита должна быть положительной.");
        this->balance += amount;
    }

    void withdraw(double amount) {
        validateAmount(amount, "Сумма снятия должна быть положительной.");
        if (this->balance < amount) {
            throw invalid_argument("Недостаточно средств для снятия.");
        }
        this->balance -= amount;
    }

    double getBalance() const {
        return this->balance;
    }

    double getInterest() const {
        return this->balance * this->interestRate * (1.0 / 12);
    }

    void setInterestRate(double newRate) {
        if (newRate < 0) {
            throw invalid_argument("Процентная ставка не может быть отрицательной.");
        }
        this->interestRate = newRate;
    }

    int getAccountNumber() const {
        return this->accountNumber;
    }

    friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};

bool transfer(BankAccount& from, BankAccount& to, double amount) {
    try {
        from.withdraw(amount);
        to.deposit(amount);
        cout << "Перевод успешно выполнен." << endl;
        return true;
    }
    catch (const invalid_argument& e) {
        cout << "Ошибка перевода: " << e.what() << endl;
        return false;
    }
}

int main() {
    setlocale(LC_ALL, "");

    double fromAccountBalance, toAccountBalance, amount;

    cout << "Введите баланс счета отправителя: ";
    cin >> fromAccountBalance;

    cout << "Введите баланс счета получателя: ";
    cin >> toAccountBalance;

    cout << "Введите сумму для перевода: ";
    cin >> amount;

    BankAccount from(12345, fromAccountBalance);
    BankAccount to(54321, toAccountBalance);

    cout << "Баланс до перевода:" << endl;
    cout << "Счёт отправителя: " << from.getBalance() << endl;
    cout << "Счёт получателя: " << to.getBalance() << endl;

    transfer(from, to, amount);

    cout << "Баланс после перевода:" << endl;
    cout << "Счет отправителя: " << from.getBalance() << endl;
    cout << "Счет получателя: " << to.getBalance() << endl;

    return 0;
}
