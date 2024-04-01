#pragma once
#ifndef BAOBAB_H
#define BAOBAB_H

#include "Tree.h"
#include <QColor>

// Le Baobab est un arbre de très grande taille, il est très large
// Il a des betite branches
//Il est très sombres
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
        setColor(QColor(88, 41, 0));


    }

};

#endif // !BAOBAB_H