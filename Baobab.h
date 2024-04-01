#pragma once
#ifndef BAOBAB_H
#define BAOBAB_H

#include "Tree.h"
#include <QColor>

// Le Baobab est un arbre de tr�s grande taille, il est tr�s large
// Il a des betite branches
//Il est tr�s sombres
class Baobab : public Tree
{
public:
    Baobab();
    Baobab(size_t treeDepth,
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
        Wind* wind);
        

    static constexpr double DEFAULT_BRANCH_LENGTH = 1.0;
    static constexpr double DEFAULT_BRANCH_WIDTH_BASE = 1.0;
    static constexpr double DEFAULT_BRANCH_WIDTH_POINT = 1.0;
    static constexpr double DEFAULT_BRANCH_ANGLE = 1.0;
    static constexpr double DEFAULT_BRANCH_ATTACH_DIST = 0.7;
};

#endif // !BAOBAB_H