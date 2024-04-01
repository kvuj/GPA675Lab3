#include "Forest.h"


Forest::Forest()
{
	mUseMixedEssence = false;
	mTreeTypeConfig = TreeType::Buisson;
}


void Forest::addTree(std::unique_ptr<Tree> tree)
{
	mTrees.push_back(std::move(tree));
}

void Forest::addSpecificTree(TreeType type)
{
	auto tree = createTreeOfType(type);
	addTree(std::move(tree));
}


void Forest::randomizeTrees()
{
	clear(); // Effacer les arbres existants avant de randomiser

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(1,2); // Ajustez pour le nombre de types d'arbres

	for (size_t i = 0; i < mTrees.size(); ++i) {
		TreeType type = mUseMixedEssence ? static_cast<TreeType>(distrib(gen)) : mTreeTypeConfig;
		addSpecificTree(type);
	}
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

std::unique_ptr<Tree> Forest::createTreeOfType(TreeType type)
{
	switch (type) {
	case TreeType::Bouleau:
		return nullptr;
	case TreeType::Buisson:
		return std::make_unique<Buisson>();
	default:
		return nullptr;
	}
}

void Forest::updateTreePositions(int windowHeight, float plantingArea) {
	float plantingZoneHeight = windowHeight * plantingArea;
	float minY = windowHeight - plantingZoneHeight;

	for (auto& tree : mTrees) {
		// Supposons que Tree a une m�thode pour obtenir et d�finir sa position Y
		QPoint pos = tree->getPosition();
		if (pos.y() < minY) {
			pos.setY(minY + ((plantingZoneHeight - 100) * (rand() / (RAND_MAX + 1.0)))); // Exemple simplifi�
			tree->setPosition(pos);
		}
	}
}

