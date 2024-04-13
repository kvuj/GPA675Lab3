#include "Branch.h"
Branch::Branch(const BranchConfiguration& config,
	Branch* parent,
 size_t currentDepth, std::function<size_t()> children)
	: mTreeDepth{ currentDepth }
	, mParent{ parent }
	, mColor{ config.color }
	, mLength{ config.length }
	, mWidthBase{ config.widthBase }
	, mWidthPoint{ config.widthPoint }
	, mAngleFromWind{ 0.0 }
	, mPoly{ 4 }
	, mLinearAttachDistance{ config.attachDistance }
	, mAngleBetweenParent{ config.angle }
	, mOrientation{}
	, mChildrenCount{ children()}
{

	if (mTreeDepth < currentDepth)
	{
		mChildren.reserve(mChildrenCount);
		for (size_t i{}; i < mChildrenCount; i++)
		{
			mChildren.emplace_back(new Branch(config, this, mTreeDepth + 1,children));
		}
	}
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
