#include "Branch.h"
Branch::Branch(const TreeConfiguration& treeConfig,
	Branch* parent,
 size_t treeDepth, size_t currentDepth, std::function<size_t()> children)
	: mTreeDepth{ currentDepth }
	, mParent{ parent }
	, mAngleFromWind{ 0.0 }
	, mPoly{ 4 }
	, mOrientation{}
	, mChildrenCount{ children()}
{

	if (parent == nullptr)
	{ 
		mLength = treeConfig.trunkConfig.length;
		mWidthBase = treeConfig.trunkConfig.widthBase;
		mWidthPoint = treeConfig.trunkConfig.widthPoint;
		mLinearAttachDistance = treeConfig.trunkConfig.attachDistance;
		mAngleBetweenParent = treeConfig.trunkConfig.angle;
		mColor = treeConfig.trunkConfig.color;
	}
	else
	{
		mLength = treeConfig.branchConfig.length;
		mWidthBase = treeConfig.branchConfig.widthBase;
		mWidthPoint = treeConfig.branchConfig.widthPoint;
		mLinearAttachDistance = treeConfig.branchConfig.attachDistance;
		mAngleBetweenParent = treeConfig.branchConfig.angle;
		mColor = treeConfig.branchConfig.color;
	}

	if (mTreeDepth < treeDepth )
	{
		mChildrenCount = children();
		mChildren.reserve(mChildrenCount);
		for (size_t i = 0; i < mChildrenCount; ++i) {
			mChildren.emplace_back(new Branch(treeConfig,this,treeDepth,mTreeDepth + 1,children));
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


const BranchConfiguration& Branch::getConfigForChild() const {
	// Supposons que nous avons un membre TreeConfiguration dans Branch qui est défini quelque part lors de la construction.
	// Nous retournerons branchConfig pour tous les enfants du tronc.
	return mTreeConfig.branchConfig;
}
