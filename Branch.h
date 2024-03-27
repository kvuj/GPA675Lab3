#pragma once
#ifndef BRANCH_H
#define BRANCH_H

#include <functional>
#include <vector>

#include <QColor>
#include <QtMath>
#include <QPainter>
#include <QPoint>
#include <QPolygon>
#include <QTransform>

class Branch
{
public:
	Branch(size_t treeDepth
		, std::function<size_t()> children
		, Branch* parent
		, std::function<double()> attachDist
		, std::function<double()> angle
		, std::function<double()> length
		, std::function<double()> widthBase
		, std::function<double()> widthPoint
		, double lengthVal
		, double widthBaseVal
		, double widthPointVal
		, size_t currentDepth);
	~Branch();
	Branch(const Branch& br) = delete;
	Branch(Branch&& br) = default;
	Branch& operator=(const Branch& br) = delete;
	Branch& operator=(Branch&& br) = default;

	void draw(QPainter* painter) const;
	void updatePolygon();

private:
	size_t mTreeDepth;
	size_t mChildrenCount;
	Branch* mParent;
	std::vector<Branch*> mChildren;
	double mLinearAttachDistance;		// % [0, 1]
	double mAngleBetweenParent;			// RAD
	double mVarLength;					// % [0, 1]
	double mVarWidthBase;				// % [0, 1]
	double mVarWidthPoint;				// % [0, 1]
	// TODO: Modification couleur

	// TODO: Retirer si 100% relatif
	// QPoint mBasePos;
	// QPoint mPointPos;
	double mOrientation;				// RAD
	double mLength;
	double mWidthBase;
	double mWidthPoint;
	QColor mColor;

	QPolygonF mPoly;
	// TODO: Déformation
};

#endif