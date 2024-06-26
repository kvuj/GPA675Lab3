﻿#include "Forest.h"

Forest::Forest()
{
	mUseMixedEssence = false;
}

void Forest::addTree(std::unique_ptr<Tree> tree)
{
	mTrees.push_back(std::move(tree));
}


void Forest::randomizeTrees()
{
	clear(); // Effacer les arbres existants avant de randomiser

	
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


void Forest::updateTreePositions(int windowHeight, float plantingArea)
{
	float plantingZoneHeight = windowHeight * plantingArea;
	float minY = windowHeight - plantingZoneHeight;

	for (auto& tree : mTrees) {
		// Supposons que Tree a une méthode pour obtenir et définir sa position Y
		QPoint pos = tree->getPosition();
		if (pos.y() < minY) {
			pos.setY(minY + ((plantingZoneHeight - 100) * (rand() / (RAND_MAX + 1.0)))); // Exemple simplifié
			tree->setPosition(pos);
		}
	}
}

