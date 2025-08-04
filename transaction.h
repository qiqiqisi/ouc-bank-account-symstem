//
// Created by Administrator on 2025/6/15.
//

#ifndef TRANSACTION_H
#define TRANSACTION_H
#pragma once
#include <string>
#include <ctime>
using namespace std;
class Transaction {
private:
    string accountNumber;
    string type;
    double amount;
    time_t timestamp;

public:
    Transaction(const string& accNum, const string& t, double amt);

    string getAccountNumber() const;
    string getType() const;
    double getAmount() const;
    string getTime() const;
    time_t getTimestamp() const;

    // 用于文件存储和读取
    string toString() const;
    static Transaction fromString(const string& s);
};
#endif //TRANSACTION_H
