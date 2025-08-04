//
// Created by Administrator on 2025/6/15.
//
#include "transaction.h"
#include <sstream>
#include <iomanip>
#include <cstring> // for strftime

Transaction::Transaction(const std::string& accNum, const std::string& t, double amt)
    : accountNumber(accNum), type(t), amount(amt) {
    timestamp = std::time(nullptr);
}

std::string Transaction::getAccountNumber() const { return accountNumber; }
std::string Transaction::getType() const { return type; }
double Transaction::getAmount() const { return amount; }
std::time_t Transaction::getTimestamp() const { return timestamp; }

std::string Transaction::getTime() const {
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&timestamp));
    return std::string(buffer);
}

std::string Transaction::toString() const {
    std::ostringstream oss;
    oss << accountNumber << ';' << type << ';' << amount << ';' << timestamp;
    return oss.str();
}

Transaction Transaction::fromString(const std::string& s) {
    std::istringstream iss(s);
    std::string accountNumber, type;
    double amount;
    std::time_t timestamp;

    std::getline(iss, accountNumber, ';');
    std::getline(iss, type, ';');
    iss >> amount;
    iss.ignore();
    iss >> timestamp;

    Transaction trans(accountNumber, type, amount);
    trans.timestamp = timestamp;
    return trans;
}