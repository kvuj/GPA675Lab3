#pragma once
#ifndef FOREST_H
#define FOREST_H

#include <vector>
#include "Tree.h"
#include <memory>
#include <random>
#include "Buisson.h"

// Essence d'arbre
enum class TreeType { Bouleau, Buisson, Sapin };
class Forest
{
public:
    
    explicit Forest();

    ~Forest() = default;

    Forest(const Forest& other) = delete;
    Forest& operator=(const Forest& other) = delete;

    // Ajouter un arbre � la for�t
    void addTree(std::unique_ptr<Tree> tree);
    // Ajoute une essence d'arbre sp�cifique � la for�t
    void addSpecificTree(TreeType type);

    // Randomise les essences d'arbre dans la for�t
    void randomizeTrees();
    void update(double elapsedTime);
    void draw(QPainter* painter) const;
    void clear(); //efface les arbres de la foret 
    void updateTreePositions(int windowHeight, float plantingArea);
private:

    std::vector<std::unique_ptr<Tree>> mTrees;
    TreeType mTreeTypeConfig; // Configuration de type d'arbre pour la for�t
    bool mUseMixedEssence; // Indique si la for�t utilise un m�lange d'essences d'arbres

    //pour cr�er un arbre d'une essence sp�cifique
    std::unique_ptr<Tree> createTreeOfType(TreeType type);
    
};

#endif