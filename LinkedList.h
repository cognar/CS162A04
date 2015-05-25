#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct Node
{
	void* data_;
	Node* prev_;
	Node* next_;

    Node()
    {
        data_   = 0;
        prev_   = 0;
        next_   = 0;
    }
};


class LinkedList
{
private:
    Node* first_;
    Node* last_;
    long listLen_;

public:
    LinkedList();
    ~LinkedList();
    void AddLinkToBack(void* ptr);
    void* RemoveThisLink(Node* node);
    void* RemoveLinkFromFront();
    Node* GetFirstNode();
    long GetListLength();
};


#endif // LINKEDLIST_H
