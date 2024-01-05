#pragma once
#include <Vertex.h>
#include <Board.h>
#include <Rectangle.h>


class Window {
public:

	Window();
	Window(const Rectangle& outer, const  Rectangle& inner);
	Window(const Rectangle& outer, double verticalThickness, double horizontalThickness);


	Vertex getBottomLeft()const;
	Vertex getTopRight()const;
	double getVerticalThickness()const;
	double getHorizontalThickness()const;


	void draw(Board& board) const;
	double getArea() const;
	Vertex getCenter()const;
	double getPerimeter()const;
	bool scale(double factor);
	Rectangle getBoundingRectangle()const;

private:

	Rectangle m_outer;
	Rectangle m_inner;
	bool checkValid();
	void setVertex();;
};

