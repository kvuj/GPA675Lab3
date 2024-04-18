#pragma once
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <functional>
#include "Forest.h"

using Generator = std::function<double>();

struct Parameters
{
	int treeCount;
	int treeDepth;
	TreeType treeType;
};

enum DrawingType : uint8_t
{
	Simulation = 1,
	Help = 2,
	Pause = 3
};

#endif