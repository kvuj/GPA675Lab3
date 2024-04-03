#pragma once
#ifndef TREE_H
#define TREE_H

#include <functional>

#include <QPainter>

#include "Branch.h"
#include "Wind.h"

class Tree
{
public:
	Tree(size_t treeDepth
		, std::function<size_t()> children
		, std::function<double()> attachDist
		, std::function<double()> angle
		, std::function<double()> length
		, std::function<double()> widthBase
		, std::function<double()> widthPoint
		, double lengthVal
		, double widthBaseVal
		, double widthPointVal
		, int positionX
		, int positionY
		, Wind* wind);
	virtual ~Tree();
	Tree(const Tree& tr) = delete;
	Tree(Tree&& tr) noexcept;
	Tree& operator=(const Tree& tr) = delete;
	Tree& operator=(Tree&& tr) noexcept;

	virtual void tic();
	virtual void draw(QPainter* painter) const;
	virtual void setColor(QColor color);
	virtual void setDensity(double density);
	virtual void setDeformationResistance(double deformationResistance);
	virtual QPoint getPosition() const;
	virtual void setPosition(QPoint position);
	virtual void setLenght(double lenght);
private:
	std::unique_ptr<Branch> mTrunk;
	QPoint mBasePosition;
	Wind* mWind;

	size_t mTotalHeight = 0.0; //à modifier dans les essences
	size_t mTotalBranch=0.0;
	double mDensity=0.0;
	double mDeformationResistance=0.0; //à modifier dans les essences

};

#endif