#include "Tree.h"

Tree::Tree()
{
}

Tree::Tree(size_t treeDepth
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
	, Wind* wind)
	: mTrunk{ new Branch(treeDepth
	, children
	, nullptr
	, attachDist
	, angle
	, length
	, widthBase
	, widthPoint
	, lengthVal / 2.0
	, widthBaseVal / 2.0
	, widthPointVal / 2.0
	, 0) }
	, mBasePosition(positionX, positionY)
	, mWind{ wind }
{
}

Tree::~Tree()
{
	//delete mTrunk;
}

Tree::Tree(Tree&& tr) noexcept
{
	*this = std::move(tr);
}

Tree& Tree::operator=(Tree&& tr) noexcept
{
	if (this != &tr) {
		//delete mTrunk;

		mTrunk = std::move(tr.mTrunk);
		mTotalHeight = tr.mTotalHeight;
		mTotalBranch = tr.mTotalBranch;
		mDensity = tr.mDensity;
		mDeformationResistance = tr.mDeformationResistance;
	}
	return *this;
}

void Tree::tic()
{
	mTrunk->updatePolygon(mWind, 0);
}

void Tree::draw(QPainter* painter) const
{
	painter->save();
	painter->translate(mBasePosition);
	mTrunk->draw(painter);
	painter->restore();
}

void Tree::setColor(QColor color)
{
	mTrunk->setColor(color);
}

void Tree::setDensity(double density)
{
	mDensity = density;
}

void Tree::setDeformationResistance(double deformationResistance)
{
	mDeformationResistance = deformationResistance;
}

QPoint Tree::getPosition() const
{
	return mBasePosition;
}

void Tree::setPosition(QPoint position)
{
		mBasePosition = position;
}
