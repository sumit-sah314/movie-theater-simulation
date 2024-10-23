#include "movie_simulation_program_3.h"


/*********************************************************************
File name: movie_simulation_program_3.cpp
Author: David Patrick
Date: 03/31/24

Purpose:
    Extend the movie theater simulation from program 2.
Command Parameters:
    -
Input:
    Path to theater text files.
    Various user input menu choices and ticket purchases.
Results:
    Simulates a drive-in movie theater ticket booth.
Notes:
    -
*********************************************************************/
int main()
{
    fstream fileTheaterInput;
    fstream fileDataIO;
    string szTheaterName;
    string szAdminPassword = "cars";
    string szTemp;
    int iAttempts = 0; 

    string szDefaultMenuChoicesArr[6] = {
        "Display theater information",
        "Display now showing",
        "Buy tickets",
        "Refund tickets",
        "Admin Menu",
        "Exit program"
    };

    string szAdminMenuChoicesArr[7] = {
        "Update theater information",
        "Display total sales",
        "Clear data",
        "Store data",
        "Load data",
        "Update admin password",
        "Exit admin menu"
    };

    cout << "Starting movie theater simulation\n" << endl;

    Theater driveInTheater;
    processTheaterInformation(fileTheaterInput, driveInTheater);

    int iChoice;
    int iAdminChoice;
    do
    {
        displayMenu("\nMenu", szDefaultMenuChoicesArr, 6);
        
        cout << "\nEnter choice: ";
        cin >> iChoice;
        
        switch(iChoice)
        {
            case 1:
                displayTheaterInfo(driveInTheater);
                break;
            case 2:
                displayNowShowing(driveInTheater);
                break;
            case 3:
                driveInTheater.customersArr[driveInTheater.iCurrentCustomers] = buyTickets(driveInTheater);
                if(driveInTheater.customersArr[driveInTheater.iCurrentCustomers].szName != "")
                    driveInTheater.iCurrentCustomers += 1;
                break;
            case 4:
                refundTickets(driveInTheater);
                break;
            case 5:
                cout << "Enter admin password: ";
                cin.ignore();
                cin >> szTemp;

                if(szTemp == szAdminPassword)
                {
                    cout << "Admin access granted" << endl;
                    iAttempts = 0;
                    do
                    {
                        displayMenu("\nAdmin Menu", szAdminMenuChoicesArr, 7);
                        
                        cout << "\nEnter choice: ";
                        cin >> iAdminChoice;
                        
                        switch(iAdminChoice)
                        {
                            case 1:
                                cin.ignore();
                                processTheaterInformation(fileTheaterInput, driveInTheater);
                                break;
                            case 2:
                                calculateTotalSales(driveInTheater);
                                cout << "Today's total sales is $" << calculateTotalSales(driveInTheater) << endl;
                                break;
                            case 3:
                                cout << "What data would you like to clear (Customers/Members): ";
                                cin >> szTemp;
                                clearData(driveInTheater, szTemp);
                                break;
                            case 4:
                                cout << "What data would you like to store (Customers/Members): ";
                                cin >> szTemp;
                                storeData(driveInTheater, fileDataIO, szTemp);
                                break;
                            case 5:
                                cout << "What data would you like to load (Customers/Members): ";
                                cin >> szTemp;
                                loadData(driveInTheater, fileDataIO, szTemp);
                                break;
                            case 6:
                                cout << "Please enter new admin password: ";
                                cin.ignore();
                                getline(cin, szAdminPassword);
                                cout << "Password has been updated" << endl; 
                            case -1:
                                cout << "Exiting admin menu" << endl;
                                iAdminChoice = -1;
                                break;
                            default:
                                cout << "Please choose a valid menu choice" << endl;
                            
                        }
                    }while(iAdminChoice != -1);
                }
                else
                {
                    cout << "Incorrect password." << endl;
                    iAttempts += 1;
                    
                    if(iAttempts > 3)
                    {
                        cout << "Closing program due to excess password attempts." << endl;
                        return -1;
                    }
                    
                }
                break;
            // Exit the program
            case -1:
                cout << "Exiting program" << endl;
                break;
            // Default case handling
            default:
                cout << "Please choose a valid menu choice" << endl;
        }
        
    }while(iChoice != -1);

    return 0;
}