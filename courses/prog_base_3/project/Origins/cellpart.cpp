#include "cellpart.hpp"

CellPart::CellPart(CircleShape* shape, CellPart* parent) {
	this->shape = shape;
	this->parent = parent;
}
