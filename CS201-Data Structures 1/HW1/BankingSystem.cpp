//
//  BankingSystem.cpp
//  HW1
//
//  Created by Yasemin Akın on 31.03.2023.
//

#include "BankingSystem.h"
#include <iostream>
BankingSystem::BankingSystem () {
    accountIds = 0;
    branches = NULL;
    numBranches = 0;
    customers = NULL;
    numCustomers = 0;
    numAccounts = 0;
    accountIds = 0;
    allAccounts = NULL;
}
BankingSystem::~ BankingSystem () {
    if(customers!=NULL){
        delete[] customers;
    }
    if(branches!=NULL){
        delete[] branches;
    }
    if(allAccounts!=NULL){
        delete[] allAccounts;
    }
}
void BankingSystem::addBranch ( const int branchId , const string branchName ) {
    Branch branchToAdd;
    branchToAdd.branchId = branchId;
    branchToAdd.branchName = branchName;
    branchToAdd.accountsInBranch = NULL;
    branchToAdd.numAccountsInBranch = 0;
    if(branches == NULL){
        numBranches++;
        branches = new Branch[numBranches];
        branches[numBranches-1] = branchToAdd;
    }
    else{
        for(int i = 0; i < numBranches; i++){
            if(branchId == branches[i].branchId){
                cout<<"Branch "<<branchId<<" already exists"<<endl;
                return;
            }
        }
        numBranches++;
        Branch* temp = new Branch[numBranches];
        for(int i = 0; i < numBranches-1; i++){
            temp[i].deepcopy(branches[i]);
        }
        temp[numBranches-1].deepcopy(branchToAdd);
        delete[] branches;
        branches = temp;
    }
    cout<<"Branch "<<branchId<<" has been added"<<endl;
}
void BankingSystem::deleteBranch ( const int branchId ) {
    bool flag =  false;
    for(int i = 0; i < numBranches; i++){
        if(branchId == branches[i].branchId){
            if(numBranches == 1){
                delete[] branches;
                branches = NULL;
                numBranches = 0;
            }
            else{
                Branch* temp = new Branch[numBranches-1];
                for (int j = 0; j< i; j++){
                    temp[j].deepcopy(branches[j]);
                }
                for (int j=i+1; j< numBranches; j++){
                    temp[j-1].deepcopy(branches[j]);
                }
                numBranches--;
                delete[] branches;
                branches = temp;
            }
            cout<<"Branch "<<branchId<<" has been deleted"<<endl;
            flag = true;
        }
    }
    if(allAccounts != NULL){
        int deletionCount = 0;
        for(int i = 0; i < numAccounts; i++){
            if(allAccounts[i].branchId == branchId){
                deletionCount++;
            }
        }
        for(int k = 0; k < deletionCount; k++){
            for(int i = 0; i < numAccounts; i++){
                if(allAccounts[i].branchId == branchId){
                    if(numAccounts==1){
                        delete[] allAccounts;
                        allAccounts = NULL;
                        numAccounts = 0;
                    }
                    else{
                        Account* temp = new Account[numAccounts-1];
                        for (int j = 0; j< i; j++){
                            temp[j].deepcopy(allAccounts[j]);
                        }
                        for (int j=i+1; j< numAccounts; j++){
                            temp[j-1].deepcopy(allAccounts[j]);
                        }
                        numAccounts--;
                        delete[] allAccounts;
                        allAccounts = temp;
                    }
                    break;
                }
            }
        }
    }
    for(int i = 0; i < numCustomers; i++){
        customers[i].deleteBranchFromCustomer(branchId);
    }
    if(!flag){
        cout<<"Branch "<<branchId<<" does not exist"<<endl;
    }
}
void BankingSystem::addCustomer ( const int customerId , const string customerName ) {
    Customer customerToAdd;
    customerToAdd.customerId = customerId;
    customerToAdd.customerName = customerName;
    customerToAdd.accountsOfCustomer = NULL;
    customerToAdd.numAccountsOfCustomer = 0;
    if(customers == NULL){
        numCustomers++;
        customers = new Customer[numCustomers];
        customers[numCustomers-1] = customerToAdd;
    }
    else{
        for(int i = 0; i < numCustomers; i++){
            if(customerId == customers[i].customerId){
                cout<<"Customer "<<customerId<<" already exists"<<endl;
                return;
            }
        }
        numCustomers++;
        Customer* temp = new Customer[numCustomers];
        for(int i = 0; i < numCustomers-1; i++){
            temp[i].deepcopy(customers[i]);
        }
        temp[numCustomers-1].deepcopy(customerToAdd);
        delete[] customers;
        customers = temp;
    }
    cout<<"Customer "<<customerId<<" has been added"<<endl;
}
void BankingSystem::deleteCustomer ( const int customerId ) {
    bool flag = false;
    for(int i = 0; i < numCustomers; i++){
        if(customerId == customers[i].customerId){
            if(numCustomers == 1){
                delete[] customers;
                customers = NULL;
                numCustomers = 0;
            }
            else{
                Customer* temp = new Customer[numCustomers-1];
                for (int j = 0; j< i; j++){
                    temp[j].deepcopy(customers[j]);
                }
                for (int j=i+1; j< numCustomers; j++){
                    temp[j-1].deepcopy(customers[j]);
                }
                numCustomers--;
                delete[] customers;
                customers = temp;
            }
            cout<<"Customer "<<customerId<<" has been deleted"<<endl;
            flag = true;
        }
    }
    if(allAccounts != NULL){
        int deletionCount = 0;
        for(int i = 0; i < numAccounts; i++){
            if(allAccounts[i].customerId == customerId){
                deletionCount++;
            }
        }
        for(int k = 0; k < deletionCount; k++){
            for(int i = 0; i < numAccounts; i++){
                if(allAccounts[i].customerId == customerId){
                    if(numAccounts==1){
                        delete[] allAccounts;
                        allAccounts = NULL;
                        numAccounts = 0;
                    }
                    else{
                        Account* temp = new Account[numAccounts-1];
                        for (int j = 0; j< i; j++){
                            temp[j].deepcopy(allAccounts[j]);
                        }
                        for (int j=i+1; j< numAccounts; j++){
                            temp[j-1].deepcopy(allAccounts[j]);
                        }
                        numAccounts--;
                        delete[] allAccounts;
                        allAccounts = temp;
                    }
                    break;
                }
            }
        }
    }
    for(int i = 0; i < numBranches; i++){
        branches[i].deleteCustomerFromBranch(customerId);
    }
    if(!flag){
        cout<<"Customer "<<customerId<<" does not exist"<<endl;
    }
}
int BankingSystem::addAccount ( const int branchId , const int customerId , const double amount ) {
    for(int i = 0; i < numBranches; i++){
        if(branchId == branches[i].branchId){
            for(int j = 0; j < numCustomers; j++){
                if(customerId == customers[j].customerId){
                    numAccounts++;
                    accountIds++;
                    Account accountToAdd;
                    accountToAdd.branchId = branchId;
                    accountToAdd.customerId = customerId;
                    accountToAdd.depositedAmount = amount;
                    accountToAdd.accountId = accountIds;
                    if(allAccounts==NULL){
                        allAccounts = new Account[numAccounts];
                        allAccounts[0]=accountToAdd;
                    }
                    else{
                        Account* temp = new Account[numAccounts];
                        for(int i = 0; i < numAccounts-1; i++){
                            temp[i].deepcopy(allAccounts[i]);
                        }
                        temp[numAccounts-1].deepcopy(accountToAdd);
                        delete[] allAccounts;
                        allAccounts = temp;
                    }
                    branches[i].addAccountToBranch(customerId, amount, accountIds);
                    customers[j].addAccountToCustomer(branchId, amount, accountIds);
                    cout<<"Account "<<accountIds<<" added for customer "<<customerId<<" at branch "<<branchId<<endl;
                    return accountIds;
                }
            }
            cout<<"Customer "<<customerId<<" does not exist"<<endl;
            return -1;
        }
    }
    cout<<"Branch "<<branchId<<" does not exist"<<endl;
    return -1;
}
void BankingSystem::deleteAccount ( const int accountId ) {
    bool flag = false;
    for(int i = 0; i < numAccounts; i++){
        if(allAccounts[i].accountId == accountId){
            if(numAccounts==1){
                delete[] allAccounts;
                allAccounts = NULL;
                numAccounts = 0;
            }
            else{
                Account* temp = new Account[numAccounts-1];
                for (int j = 0; j< i; j++){
                    temp[j].deepcopy(allAccounts[j]);
                }
                for (int j=i+1; j< numAccounts; j++){
                    temp[j-1].deepcopy(allAccounts[j]);
                }
                numAccounts--;
                delete[] allAccounts;
                allAccounts = temp;
            }
            flag = true;
        }
    }
    if(!flag){
        cout<<"Account "<<accountId<<" does not exist"<<endl;
        return;
    }
    cout<<"Account "<<accountId<<" has been deleted"<<endl;
    for(int i = 0; i < numBranches; i++){
        branches[i].deleteAccountFromBanch(accountId);
    }
    for(int i = 0; i < numCustomers; i++){
        customers[i].deleteAccountFromCustomer(accountId);
    }
}
void BankingSystem::showAllAccounts () {
    cout<<"Account id Branch id Branch name Customer id Customer name Balance"<<endl;
    if(numAccounts == 0){return;}
    for(int i = 0; i < numAccounts; i++){
        string branchName = "";
        string customerName = "";
        for(int j = 0; j < numBranches; j++){
            if(allAccounts[i].branchId == branches[j].branchId){
                branchName = branches[j].branchName;
            }
        }
        for(int j = 0; j < numCustomers; j++){
            if(allAccounts[i].customerId == customers[j].customerId){
                customerName = customers[j].customerName;
            }
        }
        cout<<allAccounts[i].accountId<<" "<<allAccounts[i].branchId<<fixed<<setprecision(2)<<" "<<branchName<<" "<<allAccounts[i].customerId<<" "<<customerName<<" "<<allAccounts[i].depositedAmount<<endl;
    }
}
void BankingSystem::showBranch ( const int branchId ) {
    for(int i = 0; i < numBranches; i++){
        if(branchId == branches[i].branchId){
            cout<<"Branch id: "<<branchId<<" Branch name: "<<branches[i].branchName<<" Number of accounts: "<<branches[i].numAccountsInBranch<<endl;
            if(branches[i].numAccountsInBranch!=0){
                cout<<"Accounts at this branch:"<<endl;
                cout<<"Account id Customer id Customer name Balance"<<endl;
                for(int j = 0; j < branches[i].numAccountsInBranch; j++){
                    string customerName = "";
                    for(int k = 0; k < numCustomers; k++){
                        if(branches[i].accountsInBranch[j].customerId == customers[k].customerId){
                            customerName = customers[k].customerName;
                        }
                    }
                    cout<<branches[i].accountsInBranch[j].accountId<<" "<<branches[i].accountsInBranch[j].customerId<<" "<<fixed<<setprecision(2)<<customerName<<" "<<branches[i].accountsInBranch[j].depositedAmount<<endl;
                }
            }
            return;
        }
    }
    cout<<"Branch "<<branchId<<" does not exist"<<endl;
}
void BankingSystem::showCustomer ( const int customerId ) {
    for(int i = 0; i < numCustomers; i++){
        if(customerId == customers[i].customerId){
            cout<<"Customer id: "<<customerId<<" Customer name: "<<customers[i].customerName<<" Number of accounts: "<<customers[i].numAccountsOfCustomer<<endl;
            if(customers[i].numAccountsOfCustomer!=0){
                cout<<"Accounts of this customer:"<<endl;
                cout<<"Account id Branch id Branch name Balance"<<endl;
                for(int j = 0; j < customers[i].numAccountsOfCustomer; j++){
                    string branchName = "";
                    for(int k = 0; k < numBranches; k++){
                        if(customers[i].accountsOfCustomer[j].branchId == branches[k].branchId){
                            branchName = branches[k].branchName;
                        }
                    }
                    cout<<customers[i].accountsOfCustomer[j].accountId<<" "<<customers[i].accountsOfCustomer[j].branchId<<" "<<branchName<<" "<<fixed<<setprecision(2)<<customers[i].accountsOfCustomer[j].depositedAmount<<endl;
                }
            }
            return;
        }
    }
    cout<<"Customer "<<customerId<<" does not exist"<<endl;
}
void BankingSystem::showAllBranches(){
    cout<<"All branches:"<<endl;
    for(int i = 0; i < numBranches; i++){
        cout<<branches[i].branchId<<" "<<i<<" "<<branches[i].numAccountsInBranch<<endl;
    }
}

void BankingSystem::showAllCustomers(){
    cout<<"All customers:"<<endl;
    for(int i = 0; i < numCustomers; i++){
        cout<<customers[i].customerId<<" "<<i<<" "<<customers[i].numAccountsOfCustomer<<endl;
    }
}
