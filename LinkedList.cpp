#include <iostream>
#include "LinkedList.h"

LinkedList::LinkedList(){
    first_ = 0;
    last_ = 0;
    listLen_ = 0;

}

LinkedList::~LinkedList(){
    //Deconstructor is declared in header but is not needed.
}

void LinkedList::AddLinkToBack(void* ptr){       //Add node to end of list{
        Node *newNode = new Node();
        if(newNode == 0){    //Abort is memory allocation fails.
            std::cout << "Memory allocation failed.\n";
            return;
        }
        newNode->data_ = ptr;
        newNode->next_ = 0;     //since node is at the end, next points to 0
        if(listLen_ == 0){       //If no stars are loaded this node will be the first and last node
            first_ = newNode;
            last_ = newNode;
            newNode->prev_ = 0;
        }
        else{       //Append existing list
            last_->next_ = newNode;
            newNode->prev_ = last_;
            last_ = newNode;
        }
        listLen_++;
}

void* LinkedList::RemoveLinkFromFront(){
    void *ptr = 0;
    if(first_->data_ != 0){      //If first_->data_ == 0 there are no Nodes to return
        ptr = first_->data_;    //store first star in temp pointer
        Node *nextFirst = first_->next_;     //Store second entry in list
        delete first_;
        first_ = nextFirst;     //Set first_ to second element (new first element) of list
        listLen_--;
    }
    return ptr;     //Return ptr to the removed node.
}

Node* LinkedList::GetFirstNode(){
    return first_;
}

long LinkedList::GetListLength(){
    return listLen_;
}

void* LinkedList::RemoveThisLink(Node *node){
    void *ptr = 0;

    if(listLen_ == 0){
        std::cout << "No node to remove." << std::endl;
    }
    else if(node->next_ == 0){   //if removing last node;
        last_ = node->prev_;
        (node->prev_)->next_ = 0;
    }
    else if(node->prev_ == 0){   //if removing first node
        first_ = node->next_;
        (node->next_)->prev_ = 0;
    }
    else{   //if removing node in middle
        (node->prev_)->next_ = node->next_;     //point the next attribute of the previous node to where nodes next points
        (node->next_)->prev_ = node->prev_;     // same but with previous
    }
    ptr = node->data_;      //node to return
    delete node;
    listLen_--;
    return ptr;
}
