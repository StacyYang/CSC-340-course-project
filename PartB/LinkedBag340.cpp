//	LinkedBag340.cpp
//	Created by: CSC340

#include <iostream>
#include <string>
#include <memory>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "LinkedBag.h"
#include "Node.h"


using namespace std;

//deletes the second node in the Linked Bag. 
template<typename ItemType>
bool LinkedBag<ItemType>::removeSecondNode340(){
    
    Node<ItemType>* secondNodePtr = headPtr->getNext();
    bool canRemoveItem = !isEmpty() && (secondNodePtr != nullptr);
    if(canRemoveItem){
        secondNodePtr->setItem(headPtr->getItem());
        Node<ItemType>* nodeToDeletePtr = secondNodePtr;
        headPtr = headPtr->getNext();

        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;

        itemCount--;
    }
    return canRemoveItem;
}


//inserts the new node at the end of the Linked Bag
template<typename ItemType>
bool LinkedBag<ItemType>::addEnd340(const ItemType& newEntry){
    Node<ItemType>* checkNode = headPtr;
    Node<ItemType>* newNode = new Node<ItemType>();
    if(!isEmpty()){
        //loop to get the last position, if position->getNext() is null, then this is the last position
        while(checkNode->getNext() != nullptr){
            checkNode = checkNode->getNext();
        }
        newNode->setItem(newEntry);
        checkNode->setNext(newNode);
        itemCount++;
        return true;
    }else{
        return false;
    }
}

// counts the number of nodes in the Linked Bag iteratively
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Iterative() const{
    int tempCount = 0;
    if(!isEmpty()){
        Node<ItemType>* checkNode;
        for(checkNode = headPtr;  checkNode != nullptr; checkNode = checkNode->getNext()){
            tempCount++;
        }
    }
    return tempCount;
}

//counts the number of nodes in the Linked Bag recursively, use 1 helper function
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const{
    int currentSize = 0;
    Node<ItemType>* checkNode = headPtr;
    if(isEmpty()){
        currentSize = 0;
    }else{
        currentSize = getCurrentSize340RecursiveHelper(checkNode);
    }
    return currentSize; 
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveHelper(Node<ItemType>* checkNode) const{
    int tempCount = 0;
    if(checkNode == nullptr){
        return tempCount;
    }else{
        checkNode = checkNode->getNext();
        tempCount++;
        return tempCount + getCurrentSize340RecursiveHelper(checkNode);
    }
}

//counts the number of nodes in the Linked Bag recursively. This recursive function does not use any helper functions.
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveNoHelper() const{
    int tempCount = 0;
    static Node<ItemType>* checkNode = headPtr;
    if(checkNode != nullptr){
        checkNode = checkNode->getNext();
        tempCount++;
        return tempCount + getCurrentSize340RecursiveNoHelper();
    }else{
        return 0;
    }
}

//recursively counts the number of times an entry appears in the Linked Bag      Use 1 helper function
template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType& checkEntry) const{
    Node<ItemType>* checkNode = headPtr;
    if(isEmpty()){
        return 0;
    }else{
        return getFrequencyOf340RecursiveHelper(checkNode, checkEntry);
    }
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveHelper(Node<ItemType>* checkNode, const ItemType& checkEntry) const{
    int frequency = 0;
    if(checkNode == nullptr){
        return 0;
    }else{
        if(checkEntry != checkNode->getItem()){
            checkNode = checkNode->getNext();
            return frequency + getFrequencyOf340RecursiveHelper(checkNode, checkEntry);
        }else{
            frequency++;
            checkNode = checkNode->getNext();
            return frequency + getFrequencyOf340RecursiveHelper(checkNode, checkEntry);
        }
    }
}

//recursively counts the number of times an entry appears in the Linked Bag. This recursive function does not use any helper functions
template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveNoHelper(const ItemType& checkEntry) const{
    static Node<ItemType>* checkNode = headPtr;
    int frequency = 0;
    if(isEmpty()){
        return 0;
    }else{
        if(checkNode == nullptr){
            return 0;
        }else{
            if(checkEntry != checkNode->getItem()){
                checkNode = checkNode->getNext();
                return frequency + getFrequencyOf340RecursiveNoHelper(checkEntry);
            }else{
                frequency++;
                checkNode = checkNode->getNext();
                return frequency + getFrequencyOf340RecursiveNoHelper(checkEntry);
            }
        }
    }
    return frequency;
}


//removes a random entry from the Linked Bag
template<typename ItemType>
ItemType LinkedBag<ItemType>::removeRandom340(){
    
}
	
	
	
    
	
