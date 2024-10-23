#include "movie_simulation_program_3.h"

/*********************************************************************
string promptForFilename()
Purpose:
    Helper function to ask the user for a valid file path.
Parameters:
    - None
Return Value:
    - A valid filepath string entered by the user. If the user enters "exit", the function 
    returns "EXIT".
Notes:
    - This function continuously prompts the user to enter a file path until a valid one 
       is provided or the user types "exit".
    - A valid filepath must not contain spaces and must have the ".txt" extension.
*********************************************************************/

string promptForFilename()
{
    string file_path;
    while (true) 
    {
        cout << "Please enter file path: ";
        getline(cin, file_path);

        if (file_path == "exit")
        {
            return "EXIT";
        }
        
        size_t dot_index = file_path.find('.');
        
        if ((file_path.find(' ') != string::npos) || (file_path.substr(dot_index+1) != "txt")) 
        {
            cout << "Please enter a valid file path." << endl;
            continue;
        }
        else {
            return file_path;
        }
    }
}

/*********************************************************************
void processTheaterInformation(fstream& fileInput, Theater& myTheater)
Purpose:
    Function to read theater text file and process the information
    into a theater structure
Parameters:
    I/O fstream fileInput   File stream to read theater info
    I/O Theater myTheater   Theater structure to populate
Return Value:
    -
Notes:
    This function does not validate the file structure it is provided
*********************************************************************/
void processTheaterInformation(fstream& fileInput, Theater& myTheater)
{
    string szFilePath, skip;
    while(true){
        
        szFilePath = promptForFilename();

        if(szFilePath == "EXIT")
        {
            cout << "Exiting function due to early exiting of file prompt." << endl;
            return;
        }

        fileInput.open(szFilePath);

        if(!fileInput.is_open()){
            cout << szFilePath << " does not exist" << endl;
            continue;
        }
        else {
            cout << "Reading " << szFilePath << endl;
               
            getline(fileInput, myTheater.szName);
            fileInput >> myTheater.iNumberScreens;
           
            // Skip the line containing "*Theater Rooms*"
            fileInput.ignore();
            getline(fileInput, skip);
            
            for(int i = 0; i < myTheater.iNumberScreens; i++)
            {
                fileInput >> myTheater.roomsArr[i].szName;
                fileInput >> myTheater.roomsArr[i].iParkingCapacity;
                fileInput >> myTheater.roomsArr[i].szMovieShowing;
                for(int j = 0; j< myTheater.roomsArr[i].szMovieShowing.size(); j++)
                {
                    if(myTheater.roomsArr[i].szMovieShowing[j] == '_'){
                        myTheater.roomsArr[i].szMovieShowing[j] = ' ';
                    }
                }

                myTheater.roomsArr[i].iParkingAvailable = myTheater.roomsArr[i].iParkingCapacity;
            }
            
            // Skip the line containing "*Pricing*"
            fileInput.ignore();
            getline(fileInput, skip);
            
            for(int i = 0; i < 5; i++)
            {
                fileInput >> myTheater.dPricingArr[i];
            }
            
            fileInput.close();   
            break;
        }
    }
}

/*********************************************************************
void displayMenu(string szMenuName, string szChoicesArr[], int iChoices)
Purpose:
    Function to display the menu choices of a provided menu
Parameters:
    I   string szMenuName       Title of the displayed menu
    I   string szChoicesArr     Menu choices to be displayed
    I   int iChoices            Number of menu choices    
Return Value:
    -
Notes:
    Menu options are displayed starting at 1
    The last menu option should always be displayed as -1
*********************************************************************/

void displayMenu(string szMenuName, string szChoicesArr[], int iChoices)
{
    cout<<szMenuName<<endl;
    cout << szBreakMessage;
    for(int i=0; i<iChoices-1;i++)
    {
        cout<<(i+1)<<". "<<szChoicesArr[i]<<endl;
    }
    cout<<"-1. "<<szChoicesArr[iChoices-1]<<endl;
    cout<<szBreakMessage;
}

