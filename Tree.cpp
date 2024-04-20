#include "Tree.h"


Tree::Tree(const TreeConfiguration& config, int positionX, int positionY, Wind* wind, size_t treeDepth, std::function<size_t()> children )
{
	mBasePosition = QPoint(positionX, positionY);
	mWind = wind;
	mTrunk = std::make_unique<Branch>(config ,nullptr,treeDepth,0,children);
}

Tree::~Tree()
{
}

/*Tree::Tree(Tree&& tr) noexcept
{
	*this = std::move(tr);
}*/

/*Tree& Tree::operator=(Tree&& tr) noexcept
{
	if (this != &tr) {
		mTrunk.reset();

		mTrunk = std::move(tr.mTrunk);
		mTotalHeight = tr.mTotalHeight;
		mTotalBranch = tr.mTotalBranch;
		mDensity = tr.mDensity;
		mDeformationResistance = tr.mDeformationResistance;
	}
	return *this;
}*/

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
	
}

void Tree::setDeformationResistance(double deformationResistance)
{
	
}

QPoint Tree::getPosition() const
{
	return mBasePosition;
}

void Tree::setPosition(QPoint position)
{
	mBasePosition = position;
}

void Tree::setLength(double length)
{

}

void Tree::infect()
{
	if (mTrunk)
	{
		mTrunk->infectDeepest();
	}

}

void Tree::updateInfection()
{
	if (mTrunk)
	{
		mTrunk->updateInfection();
	}

}
