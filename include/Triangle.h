#pragma once
#include "Rectangle.h"
#include "Board.h"
#include "Vertex.h"
#include "Utilities.h"

class Triangle
{
public:
	//constrctors
	Triangle();
	Triangle(const Vertex vertices[3]);
	Triangle(const Vertex& v0, const Vertex& v1, double height);

	//Functions
	Vertex getVertex(int index) const;
	double getLength() const;
	double getHeight() const;

	void draw(Board& board) const;
	double getArea() const;
	Vertex getCenter() const;
	double getPerimeter() const;
	bool scale(double factor);
	Rectangle getBoundingRectangle() const;

private:
	// members
	Vertex m_bottomLeft;
	Vertex m_bottomRight;
	Vertex m_top;

	bool checkValid();
	void setVertex();
};
