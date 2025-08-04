#include "database.h"
#include "account.h"
#include "transaction.h"
#include <algorithm>
#include <limits>
#include <iomanip>
using namespace std;

int main() {
    while (true) {
        Database database;
        char choice, choice1;
        string number,password,name;
        reChooseAll:
        cout<<"---��ӭʹ��ÿ������ϵͳ---"<<endl;
        cout<<"�˻���¼�밴1"<<endl;
        cout<<"�˻�ע���밴2"<<endl;
        cout<<"������Ա�밴3"<<endl;
        cout<<"������ѡ�";
        cin >> choice;
        switch(choice) {
            case '1': {
                //��¼
                reInput:;
                cout << "�������˻�: ";
                cin >> number;
                cout <<"���������룺";
                cin >> password;


                auto underUser = find_if(database.accounts.begin(),database.accounts.end(),
                                                 [number,password](const Account* a) {
                                                     return a->getAccountNumber()==number && a->getPassword()==password;
                                                 });

                if (underUser != database.accounts.end()) {
                    (*underUser)->display();
                }
                else {
                    cout<<"�˺Ż����������"<<endl;
                    goto reInput;
                }

                //����ҵ��
                cout<<"��Ǯ�밴1��ȡǮ�밴2���޸������밴3���鿴���׼�¼�밴4���˳��밴5��";
                while(true) {
                    cin >> choice1;
                    if(choice1 == '5') break;

                    switch(choice1) {
                        //��Ǯ
                        case '1': {
                            cout<<"�����������"<<endl;
                            double amount;
                            cin>>amount;
                            while(amount<0||cin.fail()) {
                                cout<<"����������������룺";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin>>amount;
                            }
                            (*underUser)->deposit(amount);
                            // ��Ӵ���¼
                            database.addTransaction(Transaction(number, "���", amount));
                            cout<<"�����ɹ�"<<endl;
                            break;
                        }
                        case '2': {
                            cout<<"��������Ҫȡ���Ľ��"<<endl;
                            double amount;
                            cin>>amount;
                            while(amount<0||cin.fail()) {
                                cout<<"�����������������"<<endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin>>amount;
                            }

                            if ((*underUser)->withdraw(amount)) {
                                // ���ȡ���¼
                                database.addTransaction(Transaction(number, "ȡ��", amount));
                                cout<<"�����ɹ�"<<endl;
                            }
                            else {
                                cout<<"ȡǮʧ��"<<endl;
                            }
                            break;
                        }
                        case '3': {
                            cout<<"���������������룺";
                            string newPassword;
                            cin>>newPassword;
                            if ((*underUser)->changePassword(password,newPassword)) {
                                cout<<"�޸ĳɹ�"<<endl;
                            }
                            else {
                                cout<<"�޸�ʧ��"<<endl;
                            }
                            break;
                        }
                        case '4': {
                            // �鿴���׼�¼
                            auto trans = database.getTransactionsByAccount(number);
                            if (trans.empty()) {
                                cout << "û�н��׼�¼" << endl;
                            } else {
                                cout << "���׼�¼��" << endl;
                                cout << "ʱ��\t\t\t����\t���" << endl;
                                for (const auto& t : trans) {
                                    cout << t.getTime() << "\t"
                                         << t.getType() << "\t"
                                         << fixed << setprecision(2) << t.getAmount() << endl;
                                }
                            }
                            break;
                        }
                        default:
                            cout<<"��������ȷ�Ĳ���"<<endl;
                    }
                    cout << "����������ѡ��1-4�����˳��밴5: ";
                }
                break;
            }
            case '2': {
                cout<<"��ѡ����Ҫע������ͣ������˻��밴1��֧Ʊ�˻��밴2��"<<endl;
                cin >> choice1;
                cout << "�����������˻�: ";
                cin >> number;


                auto it1=find_if(database.accounts.begin(),database.accounts.end(),
                                         [number](const Account* a) {
                                             return a->getAccountNumber()==number;  // ����Ϊ�Ƚ��˺Ŷ��ǳ�����
                                         });

                while (it1 != database.accounts.end()) {
                    cout <<"�˻��Ѵ��ڣ�����������:";
                    cin >> number;
                    it1 = find_if(database.accounts.begin(),database.accounts.end(),
                                          [number](const Account* a) {
                                              return a->getAccountNumber()==number;
                                          });
                }
                cout <<"���������룺";
                cin >> password;
                cout <<"����������������";
                cin >> name;

                switch (choice1) {
                    case '1': {
                        database.accounts.push_back(new savingAccount(number,name,password,0.0,0));
                        cout << "����ɹ�"<<endl;
                        break;
                    }
                    case '2': {
                        database.accounts.push_back(new checkingAccount(number,name,password,0.0,0));
                        cout<<"����ɹ�"<<endl;
                        break;
                    }
                    default:
                        cout<<"������������¿�ʼע������"<<endl;
                }
                break;
            }
            case '3':
                cout<<"�����빤����Ա����"<<endl;
                cin >> password;
                if (password!="999999") {
                    cout<<"�������"<<endl;
                    break;
                }
                reChooseWorker:;
                cout<<"�������������밴1"<<endl;
                cout<<"�����˺Ų����밴2"<<endl;
                cout<<"�������������밴3"<<endl;
                cout<<"��ʾ�����˺���Ϣ�밴4"<<endl;
                cout<<"�鿴���н��׼�¼�밴5"<<endl;  // ����ѡ��
                cout<<"��ʱ��˳��鿴���׼�¼�밴6"<<endl;  // ����ѡ��
                cout<<"�˳��밴7"<<endl;
                cout<<"���������밴8"<<endl;
                cout<<"��ѡ��";
                cin >> choice1;
                if (choice1 != '7') {
                    switch(choice1) {
                        case '1': {
                            sort(database.accounts.begin(),database.accounts.end());
                            for (Account* a : database.accounts) {
                                cout<<*a<<endl;
                            }
                            goto reChooseWorker;
                        }
                        case '2': {
                            cout<<"�������˺ţ�";
                            cin >> number;
                            auto findUser = find_if(database.accounts.begin(),database.accounts.end(),[number](const Account* a) {return a->getAccountNumber()==number;});
                            if (findUser != database.accounts.end()) {
                                cout<<**findUser<<endl;
                            }
                            else {
                                cout<<"���ݿ���û�и��˺�"<<endl;
                            }
                            goto reChooseWorker;
                        }
                        case '3': {
                            cout<<"������������";
                            cin >> name;
                            auto findUser = find_if(database.accounts.begin(),database.accounts.end(),[name](const Account* a) {return a->getAccountHolder()==name;});
                            if (findUser != database.accounts.end()) {
                                cout<<**findUser<<endl;
                            }
                            else {
                                cout<<"���ݿ���û�и��˺�"<<endl;
                            }
                            goto reChooseWorker;
                        }
                        case '4': {
                            for (Account* a : database.accounts) {
                                cout<<*a<<endl;
                            }
                            goto reChooseWorker;
                        }
                        case '5': {  // �鿴���н��׼�¼
                            auto allTrans = database.getAllTransactions();
                            if (allTrans.empty()) {
                                cout << "û�н��׼�¼" << endl;
                            } else {
                                cout << "���н��׼�¼��" << endl;
                                cout << "�˻�\tʱ��\t\t\t����\t���" << endl;
                                for (const auto& t : allTrans) {
                                    cout << t.getAccountNumber() << "\t"
                                         << t.getTime() << "\t"
                                         << t.getType() << "\t"
                                         << fixed << setprecision(2) << t.getAmount() << endl;
                                }
                            }
                            goto reChooseWorker;
                        }
                        case '6': {  // ��ʱ��˳��鿴���׼�¼
                            database.sortTransactionsByTime();
                            auto sortedTrans = database.getAllTransactions();
                            if (sortedTrans.empty()) {
                                cout << "û�н��׼�¼" << endl;
                            } else {
                                cout << "��ʱ������Ľ��׼�¼��" << endl;
                                cout << "ʱ��\t\t\t�˻�\t����\t���" << endl;
                                for (const auto& t : sortedTrans) {
                                    cout << t.getTime() << "\t"
                                         << t.getAccountNumber() << "\t"
                                         << t.getType() << "\t"
                                         << fixed << setprecision(2) << t.getAmount() << endl;
                                }
                            }
                            goto reChooseWorker;
                        }
                        case '7': {
                            goto reChooseAll;
                        }
                        case '8': {
                            goto exit;
                        }
                        default: {
                            cout<<"��Чѡ�������ѡ��" << endl;
                            goto reChooseWorker;
                        }
                    }
                }
                break;
            default:
                cout << "��Чѡ�������ѡ��" << endl;
                goto reChooseAll;
        }
    }
    exit:;
    return 0;
}