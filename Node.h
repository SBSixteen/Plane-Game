#pragma once
#include "GameObject.h"

class Node
{
public:
	Node* Next;
	GameObject* G;

	Node(GameObject* G) {
		Next = nullptr;
		this->G = G;
	}

};

