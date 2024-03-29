#pragma once
#ifndef FOREST_H
#define FOREST_H

#include <vector>
#include "Tree.h"

class Forest
{
public:
    
    explicit Forest();

    ~Forest() = default;

    Forest(const Forest& other) = delete;
    Forest& operator=(const Forest& other) = delete;

    // Ajouter un arbre à la forêt
    void addTree(std::unique_ptr<Tree> tree);

    void update(double elapsedTime);
    void draw(QPainter* painter) const;
    void clear(); //efface les arbres de la foret 
private:
	std::vector<std::unique_ptr<Tree>> mTrees; //La forêt est constitué d'arbres
};

#endif