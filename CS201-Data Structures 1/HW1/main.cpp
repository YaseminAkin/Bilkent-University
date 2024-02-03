//
//  main.cpp
//  HW1
//
//  Created by Yasemin Akın on 31.03.2023.
//

#include <iostream>
using namespace std;
#include "BankingSystem.h"
int main() {
//    BankingSystem B;
//    B.addBranch( 1451, "Bilkent" );
//    B.addBranch( 2435, "Kizilay" );
//    B.addBranch( 1672, "Bahcelievler" );
//    B.addBranch( 3216, "Ulus" );
//    B.addBranch( 2435, "Kizilay" );
//    B.deleteBranch( 1672 );
//    B.deleteBranch( 1723 );
//    B.addBranch( 9876, "Umitkoy" );
//    cout<<endl;
//    B.addCustomer( 1234, "Ali Ak" );
//    B.addCustomer( 4567, "Aynur Dayanik" );
//    B.addCustomer( 891234, "Cihan Erkan" );
//    B.addCustomer( 891234, "Hakan Karaca" );
//    B.addCustomer( 5678, "Mustafa Gundogan" );
//    B.addCustomer( 8901, "Can Kara" );
//    B.deleteCustomer( 5678 );
//    B.deleteCustomer( 1267 );
//    cout<<endl;
//    int account1 = B.addAccount(1451, 4567, 100.00);
//    int account2 = B.addAccount(1451, 1234, 200.00);
//    int account3 = B.addAccount(3216, 4567, 300.00);
//    int account4 = B.addAccount(1451, 4567, 1000.00);
//    int account5 = B.addAccount(1672, 8901, 100.00);
//    int account6 = B.addAccount(2435, 5678, 100.00);
//    int account7 = B.addAccount(3216, 1234, 500.00);
//    B.deleteAccount( account2 );
//    B.deleteAccount( account5 );
//    B.deleteAccount( account7 );
//    int account8 = B.addAccount(2435, 891234, 500.00);
//    cout<<endl;
//    B.showAllAccounts();
//    cout<<endl;
//    B.showBranch( 1451 );
//    cout<<endl;
//    B.showBranch( 1672 );
//    cout<<endl;
//    B.showBranch( 9876 );
//    cout<<endl;
//    B.showCustomer( 1234 );
//    cout<<endl;
//    B.showCustomer( 4567 );
//    cout<<endl;
//    B.showCustomer( 1212 );
//    cout<<endl;
//    B.deleteBranch( 1451 );
//    cout<<endl;
//    B.showCustomer( 4567 );
//    cout<<endl;
//    return 0;
    BankingSystem B;
        B.addCustomer(1, "c1");
        B.addBranch(10, "b10");
        B.addBranch(11, "b11");
        B.addCustomer(2, "c2");
        int acc1 = B.addAccount(11, 1, 100);
        int acc2 = B.addAccount(11, 1, 200);
        int acc3 = B.addAccount(11, 2, 300);
        int acc4 = B.addAccount(11, 2, 400);
        int acc5 = B.addAccount(10, 1, 500);
        int acc6 = B.addAccount(10, 1, 600);
        int acc7 = B.addAccount(10, 2, 700);
        int acc8 = B.addAccount(10, 2, 800);
        B.showAllAccounts();
        B.showBranch(10);
        B.showBranch(11);
        B.showCustomer(1);
        B.showCustomer(2);
        B.deleteCustomer(1);
    B.deleteAccount(3);
    B.deleteAccount(4);
    
        B.showAllAccounts();
        B.showBranch(11);
    return 0;
};
