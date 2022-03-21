//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: ProfBST.cpp
//-----------------------------------------------------------------------------

#include "ProfBST.h"

#include <iostream>

using namespace std;

/**
* ProfBST - default constructor that sets the root to NULL
* @param none
* @return none
*/
ProfBST::ProfBST()
{
    root = NULL;
}

/**
* destructorHelper - rescursively deleltes each node of tree by traversing through both left and right sides
* @param *node
* @return none
*/
void destructorHelper(Professor* node){
    if(node != NULL){ //delete each node in the tree untill there are no nodes left
        destructorHelper(node->left);
        destructorHelper(node->right);
        delete node;
    }
    node = NULL;
}

/**
* ~ProfBST - destructor for the BST that calls destructorHelper
* @param none
* @return none
*/
ProfBST::~ProfBST()
{
    destructorHelper(root);
}

/**
* addProfessor - calls addProfessorHelper to add a new node to the tree
* @param profId
* @param profName
* @return none
*/
void ProfBST::addProfessor(string profId, string profName)
{
    root = addProfessorHelper(root, profId, profName);
}

/**
* searchProfessor - calls the searchProfessorHelper to find the desried node then retruns the node if found
* @param profId
* @return *desiredProfessor
*/
Professor* ProfBST::searchProfessor(string profId)
{
    Professor* desiredProfessor = searchProfessorHelper(root, profId);
    return desiredProfessor;
}

/**
* publicSearchProfessor - calls searchProfessor and then displayProfessorInfo to find and print the information for a wanted professor
* @param profId
* @return none
*/
void ProfBST::publicSearchProfessor(string profId)
{ 
    Professor* targetProfessor = searchProfessor(profId);
    displayProfessorInfo(targetProfessor);
    cout << endl;
}

/**
* displayProfessorInfo - acesses private members of the professor class to print the information of the pointer to the professor 
* @param *p
* @return none
*/
void ProfBST::displayProfessorInfo(Professor* p)
{ 
    if(p == NULL){
        cout << "Professor not found." << endl;
    }else{
        cout << "Name:" << p->profName << endl;
        for(int i = 0; i < p->coursesTaught.size(); i++){
            cout << "- " << p->coursesTaught.at(i)->courseNum << ": "
                << p->coursesTaught.at(i)->courseName << ", "
                << p->coursesTaught.at(i)->year << endl;
        }
    }
}

/**
* searchProfessorHelper - recursively loops through each side of the tree to find a professor that matches the given profId
* @param *node 
* @param profId
* @return *node
*/
Professor* ProfBST::searchProfessorHelper(Professor* node, string profId){
    if(node == NULL){ //if there are no nodes return NULL
        return NULL;
    }else if(node->profId == profId){ //check the node
        return node;
    }else if(node->profId > profId){ //check left tree
        return searchProfessorHelper(node->left, profId);
    }else if(node->profId < profId){  //check right tree
        return searchProfessorHelper(node->right, profId);
    }
    return node;
}

/**
* addProfessorHelper - recursively loops through each side of the tree to find where to insert the new professor 
* @param *node 
* @param profId
* @param profName
* @return *node
*/
Professor* ProfBST::addProfessorHelper(Professor* node, string profId, string profName){
    if(node == NULL){ //create a new node if the current node is a leaf node
        return (new Professor(profId, profName));
    } else if(node->profId < profId){ // the right subtree will contain profId > node.profId
        node->right = addProfessorHelper(node->right, profId, profName);
    }
    else if(node->profId > profId){ // a node X’s left subtree will contain profId < node.profId
        node->left = addProfessorHelper(node->left, profId, profName);
    }
    return node;
}
