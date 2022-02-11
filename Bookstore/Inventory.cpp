#define _CRT_SECURE_NO_WARNINGS
#include "report.h"
#include "date.h"
#include "InterfaceScreen.h"
#include <iomanip>
#include <stdio.h>


reportModule *reportPtr = new reportModule();


//This is the Menu for the report screen
void reportModule::reportMenu(Inventory *invPtr)
{
    int size = 10;
    int userInput = 0;
	std::string userString;
    
    while(userInput != 7)
    {
        std::cout <<std::endl;
        std::cout<<std::setw(size)<<"Serendipity Booksellers" <<std::endl;
        std::cout<<std::setw(size+3)<<"Report" <<std::endl<<std::endl;
        std::cout<<std::setw(size)<<"1.Inventory List"<<std::setw(size)<<std::endl;
        std::cout<<std::setw(size)<<"2.Inventory Wholesale Value"<<std::setw(size)<<std::endl;
        std::cout<<std::setw(size)<<"3.Inventory Retail Value"<<std::setw(size)<<std::endl;
        std::cout<<std::setw(size)<<"4.Listing by Quantity"<<std::setw(size)<<std::endl;
        std::cout<<std::setw(size)<<"5.Listing by Cost"<<std::setw(size)<<std::endl;
        std::cout<<std::setw(size)<<"6.Listing by Age"<<std::setw(size)<<std::endl;
        std::cout<<std::setw(size)<<"7.Return to Main Menu\n"<<std::setw(size)<<std::endl;
        std::cout<<std::setw(size)<<"Enter your choice: ";
    
		std::getline(std::cin, userString);
		try {
		
			userInput = stoi(userString);
			if (userString.length() > 1) {
				throw 1;
			}		
			if (userInput < 1 || userInput > 7) {
				throw 2;
			}
			
		}
		catch (...) {
			userInput = 8;
		}
        switch (userInput)
        {
            case 1:
                reportPtr->listByInfo(invPtr);
                break;
            case 2:
                reportPtr->wholeSaleList(invPtr);
                break;
            case 3:
                reportPtr->retailList(invPtr);
                break;
            case 4:
                reportPtr->listByQuantity(invPtr);
                break;
            case 5:
                reportPtr->listByCost(invPtr);
                break;
            case 6:
                reportPtr->listByAge(invPtr);
                break;
            case 7:
                std::cout << std::endl;
				std::cin.clear();
				if (userInput == 4) {
					mainMenu(invPtr);
					userInput--;
				}
                break;
            default:
				std::cout << "Invalid input!\n\n";
                break;
        }
    
    }
    
}

//This function lists all the info of the books currently in our database
void reportModule::listByInfo(Inventory *ptr)
{
    std::cout<<std::setw(40)<<"Inventory List"<<std::endl;
    std::cout<<"------------------------------------------------------------------------------"<<std::endl;
    
    for(int i = 0; i<Inventory::getCount(); i++)
    {
        std::cout<<(ptr+i)->getISBN()<<" "<<(ptr+i)->getTitle()<<" "<<(ptr+i)->getAuthor()<<" "<<
        (ptr+i)->getPublisher()<<" "<<(ptr+i)->getDateAdded()<<" "<<(ptr+i)->getWholesale()
        <<" "<<(ptr+i)->getRetail()<< " "<< (ptr+i)->getQuantity()<< std::endl;
        
    }
    
    
}
//This function Displays the entire list of books starting with their wholesale value
//Then it adds them up to get a Total WholeSale Value
void reportModule::wholeSaleList(Inventory *ptr)
{
    double totalWhole = 0;
    const int SIZE = Inventory::getCount();//Number of books in Inventory
    
    std::cout<<std::setw(40)<<"Inventory Wholesale Value "<<std::endl;
    std::cout<<"------------------------------------------------------------------------------"<<std::endl;
    for(int i = 0; i<SIZE;i++)
    {
        //For every book add their wholesale value to the running total.
        totalWhole +=(ptr+i)->getWholesale();
        std::cout << std::setprecision(2) << std::fixed<<'$'<< std::setw(5) << std::setfill(' ') << (ptr+i)->getWholesale()<<" "<<(ptr+i)->getTitle()
        <<" "<<(ptr+i)->getAuthor()<<std::endl;
    }
    
    std::cout<<"The total wholesale value is: $"<<totalWhole<<std::endl;
    
}
    
