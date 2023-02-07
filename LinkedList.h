#pragma once
#include "Node.h"
class LinkedList
{
public:
	Node* Head;
	int length;
	LinkedList();
	void insertHead(GameObject* G);
	void deleteIndex(int i);
	GameObject* at(int i);

};

