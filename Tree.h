#pragma once
#ifndef TREE_H
#define TREE_H
#include "TreeConfiguration.h"

#include <functional>

#include <QPainter>

#include "Branch.h"
#include "Wind.h"


class Tree
{
public:
	Tree(const TreeConfiguration& config, int positionX, int positionY, Wind* wind, size_t currentDepth, std::function<size_t()> children);
	virtual ~Tree();
	Tree(const Tree& tr) = delete;
	Tree(Tree&& tr) noexcept;
	Tree& operator=(const Tree& tr) = delete;
	Tree& operator=(Tree&& tr) noexcept;

	virtual void tic();
	virtual void draw(QPainter* painter) const;
	virtual void setColor(QColor color);
	virtual void setDensity(double density);
	virtual void setDeformationResistance(double deformationResistance);
	virtual QPoint getPosition() const;
	virtual void setPosition(QPoint position);
	virtual void setLength(double length);

	void infect(); // Méthode pour infecter l'arbre
	void updateInfection(double deltaTime);
private:
	std::unique_ptr<Branch> mTrunk;
	QPoint mBasePosition;
	Wind* mWind;
};

#endif