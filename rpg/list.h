#pragma once
#include <iostream>

using namespace std;

template<class T>
struct node {
	node<T>* next;
	T data;
};

template<class T>
class list
{
public:
	node<T>* first;
	node<T>* last;
	list<T>() {
		first = NULL;
		last = NULL;
	}

	void add(T data) {
		if (!first) {
			// The list is empty
			first = new node<T>;
			first->data = data;
			first->next = NULL;
			last = first;
		}
		else {
			// The list isn't empty
			if (last == first) {
				// The list has one element
				last = new node<T>;
				last->data = data;
				last->next = NULL;
				first->next = last;
			}
			else {
				// The list has more than one element
				node<T>* insdata = new node<T>;
				insdata->data = data;
				insdata->next = NULL;
				last->next = insdata;
				last = insdata;
			}
		}

	}

	T get(int index) {
		if (index == 0) {
			// Get the first element
			return first->data;
		}
		else {
			// Get the index'th element
			node<T>* curr = this->first;
			for (int i = 0; i < index; ++i) {
				curr = curr->next;
			}
			return curr->data;
		}
	}

	// function to create and return a Node 
	node<T>* getNode(T data)
	{
		// allocating space 
		node<T>* newNode = new node<T>();

		// inserting the required data 
		newNode->data = data;
		newNode->next = NULL;
		return newNode;
	}

	// function to insert a Node at required position 
	void insert(int index, T data)
	{
		node<T> **current = &first;

		// This condition to check whether the 
		// position given is valid or not. 
		if (index < 1 || index > size() + 1)
			cout << "Invalid position!" << endl;
		else {

			// Keep looping until the pos is zero 
			while (index--) {

				if (index == 0) {

					// adding Node at required position 
					node<T>* temp = getNode(data);

					// Making the new Node to point to  
					// the old Node at the same position 
					temp->next = *current;

					// Changing the pointer of the Node previous  
					// to the old Node to point to the new Node 
					*current = temp;
				}
				else
					// Assign double pointer variable to point to the  
					// pointer pointing to the address of next Node  
					current = &(*current)->next;
			}
		}

	}

	void removeFirstNode() {
		if (first == NULL)
			return;

		// move the head pointer to the next node 
		node<T> *temp = first;
		first = first->next;

		delete temp;
	}

	void removeLastNode() {
		if (first == NULL)
			return;

		if (first->next == NULL) {
			delete first;
			--size;
			return;
		}

		// find the second last node 
		node<T> *current = first;
		while (current->next->next != NULL)
			current = current->next;

		// delete last node 
		delete (current->next);

		// change next of second last 
		current->next = NULL;


	}

	void remove(int index)
	{
		// if linked list is empty 
		if (first == NULL)
			return;

		// Store head node 
		node<T>* temp = first;

		// if head needs to be removed 
		if (index == 0)
		{
			removeFirstNode();
			return;
		}

		// find previous node of the node to be deleted 
		for (int i = 0; temp != NULL && i < index - 1; i++)
			temp = temp->next;

		// if position is more than number of ndoes 
		if (temp == NULL || temp->next == NULL)
			return;

		// node temp->next is the node to be deleted 
		// store pointer to the next of node to be deleted 
		node<T> *next = temp->next->next;

		// unlink the node from linked list 
		free(temp->next);  // free memory 

		temp->next = next;  // unlink the deleted node from list 


	}

	int size()
	{
		if (first == NULL && last == NULL) { return 0; }

		node<T>* temp = first;
		int nodeCounter = 0;

		while (temp != NULL)
		{
			nodeCounter = nodeCounter + 1;
			temp = temp->next;
		}
		return nodeCounter;
	}

	T operator[](int index) {
		return get(index);
	}

};