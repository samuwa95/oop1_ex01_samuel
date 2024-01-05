#pragma once
#include "Board.h"
#include "Vertex.h"
#include "Utilities.h"
#include "macros.h"

class Rectangle
{
public:
	// Constructors
	Rectangle();
	Rectangle(const Vertex& bottomLeft, const Vertex& topRight);
	Rectangle(const Vertex vertices[2]);
	Rectangle(double x0, double y0, double x1, double y1);
	Rectangle(const Vertex& start, double width, double height);

	//Functions
	Vertex getBottomLeft() const;
	Vertex getTopRight() const;
	double getWidth() const;
	double getHeight() const;

	double getArea() const;
	double getPerimeter() const;
	Vertex getCenter() const;
	bool scale(double factor);
	Rectangle getBoundingRectangle() const;
	void draw(Board& board) const;

private:
	//Members
	Vertex m_bottomLeft;
	Vertex m_topRight;

	bool checkValid();
	void setVertex();
};