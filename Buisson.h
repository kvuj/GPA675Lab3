#pragma once
#ifndef BUISSON_H
#define BUISSON_H

#include "Tree.h"
#include <QColor>

// Le buisson est un arbre de petite taille et de couleur jaune_vert
//il resiste bien au vent
//les branches sont plus courtes et plus éloignées les unes des autres
class Buisson : public Tree
{
public:
    Buisson();
    Buisson(size_t treeDepth,
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
    ~Buisson() = default;
    static constexpr double DEFAULT_BRANCH_LENGTH = 0.5;
    static constexpr double DEFAULT_BRANCH_WIDTH_BASE = 0.1;
    static constexpr double DEFAULT_BRANCH_WIDTH_POINT = 0.1;
    static constexpr double DEFAULT_BRANCH_ANGLE = 0.5;
    static constexpr double DEFAULT_BRANCH_ATTACH_DIST = 0.5;
private:
    
};

#endif // !BUISSON_H