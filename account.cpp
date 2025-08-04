//
// Created by Administrator on 2025/6/6.
//
#include "account.h"

//Account
//������Ϣ
string Account::getAccountNumber() const {return accountNumber;}
string Account::getAccountHolder() const {return accountHolder;}
double Account::getBalance() const {return balance;}
string Account::getPassword() const {return password;}
int Account::getTransactionCount() const {return transactionCount;}
bool Account::changePassword(const string &oldPassword, const string &newPassword) {
  if (oldPassword != password) {
    return false;
  }
  password = newPassword;
  return true;
}

//�Ƚ��˺�
bool Account::operator==(const Account &other) const {
  return accountNumber == other.accountNumber&&password == other.password;
}

//��ӡ�˺���Ϣ
ostream& operator<<(ostream &os, const Account &a){
  os<<"���ͣ�"<<a.getType()<<';';
  os<<"�˺ţ�"<<a.getAccountNumber()<<';';
  os<<"�ֿ��ˣ�"<<a.getAccountHolder()<<';';
  os<<"���룺"<<a.getPassword()<<';';
  os<<"��"<<a.getBalance()<<';';
  os<<"ȡ�������"<<a.getTransactionCount()<<endl;
  return os;
}

void Account::display() const{
  cout<<"�𾴵�"<<getAccountHolder()<<':'<<endl;
  cout<<"������ʹ��"<<getAccountNumber()<<endl;
  cout<<"��������ǣ�"<<getBalance()<<endl;
}

//savingAccount
void savingAccount::deposit(double amount) {
  balance += amount;
}

bool savingAccount::withdraw(double amount) {
  if (amount <= balance && maxCount > transactionCount && maxAmount >= amount) {
    balance -= amount;
    transactionCount++;
    cout<<"ȡ��ɹ�"<<endl;
    return true;
  }

  if (amount > balance) {
    cout<<"����"<<endl;
  }
  if (maxCount <= transactionCount) {
    cout<<"��������ȡ��������޴���"<<endl;
  }
  if (maxAmount < amount) {
    cout<<"���ĵ��ʽ��׽���Ѿ��������������"<<endl;
  }
  return false;
}

string savingAccount::getType() const {return "�����˻�";}

//checkingAccount
void checkingAccount::deposit(double amount) {
  balance += amount;
}

bool checkingAccount::withdraw(double amount) {
  if (transactionCount >= freeCount) {
    amount *= (1+feeRate);
  }
  if (amount > balance) {
    cout<<"����"<<endl;
    return false;
  }
  else{
    balance -= amount;
    transactionCount++;
    return true;
  }
}

string checkingAccount::getType() const {return "֧Ʊ�˻�";}