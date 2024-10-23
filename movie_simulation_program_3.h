#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

inline string szBreakMessage = "*****************************\n";
inline double dSALES_TAX = 0.08; 

struct TheaterRoom
{
    string szName;          // Name of theater room
    string szMovieShowing;  // Name of movie showing
    int iParkingCapacity;   // Number of parking spots
    int iParkingAvailable;  // Number of parking spots left
};

struct CustomerTicket
{
    string szName = "";             // Name of person who made purchase
    string szMovie;                 // What movie tickets are for
    bool bBoughtMembership = false; // Bought membership on the purchase
    int iNumberTickets = 0;         // Number of tickets purchased 
    double dPurchaseCost = 0.0;     // How much did the tickets cost including tax
    
};

struct Member
{
    string szName = "";         // Name of person who bought membership
};

struct Theater
{
    string szName;                      // Name of the theater
    int iNumberScreens;                 // Number of screens the theater has
    int iCurrentCustomers = 0;          // Current number of customers
    int iCurrentMembers = 0;            // Current number of members
    double dPricingArr[5];              // Pricing Categories
    TheaterRoom roomsArr[10];           // Array of theater rooms
    CustomerTicket customersArr[200];   // Array of customers
    Member membersArr[200];             // Array of members
};

// Functions to Implement
string promptForFilename();
void processTheaterInformation(fstream& fileInput, Theater& myTheater);

void displayMenu(string szMenuName, string szChoicesArr[], int iChoices);
void displayTheaterInfo(const Theater myTheater);
void displayNowShowing(const Theater myTheater);
CustomerTicket buyTickets(Theater& myTheater);
void refundTickets(Theater& myTheater);

double calculateTotalSales(const Theater& myTheater);
void storeData(const Theater myTheater, fstream& fileMemberIO, string szMode);
void loadData(Theater& myTheater, fstream& fileMemberIO, string szMode);
void clearData(Theater& myTheater, string szMode);