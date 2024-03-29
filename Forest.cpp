#include "Forest.h"

Forest::Forest()
{
}



void Forest::addTree(std::unique_ptr<Tree> tree)
{
	mTrees.push_back(std::move(tree));
}

void Forest::update(double elapsedTime)
{
	for (auto& tree : mTrees)
	{
		tree->tic();
	}

}

void Forest::draw(QPainter* painter) const
{
	for (auto& tree : mTrees)
	{
		tree->draw(painter);
	}
}

void Forest::clear()
{
		mTrees.clear();
}

