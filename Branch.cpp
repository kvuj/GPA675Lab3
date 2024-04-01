#include "Branch.h"

Branch::Branch(size_t treeDepth
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
	, size_t currentDepth)
	: mTreeDepth{ currentDepth }
	, mChildrenCount{ children() }
	, mParent{ parent }
	, mLinearAttachDistance{ attachDist() }
	, mAngleBetweenParent{ angle() }
	, mAngleFromWind{}
	, mVarLength{ length() }
	, mVarWidthBase{ widthBase() }
	, mVarWidthPoint{ widthPoint() }
	, mLength{ lengthVal * mVarLength }
	, mWidthBase{ widthBaseVal * mVarWidthBase }
	, mWidthPoint{ widthPointVal * mVarWidthPoint }
	, mPoly(4)
	, mColor(139, 69, 19)
	,mOrientation{}
{

	if (mTreeDepth < treeDepth) {
		mChildren.reserve(mChildrenCount);

		for (size_t i{}; i < mChildrenCount; i++) {
			mChildren.emplace_back(new Branch(
				treeDepth
				, children
				, this
				, attachDist
				, angle
				, length
				, widthBase
				, widthPoint
				, mLength / 1.5 // TODO: Non hard codé
				, mWidthBase / 2.0
				, mWidthPoint / 2.0
				, mTreeDepth + 1
			));
		}
	}
}

Branch::~Branch()
{
	//for (auto i : mChildren)
	//	delete i;
}

void Branch::draw(QPainter* painter) const
{
	painter->save();

	if (mParent) [[likely]] {
		painter->translate((mParent->mLength) * mLinearAttachDistance, 0);
		painter->rotate(mAngleBetweenParent + (mAngleFromWind * 0.05));
		}
	else {
		painter->rotate(-90.0); // Base de l'arbre
	}
	painter->setBrush(mColor);
	painter->drawConvexPolygon(mPoly);

	for (auto& i : mChildren)
		i->draw(painter);

	painter->restore();
}

void Branch::updatePolygon(Wind* wind, double absoluteAngle)
{
	// Relatif car QPainter sera mis en mode relatif.
	mPoly.clear();
	mPoly << QPointF(0, -mWidthBase / 2.0);
	mPoly << QPointF(0, mWidthBase / 2.0);
	mPoly << QPointF(mLength, mWidthPoint / 2.0);
	mPoly << QPointF(mLength, -mWidthPoint / 2.0);
	
	// Pour le vent:
	double _x{ sin(absoluteAngle) };
	double _y{ cos(absoluteAngle) };
	double dot = wind->xPower() * _x + wind->yPower() * _y;
	double det = wind->xPower() * _y - wind->yPower() * _x;
	mAngleFromWind = qRadiansToDegrees(atan2(det, dot));

	for (auto& i : mChildren)
		i->updatePolygon(wind, absoluteAngle + mAngleBetweenParent);
}

void Branch::setColor(QColor color)
{
		mColor = color;
		// Appel récursif pour définir la couleur de toutes les branches enfants
    for (auto& child : mChildren) {
        child->setColor(color);
    }
}
