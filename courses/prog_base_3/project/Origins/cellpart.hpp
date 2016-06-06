#ifndef CELLPART_H_INCLUDED
#define CELLPART_H_INCLUDED

#include "GlobalHeader.hpp"

//class FoodRenderChunk;
class CellPart {
public:
	CircleShape* shape;
	CellPart* parent = NULL;
	//FoodRenderChunk* curChunk;
	CellPart(CircleShape* shape, CellPart* parent);
};

#endif
