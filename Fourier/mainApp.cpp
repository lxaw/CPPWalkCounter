/*
Written (with love) by Lex Whalen
*/

#include <iostream>

#include "WalkCounter.h"


int main()
{
	WalkCounter p;
	p.promptVertexCount();
	p.promptVertices();
	p.printVertices();
	p.makeAdjMat();
	p.printAjdMat();
	p.promptWalks();
}

