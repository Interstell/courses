#include "cellpart.hpp"

CellPart::CellPart(CircleShape* shape, CellPart* parent) {
	this->shape = shape;
	this->parent = parent;
}

CellPart::CellPart(CircleShape* shape, CellPart* parent, Vector2f splitVector) {
	this->shape = shape;
	this->parent = parent;
	this->splitVector = splitVector;
}
