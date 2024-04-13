#pragma once
#ifndef TREECONFIGURATION_H
#define TREECONFIGURATION_H

#include "BranchConfiguration.h"

struct TreeConfiguration
{
    BranchConfiguration trunkConfig;
    BranchConfiguration branchConfig;
};


extern const BranchConfiguration TrunkBuissonConfig;
extern const BranchConfiguration BuissonConfig;
extern const BranchConfiguration TrunkSapinConfig;
extern const BranchConfiguration SapinConfig;
extern const BranchConfiguration TrunkBaobabConfig;
extern const BranchConfiguration BaobabConfig;

extern const TreeConfiguration Buisson;
extern const TreeConfiguration Sapin;
extern const TreeConfiguration Baobab;

#endif // !TREECONFIGURATION_H

