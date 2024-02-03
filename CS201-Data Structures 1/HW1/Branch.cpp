//
//  Branch.cpp
//  HW1
//
//  Created by Yasemin Akın on 31.03.2023.
//

#include "Branch.h"
Branch::Branch(int newBranchId, string newBranchName){
    this->branchId = newBranchId;
    this->branchName = newBranchName;
    this->numAccountsInBranch = 0;
    this->accountsInBranch = NULL;
}
void Branch::deepcopy(Branch& otherBranch){
    this->branchId = otherBranch.branchId;
    this->branchName = otherBranch.branchName;
    this->numAccountsInBranch = otherBranch.numAccountsInBranch;
    if(otherBranch.accountsInBranch != NULL){
        this->accountsInBranch = new Account[otherBranch.numAccountsInBranch];
        for(int i = 0; i < otherBranch.numAccountsInBranch; i++){
            this->accountsInBranch[i].deepcopy(otherBranch.accountsInBranch[i]);
        }
    }
    else{
        this->accountsInBranch = NULL;
    }
}

Branch::~Branch(){
    if(accountsInBranch != NULL){
        delete[] accountsInBranch;
    }
}
void Branch::addAccountToBranch(int customerId, double amount, int accountId){
    Account addAccount;
    addAccount.customerId = customerId;
    addAccount.branchId = this->branchId;
    addAccount.accountId = accountId;
    addAccount.depositedAmount = amount;
    if(accountsInBranch==NULL){
        numAccountsInBranch++;
        accountsInBranch = new Account[numAccountsInBranch];
        accountsInBranch[0] = addAccount;
    }
    else{
        numAccountsInBranch++;
        Account* temp = new Account[numAccountsInBranch];
        for(int i = 0; i < numAccountsInBranch-1; i++){
            temp[i].deepcopy(accountsInBranch[i]);
        }
        temp[numAccountsInBranch-1].deepcopy(addAccount);
        delete[] accountsInBranch;
        accountsInBranch = temp;
    }
}
void Branch::deleteAccountFromBanch(int deleteAccountId){
    for(int i = 0; i < numAccountsInBranch; i++){
        if(accountsInBranch[i].accountId == deleteAccountId){
            if(numAccountsInBranch==1){
                delete[] accountsInBranch;
                accountsInBranch = NULL;
                numAccountsInBranch = 0;
            }
            else{
                Account* temp = new Account[numAccountsInBranch-1];
                for (int j = 0; j< i; j++){
                    temp[j].deepcopy(accountsInBranch[j]);
                }
                for (int j=i+1; j< numAccountsInBranch; j++){
                    temp[j-1].deepcopy(accountsInBranch[j]);
                }
                numAccountsInBranch--;
                delete[] accountsInBranch;
                accountsInBranch = temp;
            }
        }
    }
}
void Branch::deleteCustomerFromBranch(int customerId){
    if(accountsInBranch==NULL){return;}
    int deletionCount = 0;
    for(int i = 0; i < numAccountsInBranch; i++){
        if(accountsInBranch[i].customerId == customerId){
            deletionCount++;
        }
    }
    for(int i = 0; i < deletionCount; i++){
        for(int j = 0; j < numAccountsInBranch; j++){
            if(accountsInBranch[j].customerId == customerId){
                if(numAccountsInBranch==1){
                    delete[] accountsInBranch;
                    accountsInBranch = NULL;
                    numAccountsInBranch=0;
                }
                else{
                    Account* temp = new Account[numAccountsInBranch-1];
                    for (int k = 0; k< j; k++){
                        temp[k].deepcopy(accountsInBranch[k]);
                    }
                    for (int k=j+1; k< numAccountsInBranch; k++){
                        temp[k-1].deepcopy(accountsInBranch[k]);
                    }
                    numAccountsInBranch--;
                    delete[] accountsInBranch;
                    accountsInBranch = temp;
                }
                break;
            }
        }
    }
}
