#include <iostream>
#include <cstring>
#include <stack>
#include "BTnode.h"

using namespace std;

//create struct for the node that we need to work with using the algorithm
struct Node {
	char data;
	Node* next;
};

//take in mathmatical expression entered with infix notation
//take mathmatical expression ---> translate to postfix
///take postfix ------> create expression tree
//allow user to output expression as infix, prefix, or postfix notation
// print the notation using the expression tree (recursive print from the expression tree)





int main() {
	//pointers to top of stack
	Node* top = NULL;
	//pointers in queue
	Node* front = NULL;
	Node* end = NULL;

	//take input in from user
	char* input = new char()
	//create an output
	char output[100];
	//set output chars to null character
	memset(output, '\0', 100);

	cout << "Welcome to the Binary Expression Trees using the Stunting Yard Algorithm!" << endl;
	cout << "Enter a mathmatical expression in infix notation with spaces between each character." << endl;
	//get input until the new line
	cin.getline(input, 80, '\n');
	//use a postfix function to translate expression into postfix notation
	cout << "The postfix expression for your input is: " << endl;
	//print output
	cout << output << endl;
	bool running = true;
	BTnode* head = constructTree(output);

	while (running) {
		cout << "\nWhat would you like to do? Type 1, 2, 3, or 4 (1 - Convert to infix, 2 - Convert to prefix, 3 - Convert to postfix, 4 - QUIT)" << endl;
		cin.getline(input, 80, '\n');
		if (strcmp(input, "1") == 0) {
            infix(head);
        }
        else if (strcmp(input, "2") == 0) {
            prefix(head);
        }
        else if (strcmp(input, "3") == 0) {
            postfix(head);
        }
        else {
            cout << "Thanks for hanging! See you next time!\n";
            running = false;
        }

	}
}	

//Push, which adds an element to the collection
void push(char value, Node* &top) {
	Node* node = new Node();
	node->data = value;
	node->next = top;
	top = node;
}

//Pop, which removes the most recently added element that was not yet removed.
void pop(Node* &top) {
	Node* temp = top;
	if(temp == NULL) {
		cout << "Stack is empty." << endl;
	}
	else {
		//pops the current top to the next top
		top = top->next;
		delete temp;
	}
}

//peek at the top of the stack
int peek(Node* &top) {
	return top->data;
}

bool isOperator(char c) {
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        return true;
    }
    else { 
    	return false; 
    }
}

// returns the precedence of each operator
int getPrecedence(char c) {
    if (c == '^') {
        return 4;
    }
    else if (c == '*' || c == '/') {
        return 3;
    }
    else if (c == '+' || c == '-') {
        return 2;
    }
    else {
        return 0;
    }
}

BTnode* constructTree(char output[]) {
	stack<BTnode*> stack;
	BTnode *head, *left, *right;

	for (int i = 0; i < strlen(output); i++) {
		if (c != ' ') {
			//if its an operand, then push into stack
			if(!isOperator(output[i])) {
				head = new BTnode(output[i]);
				stack.push(head);
			}
			else { //otherwise if its a operator 
				head = new BTnode(output[i]);
				//pop the two top nodes
				right = stack.top(); //store top
				stack.pop();
				left = stack.top; 
				stack.pop();

				// make them children
				head->right = right;
				head->left = left;

				//add this subexpression to stack
				stack.push(head);
				
			}
		}
	}
	head = stack.top();
    stack.pop();
    // returns the head of the  tree
    return head;
}


void inToPost(char* input, Node* &top, Node *&front, Node* &back) {
	for (int i = 0; input[i] != "\0"; i++) {
		if (i != ' ') {
			if (isOperator(input[i])) {
				if (top != NULL) {
					while (top != NULL && getPrecedence(top->data) > getPrecedence(input[i]) || getPrecedence(top->data) == getPrecedence(input[i]) && top->data != '(') {
						enqueue(top->data, front, back);
						pop(top);
						if(top == NULL) {
							break;
						}
					}
				}
				push(input[i], top);
			}
			else if (input[i] == '(') {
				push(input[i], top);
			}
			else if (input[i] == ')') {
				 while (top->data != '(') {
                    enqueue(top->data, front, back);
                    pop(top);
                }
                if (top->data == '(') {
                    pop(top);
                } 
            }
            //numbers are put into the queue
            else {
                enqueue(i, front, back);
            }
        }
    }
    while (top != NULL) {// push anything left to the queue
        enqueue(top->data, front, back);
        pop(top);
    }
}


//add to the queue
void enqueue(char value, Node* &front, Node* &back) {
	Node *node = new Node();
	node->data = value;

	if (back == NULL) {
		front = node;
		back = node;
	}
	else {
		back->next = node;
		back = node;
	}
}

//removes from queue
void dequeue(Node *&front, Node *&back) {
	if (front == NULL) {
		return;
	}
	Node *temp = front;
	front = front->next;
	if (front == NULL) {
		rear == NULL;
	}
	delete temp;
}

void postfix(BTnode* head) {
	if (head) {
		postfix(head->left);
		postfix(head->right);
		cout << head->data << " ";
	}
}


