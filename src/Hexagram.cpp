#pragma once
#include "Hexagram.h"
#include "Triangle.h"

Hexagram::Hexagram()
{
	checkValid();
}

Hexagram::Hexagram(Vertex firstTriangle[3], Vertex secondTriangle[3]):
	Hexagram(Triangle(firstTriangle),Triangle(secondTriangle))
{
}

Hexagram::Hexagram(const Triangle& t1, const Triangle& t2)
	:m_firstTriangle(t1), m_secondTriangle(t2)
{

}

double Hexagram::getTotalHeight() const
{
	Vertex startFrist = m_firstTriangle.getVertex(2);
	Vertex endSecond = m_secondTriangle.getVertex(2);
	return distance(startFrist, endSecond);
}

double Hexagram::getLength() const
{
	return  m_firstTriangle.getLength();
}

double Hexagram::getArea() const
{
	return m_firstTriangle.getArea() * (4/3);
}

double Hexagram::getPerimeter() const
{
	int  lengthHexagram = m_firstTriangle.getLength(); // TODO::
	lengthHexagram = lengthHexagram / 3;
	return (lengthHexagram * 12);
}

Vertex Hexagram::getCenter() const
{
	return m_firstTriangle.getCenter();
}

bool Hexagram::scale(double factor)
{
	if (factor < 0)
		return false;

	//scale each triangle separately
	m_firstTriangle.scale(factor);
	m_secondTriangle.scale(factor);

}

Rectangle Hexagram::getBoundingRectangle() const
{
	Vertex topRight;
	Vertex bottomLeft; // TODO::

	topRight.m_col = m_secondTriangle.getVertex(1).m_col;
	topRight.m_row = m_firstTriangle.getVertex(2).m_row;

	bottomLeft.m_col = m_secondTriangle.getVertex(0).m_col;
	bottomLeft.m_row = m_secondTriangle.getVertex(2).m_row;

	return Rectangle(topRight, bottomLeft);
}

void Hexagram::draw(Board& board) const
{
	m_firstTriangle.draw(board);
	m_secondTriangle.draw(board);
}

bool Hexagram::checkValid()
{
	if (m_firstTriangle.getVertex(2).m_row == m_secondTriangle.getVertex(2).m_row)
	{
		setVertex();
		return false;
	}

	else if ((m_firstTriangle.getCenter().m_col != m_secondTriangle.getCenter().m_col ||
		(m_firstTriangle.getCenter().m_row != m_secondTriangle.getCenter().m_row)))
	{
		setVertex();
		return false; // TODO::
	}
	return true;
}

void Hexagram::setVertex()
{
	// frist triangle
	Vertex bottomLeft1(20, 20);
	Vertex bottomRight1(20, 30);
	Vertex top1(25, 20 + sqrt(75));

	// second triangle
	Vertex bottomLeft2(20, 20 + sqrt(75) * 2/3);
	Vertex bottomRight2(25, 20 - sqrt(75)/3);
	Vertex top2(30, 20 + sqrt(75) * 2 / 3);

	Vertex firstTriangle[3] = { bottomLeft1, bottomRight1, top1 };
	Vertex secondTriangle[3] = { bottomLeft2, bottomRight2, top2 };

	// bulid two triangle
	m_firstTriangle = Triangle(firstTriangle);
	m_secondTriangle = Triangle(secondTriangle);
}


