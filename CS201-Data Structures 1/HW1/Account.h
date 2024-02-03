//
//  Account.h
//  HW1
//
//  Created by Yasemin Akın on 31.03.2023.
//

#ifndef Account_h
#define Account_h

#include <stdio.h>
class Account{
public:
    int accountId;
    int branchId;
    int customerId;
    double depositedAmount;
    Account(int newBranchId =0 , int newCustomerId = 0, double newDepositedAmount = 0);
    void deepcopy(Account &otherAccount);
    ~Account();
};
#endif /* Account_h */
