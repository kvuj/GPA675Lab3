#pragma once
#ifndef GPA675LAB3_H
#define GPA675LAB3_H

#include <functional>
#include <random>
#include <unordered_map>
#include <vector>

#include <QElapsedTimer>
#include <QMainWindow>
#include <QPalette>
#include <QPaintEvent>
#include <QtMath>
#include <QTimer>

#include "Configuration.h"
#include "Definitions.h"
#include "Tree.h"
#include "Forest.h"
#include "Wind.h"


class GPA675Lab3 : public QMainWindow
{
	Q_OBJECT

public:
	using KeyboardAction = void(GPA675Lab3::*)();
	using DrawingAction = void(GPA675Lab3::*)(QPaintEvent*);

	GPA675Lab3(QWidget* parent = nullptr);
	~GPA675Lab3() = default;

protected:
	void paintEvent(QPaintEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;

public slots:
	void configurationDone(Parameters params);
	void tic();

private:
	Configuration mConf;
	Wind mWind;
	Parameters mParams;
	DrawingType mState;
	Forest mForest;

	std::unordered_map<Qt::Key, KeyboardAction> mKeyboardActions;
	std::unordered_map<DrawingType, DrawingAction> mDrawingActions;

	QTimer mTimer;
	QElapsedTimer mElapsedTimer;
	QFont mFont;

	std::random_device mRd;
	std::mt19937 mGen;
	std::uniform_int_distribution<> mDistrib;

	void key_h();
	void key_space();
	void key_enter();
	void key_backSpace();

	void drawingSimulation(QPaintEvent* event);
	void drawingHelp(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	double mPlantingArea =0.3; //30% de la fenetre est la zone d eplantation
};

#endif //GPA675LAB3_H