#pragma once
#include "Triangle.h"
#include "Rectangle.h"
#include <cmath>

Triangle::Triangle()
{
	checkValid();
}

Triangle::Triangle(const Vertex vertices[3])
	: m_bottomLeft(vertices[0]), m_bottomRight(vertices[1]), m_top(vertices[2])
{
	checkValid();
}


Triangle::Triangle(const Vertex& v0, const Vertex& v1, double height)
	: m_bottomLeft(v0), m_bottomRight(v1)
{
	m_top.m_col = (m_bottomLeft.m_col + m_bottomRight.m_col) / 2;
	m_top.m_row = m_bottomRight.m_row + height;
	checkValid();
}

Vertex Triangle::getVertex(int index) const
{
	switch (index)
	{
	case 0:
		return  m_bottomLeft;
	case 1:
		return m_bottomRight;
	case 2:
	default:
		return m_top;
	}
}

double Triangle::getLength() const
{
	return distance(m_bottomLeft, m_bottomRight);
}

double Triangle::getHeight() const
{
	return abs(m_top.m_row - m_bottomLeft.m_row);
}

void Triangle::draw(Board& board) const
{
	board.drawLine(m_bottomLeft, m_bottomRight);
	board.drawLine(m_bottomRight, m_top);
	board.drawLine(m_top, m_bottomLeft);
}

double Triangle::getArea() const
{
	return (getHeight() * getLength()) / 2;
}

Vertex Triangle::getCenter() const
{
	Vertex center;
	center.m_col = m_top.m_col;
	center.m_row = (m_bottomLeft.m_row + m_top.m_row) / 2;
	return center;
}

double Triangle::getPerimeter() const
{
	return getLength() * 3;
}

bool Triangle::scale(double factor)
{
	if (factor < 0)
		return false;

	Vertex New_m_bottomLeft, New_m_bottomRight, New_m_vertex2;
	Vertex center = getCenter();

	New_m_bottomLeft.m_col = center.m_col - (center.m_col - m_bottomLeft.m_col) * factor;
	New_m_bottomLeft.m_row = center.m_row - (center.m_row - m_bottomLeft.m_row) * factor;

	New_m_bottomRight.m_col = center.m_col + (m_bottomRight.m_col - center.m_col) * factor;
	New_m_bottomRight.m_row = center.m_row + (m_bottomRight.m_row - center.m_row) * factor;

	//New_m_vertex2.m_col = center.m_col + (m_vertex2.m_col - center.m_col) * factor;
	New_m_vertex2.m_col = center.m_col;
	New_m_vertex2.m_row = center.m_row + (m_top.m_row - center.m_row) * factor;

	if (New_m_bottomLeft.isValid() && New_m_bottomRight.isValid() && New_m_vertex2.isValid())
	{
		m_bottomLeft = New_m_bottomLeft;
		m_bottomRight = New_m_bottomRight;
		m_top = New_m_vertex2;
		return true;
	}
	else
		return false;
}

Rectangle Triangle::getBoundingRectangle() const
{
	Vertex topRight;
	Vertex bottomLeft;

	if (m_top.isHigherThan(m_bottomRight))
	{
		topRight = Vertex(m_bottomRight.m_col, m_top.m_row);
		return Rectangle(m_bottomLeft, topRight);
	}

	bottomLeft = Vertex(m_bottomLeft.m_col, m_top.m_row);
	return Rectangle(bottomLeft, m_bottomRight);
}

bool Triangle::checkValid()
{
	
	if (!m_bottomLeft.isValid() || !m_bottomRight.isValid() || !m_top.isValid())
	{
		setVertex();
		return false;
	}
	else if (m_bottomLeft.m_row != m_bottomRight.m_row)
	{
		setVertex();
		return false;
	}
	
	else if (!doubleEqual(distance(m_bottomLeft, m_bottomRight), distance(m_bottomRight, m_top)) ||
		!doubleEqual(distance(m_bottomRight, m_top), distance(m_top, m_bottomLeft)))
	{
		setVertex();
		return false;
	}
	return true;
}

void Triangle::setVertex()
{
	m_bottomLeft = Vertex(20, 20);
	m_bottomRight = Vertex(30, 20);
	m_top = Vertex(25, 20 + sqrt(75));
}