/*********************************************************************
void displayTheaterInfo(const Theater myTheater)
Purpose:
    Function to display basic theater information
Parameters:
    I   Theater myTheater   Populated Theater info   
Return Value:
    -
Notes:
    -
*********************************************************************/

void displayTheaterInfo(const Theater myTheater)
{
    int TotalParkingSpots = 0;
    cout<<"\nTheater Information\n";
    cout << szBreakMessage;
    cout<<"Name: "<<myTheater.szName<<endl;
    cout<<"Screens: "<<myTheater.iNumberScreens<<endl;
    
    for(int i=0; i<myTheater.iNumberScreens; i++)
    {
        TotalParkingSpots += myTheater.roomsArr[i].iParkingCapacity;
    }
    cout<<"Total Parking Spots: "<<TotalParkingSpots<<endl;
    cout<<szBreakMessage;
}

/*********************************************************************
void displayNowShowing(const Theater myTheater)
Purpose:
    Function to display all movies currently showing
Parameters:
    I   Theater myTheater   Populated Theater info   
Return Value:
    -
Notes:
    Movies are displayed starting at 0
*********************************************************************/
void displayNowShowing(const Theater myTheater)
{
    cout << "\nNow Showing\n";
    
    cout<<szBreakMessage;
    
    for(int i=0; i<myTheater.iNumberScreens; i++)
    {
        cout<<i<<". "<<myTheater.roomsArr[i].szMovieShowing<<endl;
    }
    
    cout<<szBreakMessage<<endl;

}

