#pragma once
#include "Rectangle.h"

Rectangle::Rectangle(const Vertex& bottomLeft, const Vertex& topRight)
	: m_bottomLeft(bottomLeft), m_topRight(topRight)
{
	checkValid();
}

Rectangle::Rectangle(const Vertex vertices[2])
	: Rectangle(vertices[0], vertices[1])
{
	checkValid();
}

Rectangle::Rectangle(double x0, double y0, double x1, double y1)
	: m_bottomLeft(x0, y0), m_topRight(x1, y1)
{
	checkValid();
}

Rectangle::Rectangle(const Vertex& start, double width, double height)
	: m_bottomLeft(start), m_topRight(start.m_col + width, start.m_row + height)
{
	checkValid();
}

bool Rectangle::checkValid()
{
	if (!m_bottomLeft.isValid() || !m_topRight.isValid())
	{
		setVertex();
		return false;
	}
	else if (m_bottomLeft.isHigherThan(m_topRight))
	{
		setVertex();
		return false;
	}
	else if (m_bottomLeft.isToTheRightOf(m_topRight))
	{
		setVertex();
		return false;
	}

	return true;
}

void Rectangle::setVertex()
{
	m_bottomLeft.m_col = 20;
	m_bottomLeft.m_row = 10;
	m_topRight.m_col = 30;
	m_topRight.m_row = 20;
}

Vertex Rectangle::getBottomLeft() const
{
	return m_bottomLeft;
}

Vertex Rectangle::getTopRight() const
{
	return m_topRight;
}

double Rectangle::getWidth() const
{
	return m_topRight.m_col - m_bottomLeft.m_col;
}

double Rectangle::getHeight() const
{
	return m_topRight.m_row - m_bottomLeft.m_row;
}

void Rectangle::draw(Board& board) const
{
	Vertex bottomRight;
	bottomRight.m_col = m_topRight.m_col;
	bottomRight.m_row = m_bottomLeft.m_row;

	Vertex topLeft;
	topLeft.m_col = m_bottomLeft.m_col;
	topLeft.m_row = m_topRight.m_row;

	board.drawLine(m_bottomLeft, bottomRight);
	board.drawLine(bottomRight, m_topRight);
	board.drawLine(m_topRight, topLeft);
	board.drawLine(topLeft, m_bottomLeft);
}

Rectangle Rectangle::getBoundingRectangle() const
{
	return *this;
}

double Rectangle::getArea() const
{
	return getWidth() * getHeight();
}

Vertex Rectangle::getCenter() const
{
	Vertex center;
	center.m_col = (m_topRight.m_col + m_bottomLeft.m_col) / 2;
	center.m_row = (m_topRight.m_row + m_bottomLeft.m_row) / 2;
	return center;
}

double Rectangle::getPerimeter() const
{
	double width = getWidth();
	double height = getHeight();
	return (width * 2) + (height * 2);
}

bool Rectangle::scale(double factor)
{
	if (factor < 0)
		return false;

	Vertex NewBottomLeft, NewTopRight;
	Vertex center = getCenter();

	double scaleDiffCol = (center.m_col - m_bottomLeft.m_col) * factor;
	double scaleDiffRow = (center.m_row - m_bottomLeft.m_row) * factor;

	NewBottomLeft.m_col = center.m_col - scaleDiffCol;
	NewBottomLeft.m_row = center.m_row - scaleDiffRow;

	NewTopRight.m_col = center.m_col + scaleDiffCol;
	NewTopRight.m_row = center.m_row + scaleDiffRow;

	if (NewBottomLeft.isValid() && NewTopRight.isValid())
	{
		m_bottomLeft = NewBottomLeft;
		m_topRight = NewTopRight;
		return true;
	}
	return false;
}

