#pragma once
#include "Window.h"
#include "Rectangle.h"

Window::Window()
{
	checkValid();
}

Window::Window(const Rectangle& outer, const Rectangle& inner)
	:m_outer(outer),m_inner(inner)
{
	checkValid();
}

Window::Window(const Rectangle& outer, double verticalThickness, double horizontalThickness)
	:m_outer(outer)
{
	if(verticalThickness >= outer.getHeight() / 2 || horizontalThickness >= outer.getWidth() / 2 )
		return;

	Vertex outerStart = m_outer.getBottomLeft();
	//Vertex outerEnd = m_outer.getTopRight();

	Vertex newStart = Vertex(outerStart.m_col + horizontalThickness, outerStart.m_row + verticalThickness);
	//Vertex newEnd = Vertex(outerEnd.m_col - horizontalThickness, outerEnd.m_row + verticalThickness);
	//m_inner = Rectangle(newStart, newEnd);
	m_inner = Rectangle(newStart, outer.getWidth() - 2 * horizontalThickness, outer.getHeight() - 2 * verticalThickness);

}

Vertex Window::getBottomLeft() const
{
	return m_outer.getBottomLeft();
}

Vertex Window::getTopRight() const
{
	return m_outer.getTopRight();
}

double Window::getVerticalThickness() const
{
	return (m_outer.getHeight() - m_inner.getHeight()) / 2;
}

double Window::getHorizontalThickness() const
{
	return (m_outer.getWidth() - m_inner.getWidth()) / 2;
}

void Window::draw(Board& board) const
{
	m_inner.draw(board);
	m_outer.draw(board);
}

double Window::getArea() const
{
	return  m_outer.getArea() - m_inner.getArea();
}

Vertex Window::getCenter() const
{
	return m_inner.getCenter();
}

double Window::getPerimeter() const
{
	return m_inner.getPerimeter() + m_outer.getPerimeter();
}

bool Window::scale(double factor)
{
	if (factor < 0)
		return false;

	bool scaleStatue = true;
	scaleStatue = m_outer.scale(factor);
	if (scaleStatue == true) {
		m_inner.scale(factor);
	}
	return scaleStatue;
}

Rectangle Window::getBoundingRectangle() const
{
	return m_outer.getBoundingRectangle();
}

bool Window::checkValid()
{	
	if ((m_inner.getWidth() + (getHorizontalThickness()* 2)  > m_outer.getWidth()) ||
		(m_inner.getHeight() + (getVerticalThickness() * 2) > m_outer.getWidth()))
	{
		setVertex();
		return false;
	}

	else if ((m_inner.getCenter().m_col != m_outer.getCenter().m_col ||
		(m_inner.getCenter().m_row != m_outer.getCenter().m_row)))
	{
		setVertex();
		return false;
	}
	
}

void Window::setVertex()
{
	// frist rectangle
	Vertex bottomLeft1(20, 10);
	Vertex topRight1(30, 20);

	// second rectangle
	Vertex bottomLeft2(20, 10);
	Vertex topRight2(30, 20);

	Vertex outterRectangle[2] = { bottomLeft1, topRight1 };
	Vertex innerRectangle[2] = { bottomLeft2, topRight2 };

	// bulid two rectangle 
	m_outer = Rectangle(outterRectangle);
	m_inner = Rectangle(innerRectangle);
}




