#pragma once
#ifndef FOREST_H
#define FOREST_H

#include <vector>
#include "Tree.h"
#include <memory>
#include <random>
#include "Buisson.h"
#include "Sapin.h"
#include "Baobab.h"

// Essence d'arbre
enum class TreeType : uint8_t
{
	Baobab, Buisson, Sapin
};

class Forest
{
public:
	Forest();
	~Forest() = default;

	Forest(const Forest& other) = delete;
	Forest& operator=(const Forest& other) = delete;

	// Ajouter un arbre à la forêt
	void addTree(std::unique_ptr<Tree> tree);
	// Ajoute une essence d'arbre spécifique à la forêt
	void addSpecificTree(TreeType type, size_t treeDepth,
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

	// Randomise les essences d'arbre dans la forêt
	void randomizeTrees();
	void update(double elapsedTime);
	void draw(QPainter* painter) const;
	void clear(); // Efface les arbres de la foret 
	void updateTreePositions(int windowHeight, float plantingArea);

	void infectTree();
	void updateInfection();


private:
	std::vector<std::unique_ptr<Tree>> mTrees;
	TreeType mTreeTypeConfig; // Configuration de type d'arbre pour la forêt

};

#endif