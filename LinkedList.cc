//I pledge my honor that I have abided by the Stevens Honor Society - Justin Frederickson

#include <iostream>
using namespace std; 

class chunk {

public: 
	int value;
	chunk *next;
  
chunk() {

	value =-1; 
	next = NULL;
}

};

class List {

 public:
   chunk *head;

   List(){
     head = NULL;
   }
  
 void insertAtHead(int value){
  chunk *temp = new chunk;
	temp->value = value;


	if(head == NULL) {
	   head = temp; 

	}

	else {
	   temp->next = head;
	   head = temp;
	}
	
	cout << "Just added a new element: " << head->value << endl;
 }

 

 void insertAtPosition(int position, int value){
   chunk *ptr;
   chunk *temp = new chunk;
   temp->value = value;
   ptr = head;    
   int counter = 1;

   while (ptr->next != NULL) {
     if (counter == (position-1)) {
       temp->next = ptr->next;
       ptr->next = temp;
       break;
      
     }
     else {
       ptr = ptr->next;
       counter++;
     }

   }
 }

  
 void removeFromPosition(int position){
   chunk *temp;
   temp = head;
   int counter = 1;

   if (position == 1) {
     head = temp->next;
     delete temp; 
     return;
   }

   for (int i = 1; temp != NULL && i < position-1; i++) {
     temp = temp->next;
   }

   if (temp == NULL || temp->next == NULL) {
     return;
   }

   chunk *ptr = temp->next->next;
   delete temp->next; 
   temp->next = ptr;
 }

   
       
 

 void displayContents(){
   chunk *temp; 

	if (head == NULL) {

	   cout << "Empty List" << endl; 

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

  //I already did #7 (void findAndDelete) on midterm so I am doing #8 and #9

  void reverseList(){
    chunk *temp = head;
    chunk *follow = NULL, *prev = NULL;

    while (temp != NULL){
      follow = temp->next;
      temp->next = prev;
      prev = temp;
      temp = follow;
    }
    head = prev;
  }

  void deleteLinkedList(){
    chunk *temp = head;
    chunk *follow = NULL;

    while (temp != NULL){
      follow = temp->next;
      delete(temp);
      temp = follow;
    }

    head = NULL;
  }
	
    
};

int main() {

  List S;
  int choice, value, position, pos, val;

	while(1) {
		cout << "Press 1 to insert at head" << endl;
		cout << "Press 2 to insert at position" << endl;
		cout << "Press 3 to remove from position" << endl;
		cout << "Press 4 to display contents" << endl;
		cout << "Press 5 to reverse list" << endl;
		cout << "Press 6 to delete entire linked list" << endl;
		cout << "Anything else to quit" << endl;
		cin >> choice;

		switch(choice) {
	       	case 1: cout << "insert what value?" << endl;
				cin >> value;
				S.insertAtHead(value);
				break;
				
		case 2: cout << "Insert what position?" << endl;
		  cin >> pos;
		  cout << "Insert a value: " << endl;
		  cin >> val;
		  S.insertAtPosition(pos, val);
				break;

		case 3: cout << "Remove what position?" << endl;
		  cin >> position;
			  S.removeFromPosition(position);
				break;

	       	case 4: S.displayContents();
		                break;

		case 5: cout << "About to reverse list..." << endl;
		  S.reverseList();
		  break;

		case 6: cout <<"About to delete list" << endl;
		  S.deleteLinkedList();
		  break;

			default: cout << "Goodbye!" << endl;
				exit(1);

	}
	

	}



}
