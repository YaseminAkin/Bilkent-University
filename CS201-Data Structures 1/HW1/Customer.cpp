//
//  Customer.cpp
//  HW1
//
//  Created by Yasemin Akın on 31.03.2023.
//

#include "Customer.h"
#include <iostream>
using namespace std;
Customer::Customer (int newCustomerId, string newCustomerName){
    customerId = newCustomerId;
    customerName = newCustomerName;
    accountsOfCustomer = NULL;
    numAccountsOfCustomer = 0;
}
void Customer::deepcopy(Customer& otherCustomer){
    customerId = otherCustomer.customerId;
    customerName = otherCustomer.customerName;
    numAccountsOfCustomer = otherCustomer.numAccountsOfCustomer;
    if(otherCustomer.accountsOfCustomer != NULL){
        Account* temp = new Account[otherCustomer.numAccountsOfCustomer];
        for(int i = 0; i < otherCustomer.numAccountsOfCustomer; i++){
            temp[i].deepcopy(otherCustomer.accountsOfCustomer[i]);
        }
        delete[] accountsOfCustomer;
        accountsOfCustomer = temp;
    }
    else{
        this->accountsOfCustomer = NULL;
    }
}
Customer::~Customer(){
    if(accountsOfCustomer != NULL){
        delete[] accountsOfCustomer;
    }
}
void Customer::addAccountToCustomer(int branchId, double amount, int accountId){
    Account addAccount;
    addAccount.customerId = this->customerId;
    addAccount.branchId = branchId;
    addAccount.depositedAmount = amount;
    addAccount.accountId = accountId;
    if(accountsOfCustomer==NULL){
        numAccountsOfCustomer++;
        accountsOfCustomer = new Account[numAccountsOfCustomer];
        accountsOfCustomer[0] = addAccount;
    }
    else{
        numAccountsOfCustomer++;
        Account* temp = new Account[numAccountsOfCustomer];
        for(int i = 0; i < numAccountsOfCustomer-1; i++){
            temp[i].deepcopy(accountsOfCustomer[i]);
        }
        temp[numAccountsOfCustomer-1].deepcopy(addAccount);
        delete[] accountsOfCustomer;
        accountsOfCustomer = temp;
    }
}
void Customer::deleteAccountFromCustomer(int deleteAccountId){
    for(int i = 0; i < numAccountsOfCustomer; i++){
        if(accountsOfCustomer[i].accountId == deleteAccountId){
            if(numAccountsOfCustomer==1){
                delete[] accountsOfCustomer;
                accountsOfCustomer = NULL;
                numAccountsOfCustomer = 0;
            }
            else{
                Account* temp = new Account[numAccountsOfCustomer-1];
                for (int j = 0; j< i; j++){
                    temp[j].deepcopy(accountsOfCustomer[j]);
                }
                for (int j=i+1; j< numAccountsOfCustomer; j++){
                    temp[j-1].deepcopy(accountsOfCustomer[j]);
                }
                numAccountsOfCustomer--;
                delete[] accountsOfCustomer;
                accountsOfCustomer = temp;
            }
        }
    }
}
void Customer::deleteBranchFromCustomer(int branchId){
    if(accountsOfCustomer == NULL){
        return;}
    int deletionCount = 0;
    for(int i = 0; i < numAccountsOfCustomer; i++){
        if(accountsOfCustomer[i].branchId == branchId){
            deletionCount++;
        }
    }
    for(int i = 0; i < deletionCount; i++){
        for(int j = 0; j < numAccountsOfCustomer; j++){
            if(accountsOfCustomer[j].branchId == branchId){
                if(numAccountsOfCustomer==1){
                    delete[] accountsOfCustomer;
                    accountsOfCustomer = NULL;
                    numAccountsOfCustomer=0;
                }
                else{
                    Account* temp = new Account[numAccountsOfCustomer-1];
                    for (int k = 0; k< j; k++){
                        temp[k].deepcopy(accountsOfCustomer[k]);
                    }
                    for (int k=j+1; k< numAccountsOfCustomer; k++){
                        temp[k-1].deepcopy(accountsOfCustomer[k]);
                    }
                    numAccountsOfCustomer--;
                    delete[] accountsOfCustomer;
                    accountsOfCustomer = temp;
                }
                break;
            }
        }
    }
}
