//
// Created by Administrator on 2025/6/6.
//
#include "database.h"
#include <fstream>
#include <ostream>
#include <istream>
#include <sstream>
#include "account.h"
#include "utils.h"
#include "transaction.h"
#include <algorithm>
using namespace std;

// 添加交易记录
void Database::addTransaction(const Transaction& trans) {
    transactions.push_back(trans);
}

// 按账户获取交易记录
vector<Transaction> Database::getTransactionsByAccount(const string& accountNumber) const {
    vector<Transaction> result;
    for (const auto& trans : transactions) {
        if (trans.getAccountNumber() == accountNumber) {
            result.push_back(trans);
        }
    }
    return result;
}

// 获取所有交易记录
vector<Transaction> Database::getAllTransactions() const {
    return transactions;
}

// 按时间排序交易记录
void Database::sortTransactionsByTime() {
    sort(transactions.begin(), transactions.end(), 
        [](const Transaction& a, const Transaction& b) {
            return a.getTimestamp() < b.getTimestamp();
        });
}

Account* Database::stringToAccount( string s){
    istringstream iss(s);
    string token;
    vector<string> tokens;
    while (getline(iss, token, ';')){
        tokens.push_back(token);
    }
    Utils<int>uInt;
    Utils<double>uDouble;
    if (tokens[0] == "储蓄账户"){
        return new savingAccount(tokens[1], tokens[2], tokens[3], uDouble.stringToOther(tokens[4]), uInt.stringToOther(tokens[5]));
    }
    else {
        return new checkingAccount(tokens[1], tokens[2], tokens[3], uDouble.stringToOther(tokens[4]), uInt.stringToOther(tokens[5]));

    }
}

string Database::AccountToString( Account* a) {
     ostringstream oss;
     oss << a->getType()<<';'<<a->getAccountNumber()<<';'<<a->getAccountHolder()<<';'<<a->getPassword()<<';'<<a->getBalance()<<';'<<a->getTransactionCount();
     return oss.str();
 }

Database :: Database(){
    // 读取账户信息
    ifstream ifs("database.txt");
    if (!ifs.is_open()){
        cerr<<"数据库读取故障，请联系工作人员"<<endl;
    }
    string line;
    while (getline(ifs, line)){
        accounts.push_back(stringToAccount(line));
    }
    ifs.close();
    
    // 读取交易记录
    ifstream transIfs("transactions.txt");
    if (transIfs.is_open()) {
        string line;
        while (getline(transIfs, line)) {
            transactions.push_back(Transaction::fromString(line));
        }
        transIfs.close();
    }
}

Database::~Database() {
     // 保存账户信息
     ofstream ofs("database.txt");
     if (!ofs.is_open()) {
         cerr<<("数据库保存故障，请联系工作人员")<<endl;
     }
     for (int i = 0; i < accounts.size(); i++) {
         ofs<<AccountToString(accounts[i])<<endl;
         delete accounts[i];
     }
     ofs.close();
     
     // 保存交易记录
     ofstream transOfs("transactions.txt");
     if (transOfs.is_open()) {
         for (const auto& trans : transactions) {
             transOfs << trans.toString() << endl;
         }
         transOfs.close();
     }
}