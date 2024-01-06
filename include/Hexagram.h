#pragma once
#include "Board.h"
#include "Vertex.h"
#include "Utilities.h"
#include "macros.h"
#include "Triangle.h"

class Hexagram
{
public:

	//consttactors
	Hexagram();
	Hexagram(Vertex firstTriangle[3], Vertex secondTriangle[3]);
	Hexagram(const Triangle& t1, const Triangle& t2);

	//functons
	double getTotalHeight()const;
	double getLength()const;

	double getArea() const;
	double getPerimeter() const;
	Vertex getCenter() const;
	bool scale(double factor);
	Rectangle getBoundingRectangle() const;
	void draw(Board& board) const;

private:
	// members
	Triangle m_firstTriangle;
	Triangle m_secondTriangle;

	bool checkValid();
	void setVertex();
};