/*********************************************************************
CustomerTicket buyTickets(Theater& myTheater)
Purpose:
    Function to handle customer buying tickets
Parameters:
    I/O Theater myTheater       Populated Theater info
Return Value:
    Populated CustomerTicket if transaction was successful
    Empty Customer Ticker if transaction was unsuccessful
Notes:
    -
*********************************************************************/
CustomerTicket buyTickets(Theater& myTheater)
{
    CustomerTicket tempCust;
    
    int MovieChoice;

    cout<<"\nBuying Tickets\n";
    cout<<szBreakMessage;
    
    cout<<"Enter Customer Name: ";
    cin>>tempCust.szName;

    for(int i=0; i<myTheater.iCurrentCustomers; i++)
    {
     
     if(myTheater.customersArr[i].szName == tempCust.szName){
       cout<<"You are only allowed 1 ticket purchase per account\n";
       tempCust.szName = "";
       cout<<szBreakMessage<<endl;
       return tempCust;
     }
    }
    
    int i=0;
    
    for(i=0; i<myTheater.iCurrentMembers; i++)
    {
     
     if(myTheater.membersArr[i].szName == tempCust.szName){
         break;
        }
    }
    
    if(tempCust.szName == myTheater.membersArr[i].szName){
           cout<<"Welcome back "<<tempCust.szName<<endl;
           
         label1: 
           displayNowShowing(myTheater);
           cout<<"What movie you would like to see? ";
           
           cin>>MovieChoice;
           cout<<"Movie Location: "<<myTheater.roomsArr[MovieChoice].szName<<endl;
           cout<<"Seats Remaining: "<<myTheater.roomsArr[MovieChoice].iParkingAvailable<<endl;

           if(myTheater.roomsArr[MovieChoice].iParkingAvailable == 0)
                {
                    cout<<"Sorry, that movie is sold out. Please buy a ticket for a different movie.\n";
                    goto label1;
                }
   
           label5:
           cout<<"\n# of member tickets: ";
           cin>>tempCust.iNumberTickets;
           if(tempCust.iNumberTickets <= 0 ||  tempCust.iNumberTickets > myTheater.roomsArr[MovieChoice].iParkingAvailable)
                {
                cout<<"Please make sure you order at least one ticket and not over the availability.";
                goto label5;
                }
           
           
           myTheater.roomsArr[MovieChoice].iParkingAvailable -= tempCust.iNumberTickets;
           tempCust.szMovie = myTheater.roomsArr[MovieChoice].szMovieShowing;
           
           tempCust.dPurchaseCost = tempCust.iNumberTickets*(myTheater.dPricingArr[3])*(1 + dSALES_TAX);
        
        }
    
    else{
            
            char choice;
            cout<<"\nDo you want to become a member(Y/N)?: ";
            cin>>choice;
            
            if(choice == 'Y' || choice == 'y'){
                
                tempCust.bBoughtMembership = true;
                myTheater.membersArr[myTheater.iCurrentMembers].szName = tempCust.szName;
                myTheater.iCurrentMembers += 1;
                
                label2:
                displayNowShowing(myTheater);
                cout<<"What movie you would like to see? ";
                cin>>MovieChoice;
                cout<<"\nMovie Location: "<<myTheater.roomsArr[MovieChoice].szName<<endl;
                cout<<"Seats Remaining: "<<myTheater.roomsArr[MovieChoice].iParkingAvailable<<endl;
                if(myTheater.roomsArr[MovieChoice].iParkingAvailable == 0)
                {
                    cout<<"Sorry, that movie is sold out. Please buy a ticket for a different movie.\n";
                    goto label2;
                }
        


                label6:
                cout<<"\n# of member tickets: ";
                cin>>tempCust.iNumberTickets;
                if(tempCust.iNumberTickets <= 0 ||  tempCust.iNumberTickets > myTheater.roomsArr[MovieChoice].iParkingAvailable)
                        {
                            cout<<"Please make sure you order at least one ticket and not over the availability.";
                            goto label6;
                        }
                myTheater.roomsArr[MovieChoice].iParkingAvailable -= tempCust.iNumberTickets;
                
                tempCust.szMovie = myTheater.roomsArr[MovieChoice].szMovieShowing;
                
                tempCust.dPurchaseCost = (tempCust.iNumberTickets*(myTheater.dPricingArr[3]) + (myTheater.dPricingArr[4]))*(1 + dSALES_TAX);
            
            }
            
            else if(choice == 'N' || choice == 'n'){
                
                int iAdultTckt, iSeniorTckt ,iChildTckt;
                
                
                label3:
                displayNowShowing(myTheater);
                cout<<"What movie you would like to see? ";
                cin>>MovieChoice;
                cout<<"Movie Location: "<<myTheater.roomsArr[MovieChoice].szName<<endl;
                cout<<"Seats Remaining: "<<myTheater.roomsArr[MovieChoice].iParkingAvailable<<endl;

                if(myTheater.roomsArr[MovieChoice].iParkingAvailable == 0)
                {
                    cout<<"Sorry, that movie is sold out. Please buy a ticket for a different movie.\n";
                    goto label3;
                }
               
                label4:
                cout<<"\n# of adult tickets: ";
                cin>>iAdultTckt;
                cout<<"# of senior tickets: ";
                cin>>iSeniorTckt;
                cout<<"# of child tickets: ";
                cin>>iChildTckt;

                tempCust.iNumberTickets = iAdultTckt + iSeniorTckt + iChildTckt;
                if(tempCust.iNumberTickets <= 0 ||  tempCust.iNumberTickets > myTheater.roomsArr[MovieChoice].iParkingAvailable)
                {
                    cout<<"Please make sure you order at least one ticket and not over the availability.";
                    goto label4;
                }
                myTheater.roomsArr[MovieChoice].iParkingAvailable -= tempCust.iNumberTickets;
                tempCust.szMovie = myTheater.roomsArr[MovieChoice].szMovieShowing;

                float Total = (iAdultTckt*myTheater.dPricingArr[0]) + (iSeniorTckt*myTheater.dPricingArr[1]) + (iChildTckt*myTheater.dPricingArr[2]);
                tempCust.dPurchaseCost = (1 + dSALES_TAX)*Total;
            }
    }

    cout<<fixed<<setprecision(2)<<"\nTotal Price: $"<<tempCust.dPurchaseCost<<endl;
    cout<<szBreakMessage;
    return tempCust;

}

