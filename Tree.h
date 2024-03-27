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
	~Tree();
	Tree(const Tree& tr) = delete;
	Tree(Tree&& tr) noexcept;
	Tree& operator=(const Tree& tr) = delete;
	Tree& operator=(Tree&& tr) noexcept;

	void tic();
	void draw(QPainter* painter) const;

private:
	Branch* mTrunk;
	QPoint mBasePosition;
	Wind* mWind;

	// TODO: Initialise
	size_t mTotalHeight;
	size_t mTotalBranch;
	double mDensity;
	double mDeformationResistance;
};

#endif