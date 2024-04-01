#include "Baobab.h"

Baobab::Baobab()
{
}

Baobab::Baobab(size_t treeDepth,
	std::function<size_t()> children,
	std::function<double()> attachDist,
	std::function<double()> angle,
	std::function<double()> length,
	std::function<double()> widthBase,
	std::function<double()> widthPoint,
	double lengthVal, double widthBaseVal,
	double widthPointVal, int positionX,
	int positionY,
	Wind* wind)
    : Tree( // Appel du constructeur de base avec la liste d'initialisation
        treeDepth,
        children,
        [attachDist]() -> double { return DEFAULT_BRANCH_ATTACH_DIST * attachDist(); },
        [angle]() -> double { return DEFAULT_BRANCH_ANGLE * angle(); },
        [length]() -> double { return DEFAULT_BRANCH_LENGTH * length(); },
        [widthBase]() -> double { return DEFAULT_BRANCH_WIDTH_BASE * widthBase(); },
        [widthPoint]() -> double { return DEFAULT_BRANCH_WIDTH_POINT * widthPoint(); },
        lengthVal,
        widthBaseVal,
        widthPointVal,
        positionX,
        positionY,
        wind)
{
    setColor(QColor(88, 41, 0));


}

