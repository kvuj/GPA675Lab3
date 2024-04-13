#pragma once
#ifndef BRANCH_H
#define BRANCH_H

#include "BranchConfiguration.h"

#include <functional>
#include <vector>

#include <QColor>
#include <QtMath>
#include <QPainter>
#include <QPoint>
#include <QPolygon>
#include <QTransform>

#include "Wind.h"

class Branch
{
public:
	Branch(const BranchConfiguration& config,
		Branch* parent,
		size_t currentDepth,
		std::function<size_t()> children);
	~Branch() = default;
	Branch(const Branch& br) = delete;
	Branch(Branch&& br) = default;
	Branch& operator=(const Branch& br) = delete;
	Branch& operator=(Branch&& br) = default;

	void draw(QPainter* painter) const;
	void updatePolygon(Wind* wind, double absoluteAngle);
	void setColor(QColor color);

private:
	size_t mTreeDepth;
	size_t mChildrenCount;
	Branch* mParent;
	std::vector<std::unique_ptr<Branch>> mChildren;
	double mLinearAttachDistance;		// % [0, 1]
	double mAngleBetweenParent;			// RAD
	double mAngleFromWind;				// RAD
	//double mVarLength;					// % [0, 1]
	//double mVarWidthBase;				// % [0, 1]
	//double mVarWidthPoint;	// % [0, 1]
	
	double mOrientation;				// RAD
	double mLength;
	double mWidthBase;
	double mWidthPoint;
	QColor mColor;
	QPolygonF mPoly;
};

#endif