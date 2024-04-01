#pragma once
#ifndef BUISSON_H
#define BUISSON_H

#include "Tree.h"
#include <QColor>

// Le buisson est un arbre de petite taille et de couleur jaune_vert
//il resiste bien au vent
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
        setColor(QColor(173, 255, 47));
        
        
    }
    
};

#endif // !BUISSON_H