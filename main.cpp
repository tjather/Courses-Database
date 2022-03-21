//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: main.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"
#include "HashChaining.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void displayMenu(){
    cout << "=======Main Menu=======" << endl
        << "1. Populate hash tables"  << endl
        << "2. Search for a course"  << endl
        << "3. Search for a professor"  << endl 
        << "4. Display all courses"  << endl
        << "5. Exit"  << endl << endl;
}

int main (int argc, char* argv[])
{
    if(argc!=3){ //check to see if correct number of command line args is passed
        cout << "Invalid number of arguments." << endl << "Usage: ./<program name> <csv file> <hashTable size>" << endl;
        return 1;
    }

    HashOpenAddressing openAddressingResolution(stoi(argv[2]));
    HashChaining chainingResolution(stoi(argv[2]));
    bool tablesPoulated = false;
    int userChoice = 0;

    do{ // loop through the menu untill user wants to quit
        ifstream in_file {argv[1]}; 
        if(!in_file){   // check to see if the file was oppened
            cout << "Failed to open the file. Please try again" << endl << "Usage: ./<program name> <csv file> <hashTable size>" << endl;; 
            return -1;   
        }
        
        displayMenu();

        cout << "Enter an option: "; 
        cin >> userChoice;

        if (userChoice == 1){ //call insert functions
            openAddressingResolution.bulkInsert(argv[1]);
            chainingResolution.bulkInsert(argv[1]);
            tablesPoulated = true;
        } 
        if(userChoice == 2){ //call search functions after getting user input
            if(tablesPoulated == false){
                cout << "Please choose option 1 first" << endl;
            }else{
                int courseYear = 0;
                int courseNumber = 0;
                string professorId;

                cout << "Enter the course year (e.g. 2021):" << endl;
                cin >> courseYear;

                cout << "Enter a course number (e.g. 2270):" << endl;
                cin >> courseNumber;

                cout << "Enter a Professor's ID (e.g. llytellf):" << endl;
                cin >> professorId;

                openAddressingResolution.search(courseYear, courseNumber, professorId);
                cout << endl;
                chainingResolution.search(courseYear, courseNumber, professorId);
                cout << endl;
            }
        }else if(userChoice == 3){ //call search professor functions after getting user input
            if(tablesPoulated == false){
                cout << "Please choose option 1 first" << endl;
            }else{
                string professorId;
                cout << "Enter a Professor's ID (e.g. nscollan0): " << endl;
                cin >> professorId;

                cout << "\n[OPEN ADDRESSING] Search for a professor" << endl;
                cout << "----------------------------------------" << endl;
                openAddressingResolution.profDb.publicSearchProfessor(professorId);

                cout << "\n[CHAINING] Search for a professor" << endl;
                cout << "----------------------------------------" << endl;
                chainingResolution.profDb.publicSearchProfessor(professorId);
            }
        }else if(userChoice == 4){ // call display course functions after getting user input
             if(tablesPoulated == false){
                cout << "Please choose option 1 first" << endl;
            }else{
                char displayChoice;
                cout << "Which hash table would you like to display the courses for (O=Open Addressing, C=Chaining)?" << endl;
                cin >> displayChoice;
                if(displayChoice == 'O' || displayChoice == 'o'){
                    openAddressingResolution.displayAllCourses();
                }else if(displayChoice == 'C' || displayChoice == 'c'){
                    chainingResolution.displayAllCourses();
                }else{
                    cout << "Invalid choice" << endl;
                }
            }
        }else if(userChoice == 5){ // quit the program
            cout << "Goodbye" << endl;
        }else{ // display error if invalid choice
            cout << "Please pick a valid choice." << endl << endl;
        }
    }while(userChoice != 5);
    
    return 0;
}