// Extra Credit Function
void refundTickets(Theater& myTheater)
{
    cout<<"\nRefunding Tickets\n";
    cout<<szBreakMessage;
    string szName;
    cout<<"Enter Customer Name: ";
    cin>>szName;
    
    int i=0;
    for(i=0; i< myTheater.iCurrentCustomers; i++){

        if(myTheater.customersArr[i].szName == szName){
          break;
        }
    }
    if(myTheater.customersArr[i].szName == szName){
        cout<<"\nCustomer Information: \n";
        cout<<"Name: "<<myTheater.customersArr[i].szName<<endl;
        cout<<"Movie: "<<myTheater.customersArr[i].szMovie<<endl;
        cout<<"# of Tickets: "<<myTheater.customersArr[i].iNumberTickets<<endl;
        cout<<"Cost: $"<<myTheater.customersArr[i].dPurchaseCost<<endl<<endl;
       
        if(myTheater.customersArr[i].bBoughtMembership == true){
                cout<<"Please note: The membership fee cannot be refunded.\n";
            }
        
        cout<<"Would you like to refund this purchase(y/n)? ";
        char choice;
        cin>>choice;
        if(choice == 'Y' || choice == 'y')
        {
            myTheater.customersArr[i].szName = "";
            myTheater.customersArr[i].szMovie = "";
            myTheater.customersArr[i].iNumberTickets = 0;
            if(myTheater.customersArr[i].bBoughtMembership == true){
               myTheater.customersArr[i].dPurchaseCost = (myTheater.dPricingArr[4])*(1+dSALES_TAX);
               myTheater.customersArr[i].bBoughtMembership = false;
            }
            else{
                myTheater.customersArr[i].dPurchaseCost = 0;
            }
        cout<<"Your purchase has been refunded!\n";    
        
        }

    }
    else
    {
        cout<<"No customer found\n";
    }
    cout<<szBreakMessage;
    
 }

/*********************************************************************
double calculateTotalSales(const Theater& myTheater)
Purpose:
    Function to calculate the total sales of the theater
Parameters:
    I   Theater myTheater       Populated Theater info
Return Value:
    Total sales
Notes:
    This function should only be called by the admin
*********************************************************************/
double calculateTotalSales(const Theater& myTheater)
{
    double TOTAL_SALES = 0;
    for(int i=0; i<myTheater.iCurrentCustomers; i++)
    {
      TOTAL_SALES += myTheater.customersArr[i].dPurchaseCost;

    }
    return TOTAL_SALES;
}

/*********************************************************************
void storeData(const Theater myTheater, fstream& fileMemberIO, string szMode);
Purpose:
    Function to load data from the theater structure to a file
Parameters:
    I/O Theater& myTheater          Populated Theater info
    I/O fstream fileDataIO          File stream used to read file
    I   string szMode               What data to delete
Return Value:
    -
Notes:
    -
*********************************************************************/
void storeData(const Theater myTheater, fstream& fileDataIO, string szMode)
{
    cin.ignore();
    string szFilePath = promptForFilename();

    if(szFilePath == "EXIT") {
        cout << "Exiting without storing data." << endl;
        return;
    }
    
    fileDataIO.open(szFilePath);
    
    if (!fileDataIO.is_open()) {
        cout << "Failed to open file." << endl;
        return;
    }
    

    if(szMode == "Members")
    {
        cout << "Storing Members to file\n";
        for(int i=0; i < myTheater.iCurrentMembers; i++){
            fileDataIO << myTheater.membersArr[i].szName << "\n";
        }
    }
    else if(szMode == "Customers")
    {
        string szTemp;
       
        cout << "Storing Customers to file\n";
        for(int i=0; i<myTheater.iCurrentCustomers; i++)
        {
           szTemp = myTheater.customersArr[i].szMovie;
           
           for(int j = 0; j< szTemp.size(); j++)
                {
                    if(szTemp[j] == ' '){
                        szTemp[j] = '_';
                    }
                }

            fileDataIO<<fixed<<setprecision(2)<<myTheater.customersArr[i].szName<<" "<< szTemp
            <<" "<< myTheater.customersArr[i].iNumberTickets<<" "<< myTheater.customersArr[i].dPurchaseCost<<" "
            <<myTheater.customersArr[i].bBoughtMembership<<endl;    
        }
    }
    else
    {

        cout<<"Invalid mode\n";
        return;
    }

    fileDataIO.close();
}

