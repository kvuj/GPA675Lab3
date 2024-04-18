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
	, mOrientation{}
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

void Branch::isKilled()
{
	isAlive = false;
}

bool Branch::isInfectable() const
{
	//on peut infecter seulement les branches non infected
	return !isInfected && !mChildren.empty();
}

void Branch::infect()
{
	if (isInfectable()) {
		isInfected = true;
		mColor = Qt::gray;
	}
}

void Branch::infectDeepest()
{
	if (mChildren.empty())
	{
		this->infect();
	}
	else
	{
		// Autrement, trouvez l'enfant le plus profond et commencez l'infection là-bas
		Branch* deepestBranch = nullptr;
		int maxDepth = 0;
		for (auto& child : mChildren)
		{
			int childDepth = child->getMaxDepth();
			if (childDepth > maxDepth)
			{
				maxDepth = childDepth-1;
				deepestBranch = child.get();
			}
		}
		if (deepestBranch) {
			deepestBranch->infectDeepest();
		}
	}
}

void Branch::updateInfection(double time)
{
	if (isInfected)
	{
		mInfectionProgress += time; // Progression basée sur le temps réel
		// Quand la progression atteint un certain seuil, vous pouvez propager l'infection
		if (mInfectionProgress >= 1.0)
		{
			// Propager l'infection aux branches enfants
			for (auto& child : mChildren)
			{
				if (!child->isInfected) 
				{
					child->infect();
				}
			}
			// Réinitialiser le progrès ou le laisser croître pour propager à nouveau
			// mInfectionProgress = 0.0;
		}
		
		//on applique du gris
		int greyValue = static_cast<int>(255 * (1 - mInfectionProgress));
		mColor.setRgb(greyValue, greyValue, greyValue);
	}
	for (auto& child : mChildren)
	{
		child->updateInfection(time);
	}

}

int Branch::getMaxDepth() const
{
	if (mChildren.empty())
	{
		return mChildrenCount;
	}
	else
	{
		int maxDepth = 0;
		for (const auto& child : mChildren)
		{
			int childDepth = child->getMaxDepth();
			if (childDepth > maxDepth)
			{
				maxDepth = childDepth;
			}
		}
		return maxDepth;
	}
}
