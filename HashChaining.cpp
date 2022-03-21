//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashChaining.cpp
//-----------------------------------------------------------------------------

#include "HashChaining.h"

using namespace std;

/**
* HashChaining - parameterized constructor that creates the hash table and sets each bucket to NULL
* @param size
* @return none
*/
HashChaining::HashChaining(int size)
{
    hashTableSize = size;
    hashTable = new Course*[hashTableSize];
    for(int i=0;i<hashTableSize;i++){
        hashTable[i] = NULL;
    }
}

/**
* HashChaining - destructor that loops through each bucket and deletes the linked list before deleting the table
* @param none
* @return none
*/
HashChaining::~HashChaining()
{
    for(int i=0;i<hashTableSize;i++){
        Course *current = hashTable[i];
        Course *temp = current;
        while(current!=NULL){
                current = current->next;
                delete temp;
                temp = current;
            }
    }
    delete[] hashTable;
}

/**
* hash - calculates the hash key based on the course number
* @param courseNumber
* @return int
*/
int HashChaining::hash(int courseNumber)
{
    int hashKey = courseNumber % hashTableSize;
    return hashKey;
}

/**
* bulkInsert - reads and parses the file then hashes the course and inserts it into the hashtable. 
*    If the bucket is already populated, the function uses a linked list to implement chaining and adds the coruse to the end
* @param filename
* @return none
*/
void HashChaining::bulkInsert(string filename)
{
    ifstream in_file {filename};
    if(!in_file){   // check to see if the file was oppened
        cout << "Failed to open the file." << endl;
        return;   
    }

    int numCollisons = 0;
    int numSearch = 0;
    string fileValues;

    getline(in_file, fileValues); // read the first line and ignore it

    while(getline(in_file, fileValues)){
        istringstream stringParser(fileValues);
        int sizeOfLine = 7;
        string courseValues [sizeOfLine];
        
        for(int i = 0; i < sizeOfLine-1; i++){
            getline(stringParser, courseValues[i], ',');
        }   
        getline(stringParser, courseValues[6], '\r');


        int courseBucket = hash(stoi(courseValues[2]));
        
        Course *newNode = new Course(stoi(courseValues[0]), courseValues[1], stoi(courseValues[2]), courseValues[3]);
        string profName = courseValues[5] + " " + courseValues[6];

        if(hashTable[courseBucket] != NULL){ // check if the bucket it empty, if not add it to the linked list
            numCollisons++;
            numSearch++;

            Course *tempNode = hashTable[courseBucket];
            while(tempNode->next != NULL){
                numSearch++;
                tempNode = tempNode->next;
            }

            tempNode->next = newNode;
            newNode->previous = tempNode;
        }else{
            hashTable[courseBucket] = newNode;
        }

        Professor* desiredProfessor = profDb.searchProfessor(courseValues[4]);
        if(desiredProfessor == NULL){ // if the professor doesnt exist add it to the BST
            profDb.addProfessor(courseValues[4], profName);
            desiredProfessor = profDb.searchProfessor(courseValues[4]);
        }

        desiredProfessor->coursesTaught.push_back(newNode); 
        newNode->prof = desiredProfessor;
    }
      
    cout << "[CHAINING] Hash table populated" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Collisions using chaining: " << numCollisons << endl;
    cout << "Search operations using chaining: " << numSearch << endl << endl;
}

/**
* search - takes a user input and hashes the courseNumber to see if that course exists. 
*   If the element at the hashed bucket does not match the other parameters, the linked list is traversed to find if the course exists
*   The function calls displayInfo() once traversal is compelete
* @param courseYear 
* @param courseNumber 
* @param profId
* @return none
*/
void HashChaining::search(int courseYear, int courseNumber, string profId)
{
    cout << "[CHAINING] Search for a course" << endl;
    cout << "-------------------------------------" << endl;

    int courseBucket = hash(courseNumber);
    int numSearch = 0;
    bool foundCoruse = false;
    Course *current = hashTable[courseBucket];

    while(current != NULL){ // traverse the linked list
        if(current->year == courseYear && current->prof->profId == profId){
            foundCoruse = true;
            break;
        }
        numSearch++;
        current = current->next;
    }
    
    if(foundCoruse == false){
        current = NULL;
    }else{
        cout << "Search operations using chaining: " << numSearch << endl;
    }

    displayCourseInfo(current);
}

/**
* displayAllCourses - loops through each bucket in the hash table and displays it if it is not empty. 
*   The funciton also checks the linked list at each bucket and prints it before moving to the next bucket
* @param none
* @return none
*/
void HashChaining::displayAllCourses()
{
    cout << "[CHAINING] Display all courses" << endl;
    for(int i = 0; i < hashTableSize; i++){
        if(hashTable[i] != NULL){
            Course *temp = hashTable[i];
            cout << temp->year << " " << temp->courseName << " " << temp->courseNum << " " << temp->prof->profName << endl;
            while(temp->next){
                temp = temp->next;
                cout << temp->year << " " << temp->courseName << " " << temp->courseNum << " " << temp->prof->profName << endl;
            }
        }
    }
}

/**
* displayCourseInfo - takes the input paramater and accesses course members to print their values to the console if it exists
* @param *c
* @return none
*/
void HashChaining::displayCourseInfo(Course* c)
{
    if(c == NULL){
        cout << "Sorry the course was not found." << endl;
    }else{
       cout << c->year << " " << c->courseName << " " << c->courseNum << " " << c->prof->profName << endl;
    }
}