/**********************************************************************
void loadData(Theater& myTheater, fstream& fileDataIO, string szMode);
Purpose:
    Function to load data from the theater structure to a file
Parameters:
    I/O Theater& myTheater          Populated Theater info
    I/O fstream fileDataIO          File stream used to read file
    I   string szMode               What data to delete
Return Value:
    -
Notes:
    -
**********************************************************************/
void loadData(Theater& myTheater, fstream& fileDataIO, string szMode)
{
    string szFilePath;
    szFilePath = promptForFilename();
    
    if(szFilePath == "EXIT") {
        cout << "Exiting without storing data." << endl;
        return;
    }

    fileDataIO.open(szFilePath);

    if (!fileDataIO.is_open()) {
        cout << "Failed to open file." << endl;
        return;
    }

    if(szMode == "Customers")
    {
        cout << "Loading Customers info from file\n";
        int i=0;
        
        while(!fileDataIO.eof())
        {
            fileDataIO >> myTheater.customersArr[i].szName;
            fileDataIO >> myTheater.customersArr[i].szMovie;
            fileDataIO >> myTheater.customersArr[i].iNumberTickets;
            fileDataIO >> myTheater.customersArr[i].dPurchaseCost;
            fileDataIO >> myTheater.customersArr[i].bBoughtMembership;
            i++;
        }
        myTheater.iCurrentCustomers = i+1;
    }

    else if(szMode == "Members")
    {

        cout << "Loading Members info from file\n";
        
        int i=0;
        while(!fileDataIO.eof())
        {
            fileDataIO >> myTheater.membersArr[i].szName;
            i++;
        }

    }

}

/*********************************************************************
void clearData(Theater& myTheater, string szMode);
Purpose:
    Function to delete data from the theater structure
Parameters:
    I/O Theater& myTheater          Populated Theater info
    I   string szMode               What data to delete
Return Value:
    -
Notes:
    Deleted theater customers are replaced with empty customers
*********************************************************************/
void clearData(Theater& myTheater, string szMode)
{
    if(szMode == "Customers")
    {

        for(int i = 0; i < myTheater.iCurrentCustomers; i++)
        {
            myTheater.customersArr[i].szName = "";
            myTheater.customersArr[i].szMovie = "";
            myTheater.customersArr[i].iNumberTickets = 0;
            myTheater.customersArr[i].dPurchaseCost = 0;
            myTheater.customersArr[i].bBoughtMembership = false;
            if(i<3){
                myTheater.roomsArr[i].iParkingAvailable = myTheater.roomsArr[i].iParkingCapacity;
            }
        }
        myTheater.iCurrentCustomers = 0;
        cout<<"Customers data cleared sucessfully!\n";
    }
    
    else if(szMode == "Members")
    {
        for(int i = 0; i < myTheater.iCurrentMembers; i++)
        {
            myTheater.membersArr[i].szName = "";
        }
        myTheater.iCurrentMembers = 0;
        cout<<"Members data cleared sucessfully!\n";
    }

   else{
       cout<<"Invalid Mode\n";
       return;
    }

}