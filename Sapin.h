#pragma once
#ifndef SAPIN_H
#define SAPIN_H

#include "Tree.h"
#include <QColor>

// Le Sapin est un arbre de taille moyenne et de couleur vert sapin
//il resiste bien au vent
//ses branches sont plus rappochées que les autres arbres
class Sapin : public Tree
{
public:
    Sapin();
    Sapin(size_t treeDepth,
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
        : Tree(treeDepth,
            children,
            attachDist,
            angle,
            length,
            widthBase,
            widthPoint,
            lengthVal,
            widthBaseVal,
            widthPointVal,
            positionX,
            positionY,
            wind)
    {
        setColor(QColor(9,82, 40));


    }

};

#endif // !SAPIN_H
