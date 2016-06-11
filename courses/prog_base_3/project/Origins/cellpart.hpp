#ifndef CELLPART_H_INCLUDED
#define CELLPART_H_INCLUDED

#include "GlobalHeader.hpp"

class CellPart {
public:
	CircleShape* shape;
	CellPart* parent = NULL;
	CellPart* child = NULL;
	bool jumpable = true;
	Vector2f splitVector = Vector2f(0,0);
	CellPart(CircleShape* shape, CellPart* parent);
	CellPart(CircleShape* shape, CellPart* parent, Vector2f splitVector);
};

#endif
