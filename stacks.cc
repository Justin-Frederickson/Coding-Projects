// I pledge my honor that I have abided by the Stevens Honor System - Justin Frederickson

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


class Stack {

public: 
	Chunk *top;

	Stack() {

	        top = NULL;
	}
  
  void push(int x) {


	Chunk *temp = new Chunk;
	temp->value = x;

	if(top == NULL) {
	   top = temp; 

	}

	else {
	   temp->next = top;
	   top = temp;
	}
	
	cout << "Just added a new element: " << top->value << endl;

   }

void pop() {

	if(top == NULL) {
		cout << "Nothing to delete. Empty Stack. " << endl;
	}

	else {
	   Chunk *temp;
	   temp = top;
	   top = top->next;
	   cout << "About to delete: " << temp->value << endl;
	   delete temp;
	
	}		

}


void display () {
	   Chunk *temp;
	   temp = top;

 	   while(temp != NULL) {
		cout << temp->value << endl;
		temp = temp->next;

	}
}


};



int main() {

	Stack S;
	int choice, value;

	while(1) {
		cout << "Press 1 to push to stack" << endl;
		cout << "Press 2 to pop from the stack" << endl;
		cout << "Press 3 to display contents" << endl;
		cout << "Anything else to quit" << endl;
		cin >> choice;

		switch(choice) {
			case 1: cout << "Push what?" << endl;
				cin >> value;
				S.push(value);
				break;

			case 2: S.pop();
				break;

			case 3: S.display();
				break;

			default: cout << "Goodbye!" << endl;
				exit(1);
		}
	}



}
