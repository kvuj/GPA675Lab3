#pragma once
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

#include "Definitions.h"

class Configuration : public QWidget
{
	Q_OBJECT

public:
	Configuration();
	~Configuration();

signals:
	void done(Parameters params);

public slots:
	void startClicked();
	void treeCountClicked(int value);
	void treeDepthClicked(int value);

private:
	int mTreeCount;
	int mTreeDepth;
};

#endif