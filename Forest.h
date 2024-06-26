﻿#pragma once
#ifndef FOREST_H
#define FOREST_H

#include <vector>
#include "Tree.h"
#include <memory>
#include <random>



class Forest
{
public:
	Forest();
	~Forest() = default;

	Forest(const Forest& other) = delete;
	Forest& operator=(const Forest& other) = delete;

	// Ajouter un arbre à la forêt
	void addTree(std::unique_ptr<Tree> tree);

	// Randomise les essences d'arbre dans la forêt
	void randomizeTrees();
	void update(double elapsedTime);
	void draw(QPainter* painter) const;
	void clear(); // Efface les arbres de la foret 
	void updateTreePositions(int windowHeight, float plantingArea);

private:
	std::vector<std::unique_ptr<Tree>> mTrees;
	bool mUseMixedEssence; // Indique si la forêt utilise un mélange d'essences d'arbres

	
};

#endif