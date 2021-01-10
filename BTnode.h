#pragma once
#include <iostream>

using namespace std;
//BINARY TREE NODE CLASS WITH A LEFT AND RIGHT POINTER.
class BTnode 
{
public:
	BTnode(char value); //constuctor 
	char data;
	BTnode* right;
	BTnode* left;

}