#include "Forest.h"

Forest::Forest()
{
	mTreeTypeConfig = TreeType::Buisson;
}

void Forest::addTree(std::unique_ptr<Tree> tree)
{
	mTrees.push_back(std::move(tree));
}

void Forest::addSpecificTree(TreeType type, size_t treeDepth,
	std::function<size_t()> children,
	std::function<double()> attachDist,
	std::function<double()> angle,
	std::function<double()> length,
	std::function<double()> widthBase,
	std::function<double()> widthPoint,
	double lengthVal,
	double widthBaseVal,
	double widthPointVal,
	int positionX,
	int positionY,
	Wind* wind)
{
	std::unique_ptr<Tree> tree;
	if (type == TreeType::Random) {
		std::vector<TreeType> types = { TreeType::Baobab, TreeType::Buisson, TreeType::Sapin };
		std::uniform_int_distribution<> dist(0, types.size() - 1);
		type = types[dist(mGen)];  // Choisissez aléatoirement un type, sauf Random
	}
	switch (type) {
	case TreeType::Buisson:
		tree = std::make_unique<Buisson>(treeDepth,children,
			attachDist,
			angle,length,widthBase,widthPoint,lengthVal,widthBaseVal,widthPointVal,positionX,positionY,wind);
		break;
	case TreeType::Sapin:
		tree = std::make_unique<Sapin>(treeDepth, children,
			attachDist,
			angle, length, widthBase, widthPoint, lengthVal, widthBaseVal, widthPointVal, positionX, positionY, wind);
		break;
	case TreeType::Baobab:
		tree = std::make_unique<Baobab>(treeDepth, children,
			attachDist,
			angle, length, widthBase, widthPoint, lengthVal, widthBaseVal, widthPointVal, positionX, positionY, wind);
		break;
	default:
		break;
	}
	if (tree) {
		mTrees.push_back(std::move(tree));
	}
}

void Forest::randomizeTrees()
{

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

void Forest::infectTree()
{
	if (!mTrees.empty()) {
		mTrees.front()->infect();
	}
}

void Forest::updateInfection()
{
	for (auto& tree : mTrees)
	{
		if (!tree->getTrunk()->isInfectable())
		{
			tree->markForRemoval();
		}
		tree->updateInfection();
		
	}
	mTrees.erase(std::remove_if(mTrees.begin(),mTrees.end(),[](const std::unique_ptr<Tree>& tree)
		{ return tree->shouldRemove(); }),
		mTrees.end());
}

