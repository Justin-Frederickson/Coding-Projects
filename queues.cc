//I pledge my honor that I have abided by the Stevens Honor Society - Justin Frederickson

#include <iostream>
using namespace std; 

class Chunk {
public:

	int value;
	Chunk *next;
	
	Chunk () {

	   value = -1;
	   next = NULL;

	}

};

class Queue {
public: 

	Chunk *head;
        Chunk *tail;
	
	Queue() {

	   head = NULL;
	   tail = NULL;
	
	}
   void enqueue(int x) {
	
	Chunk *temp = new Chunk;
	temp->value = x;

	if(head == NULL) {

	   head = temp;
	   tail = temp;

	}

	else {

	   tail->next = temp;
	   tail = temp;
	   

	}

  }
  
 void dequeue() {

    Chunk *temp;
    
	if(head == NULL) {

	  cout << "Empty queue, nothing to delete" << endl;

	}

	else {

	  temp = head;
	  head = temp->next;
	  
	   cout << "About to delete: " << temp->value << endl;
	   delete temp; 

	}

  }

  void display () {

	Chunk *temp; 

	if (head == NULL) {

	   cout << "Empty Q" << endl; 

	}

	else {

	   temp = head;
	   cout << "------------" << endl; 
	   
	   while (temp != NULL) {

	     cout << temp->value << "---->";

	     temp = temp->next;

	   }

	   cout << "NULL" << endl; 
	   cout << "-----------------" << endl;

	}

  }

};


int main() {

	Queue Q;

	int choice, value; 

	while(1) {

	   cout << "Press 1 to enqueue" << endl;
	   cout << "press 2 to dequeue" << endl;
	   cout << "Press 3 to display" << endl;
	   cout << "Anything else to Quit" << endl;
	   cin >> choice;

	   switch(choice) {

		case 1: cout << "enqueue what?" << endl; 
			   cin >> value; 
			   Q.enqueue(value);
			   break; 

		case 2: Q.dequeue();
			   break;

		case 3: Q.display();
			   break;

	   default: cout << "Goodbye!" << endl; 
		  exit(1);

		}

	}

}
