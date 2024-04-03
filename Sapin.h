﻿#pragma once
#ifndef SAPIN_H
#define SAPIN_H

#include <QColor>

#include "Tree.h"

// Le Sapin est un arbre de taille moyenne et de couleur vert sapin
// Il résiste bien au vent
// Ses branches sont plus rapprochées que les autres arbres
class Sapin : public Tree
{
public:
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
		Wind* wind);

	static constexpr double DEFAULT_BRANCH_LENGTH = 0.7;
	static constexpr double DEFAULT_BRANCH_WIDTH_BASE = 1.0;
	static constexpr double DEFAULT_BRANCH_WIDTH_POINT = 1.0;
	static constexpr double DEFAULT_BRANCH_ANGLE = 1.0;
	static constexpr double DEFAULT_BRANCH_ATTACH_DIST = 0.7;

};

#endif // !SAPIN_H
