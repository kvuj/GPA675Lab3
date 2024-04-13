#pragma once
#ifndef BRANCHCONFIGURATION_H
#define BRANCHCONFIGURATION_H

#include <QColor>
#include <functional>

struct BranchConfiguration
{
    double length;
    double widthBase;
    double widthPoint;
    double attachDistance;
    double angle;
    double orientation;
    QColor color;
};

// Configurations prédéfinies pour différents types d'arbres

//Buisson : petit arbre petite branches 
extern const BranchConfiguration BuissonConfig;
extern const BranchConfiguration TrunkBuissonConfig;

extern const BranchConfiguration SapinConfig;
extern const BranchConfiguration TrunkSapinConfig;

extern const BranchConfiguration BaobabConfig;
extern const BranchConfiguration TrunkBaobabConfig;
#endif // !BRANCHCONFIGURATION_H