//This function displays the entire list of books starting with their retail value
//Then it adds them up to get a Total Retail Value
void reportModule::retailList(Inventory *ptr)
{
    double retailTotal = 0;
    const int SIZE = Inventory::getCount();//Number of books in Inventory
    
    std::cout<<std::setw(40)<<"Inventory Retail Value "<<std::endl;
    std::cout<<"------------------------------------------------------------------------------"<<std::endl;
    
    for(int i = 0; i<SIZE;i++)
       {
           //For every book add their retail value to the running total.
           retailTotal += (ptr+i)->getRetail();
           std::cout<<'$'<<(ptr+i)->getRetail()<<" "<<(ptr+i)->getTitle()
           <<" "<<(ptr+i)->getAuthor()<<std::endl;
       }
    std::cout<<"The total retail value is: $"<<retailTotal<<std::endl;
}

    
//This function displays the entire list of books sorted by cost
//Also displays proportional title and author
void reportModule::listByCost(Inventory *ptr)
{
    std::cout<<std::setw(40)<<"List by Cost"<<std::endl;
    std::cout<<"------------------------------------------------------------------------------"<<std::endl;
   
    const int SIZE = Inventory::getCount();
    Inventory temp;//Temporary place holder for sorting
    
    int i,j,minIndex;
  
    //selection sort 
    for( i = 0; i<SIZE-1; i++)
    {
        minIndex = i;
        for (j = i+1; j < SIZE; j++)
        if ((ptr+j)->getWholesale() >= (ptr+minIndex)->getWholesale())//Compare wholesales
            minIndex = j;
        
        temp = *(ptr+minIndex);//temp is set to highest value
        *(ptr+minIndex) = *(ptr+i);
        *(ptr+i) = temp; //Contents of index i are set to the highest value
        std::cout<<std::setprecision(2)<<std::fixed;
        std::cout<<'$'<<(ptr+i)->getWholesale()<<"  Title: "<<(ptr+i)->getTitle()<<" Author:  "<<(ptr+i)->getAuthor()<<std::endl;
    
    }
    
}
//This function displays the entire list of books sorted by the age of the book (Months, Days, Years)
void reportModule::listByAge(Inventory *ptr)
{
	const int SIZE = ptr->getCount();
    
    date myDate[70];//Create an array of dates to compare
    
    //Date has a inventory pointer for every instance
    for(int i = 0; i<SIZE; i++)
    {
        myDate[i].setMonth(ptr+i);
        myDate[i].setDay(ptr+i);
        myDate[i].setYear(ptr+i);
        myDate[i].setBook(ptr+i);
    }
    std::cout<<std::setw(40)<<"List by Age"<<std::endl;
    std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
      date temp;//Since we are comparing dates we have to use a date type
       int i,j,minIndex;
    //Essentially the same sorting algorithim but comparing dates
       for( i = 0; i <SIZE-1; i++)
       {
           minIndex = i;
           for (j = i+1; j < SIZE; j++)
           {
               if(myDate[j].getYear()<myDate[minIndex].getYear())
                   minIndex = j;
                else if((myDate[j].getYear() == myDate[minIndex].getYear()) &&
                        (myDate[j].getMonth() < myDate[minIndex].getMonth()))
                    minIndex = j;
                else if((myDate[j].getYear() == myDate[minIndex].getYear()) &&
                (myDate[j].getMonth() == myDate[minIndex].getMonth()) &&
                    (myDate[j].getDay() < myDate[minIndex].getDay()))
                    minIndex = j;
           }
           //temp is set to the oldest date
           temp = myDate[minIndex];
           myDate[minIndex]= myDate[i];
           myDate[i] = temp;

           //getInfo() prints everything the book contains.
          std::cout<<myDate[i].getInfo()<< std::endl;
       }
}

//This function displays the entire list of books sorted by Quantity
//Also Displays the proportional ISBN, Title, and Author
void reportModule::listByQuantity(Inventory *ptr)
{
    
    const int SIZE = Inventory::getCount();
    Inventory temp;//Temporary place holder for sorting
    int maxIndex;
    
    for(int i = 0; i<SIZE-1;i++)
    {
        maxIndex = i;
        for (int j = i+1; j<SIZE; j++)
        {
            if((ptr+j)->getQuantity()>(ptr+maxIndex)->getQuantity())
                maxIndex = j;
        }
        temp = *(ptr+maxIndex);//temp is set the highest book quantity
        *(ptr+maxIndex) = *(ptr+i);
        *(ptr+i) = temp;
    }
    
    for(int i = 0; i<SIZE; i++)
    {
        
        std::cout<< "You have "<<(ptr+i)->getQuantity()<<" books with ISBN: "<<(ptr+i)->getISBN()<< " || Title: " << (ptr+i)->getTitle() << " Author:"<< (ptr+i)->getAuthor()<<std::endl;
        
    }
    
}

