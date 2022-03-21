//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashOpenAddressing.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"

using namespace std;

/**
* HashOpenAddressing - parameterized constructor that creates the hash table and sets each bucket to NULL
* @param size
* @return none
*/
HashOpenAddressing::HashOpenAddressing(int size)
{
    hashTableSize = size;
    hashTable = new Course*[hashTableSize];
    for(int i=0;i<hashTableSize;i++){
        hashTable[i] = NULL;
    }
}

/**
* ~HashOpenAddressing - destructor that loops through each bucket and deletes it
* @param none
* @return none
*/
HashOpenAddressing::~HashOpenAddressing()
{
    for(int i=0;i<hashTableSize;i++){
        delete hashTable[i];
    }
    delete[] hashTable;
}

/**
* hash - calculates the hash key based on the course number
* @param courseNumber
* @return int
*/
int HashOpenAddressing::hash(int courseNumber)
{
    int hashKey = courseNumber % hashTableSize;
    return hashKey;
}

/**
* bulkInsert - reads and parses the file then hashes the course and inserts it into the hashtable. 
*    If the bucket is already populated, the function uses quadratic probing to find an empty bucket that the coruse can be added to
* @param filename
* @return none
*/
void HashOpenAddressing::bulkInsert(string filename)
{
    ifstream in_file {filename};
    if(!in_file){   // check to see if the file was oppened
        cout << "Failed to open the file." << endl;
        return;   
    }
    int numCollisons = 0;
    int numSearch = 0;

    string fileValues;
    getline(in_file, fileValues);

    while(getline(in_file, fileValues)){
        stringstream stringParser(fileValues);
        int sizeOfLine = 7;
        string courseValues [sizeOfLine];
        
        for(int i = 0; i < sizeOfLine-1; i++){
            getline(stringParser, courseValues[i], ',');
        }   
        getline(stringParser, courseValues[6], '\r'); 


        int courseBucket = hash(stoi(courseValues[2]));
        
        Course *newNode = new Course(stoi(courseValues[0]), courseValues[1], stoi(courseValues[2]), courseValues[3]);
        string profName = courseValues[5] + " " + courseValues[6];
        
        if(hashTable[courseBucket] != NULL){ // check if the bucket it empty, if not implement quadratic probing
            numCollisons++;
            int i = 1;

            while(hashTable[courseBucket] != NULL){ // loop through the table until an empty bucket is found
                int newBucket = (courseBucket + (i * i)) % hashTableSize;
                courseBucket = newBucket;
                i++;
                numSearch++;
            }
            hashTable[courseBucket] = newNode;
        }else{
            hashTable[courseBucket] = newNode;
        }

        Professor* desiredProfessor = profDb.searchProfessor(courseValues[4]);
        if(desiredProfessor == NULL){   // if the professor doesnt exist add it to the BST
            profDb.addProfessor(courseValues[4], profName);
            desiredProfessor = profDb.searchProfessor(courseValues[4]);
        }

        desiredProfessor->coursesTaught.push_back(newNode);
        newNode->prof = desiredProfessor; 
    }
     
    cout << "\n[OPEN ADDRESSING] Hash table populated" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Collisions using open addressing: " << numCollisons << endl;
    cout << "Search operations using open addressing: " << numSearch << endl << endl;
}

/**
* search - takes a user input and hashes the courseNumber to see if that course exists. 
*   If the element at the hashed bucket does not match the other parameters, quadratic probing is utilzied to search the buckets that it could have been added to
*   The function calls displayInfo() once traversal is compelete
* @param courseYear 
* @param courseNumber 
* @param profId
* @return none
*/
void HashOpenAddressing::search(int courseYear, int courseNumber, string profId)
{
    cout << "\n[OPEN ADDRESSING] Search for a course" << endl;
    cout << "-------------------------------------" << endl;

    int courseBucket = hash(courseNumber);
    int numSearch = 0;
    bool foundCoruse = false;
    int i = 0;
    Course *current = hashTable[courseBucket];

    while(numSearch != (hashTableSize-1)){
        if(current != NULL && current->year == courseYear && current->prof->profId == profId){
            foundCoruse = true;
            break;
        }
        courseBucket = (courseBucket + (i * i)) % hashTableSize;
        current = hashTable[courseBucket];
        numSearch++;
        i++;
    }
    
    if(foundCoruse == false){
        current = NULL;
    }else{
        cout << "Search operations using open addressing: " << numSearch << endl;
    }

    displayCourseInfo(current);
}

/**
* displayAllCourses - loops through each bucket in the hash table and displays it if it is not empty. 
* @param none
* @return none
*/
void HashOpenAddressing::displayAllCourses()
{
    cout << "[OPEN ADDRESSING] Display all courses" << endl;
    for(int i = 0; i < hashTableSize; i++){
        if(hashTable[i] != NULL){
            cout << hashTable[i]->year << " " << hashTable[i]->courseName << " " << hashTable[i]->courseNum << " " << hashTable[i]->prof->profName << endl;
        }
    }
}

/**
* displayCourseInfo - takes the input paramater and accesses course members to print their values to the console if it exists
* @param *c
* @return none
*/
void HashOpenAddressing::displayCourseInfo(Course* c)
{
	if(c == NULL){
        cout << "Sorry the course was not found." << endl;
    }else{
       cout << c->year << " " << c->courseName << " " << c->courseNum << " " << c->prof->profName << endl;
    }
}