#pragma once
#ifndef WIND_H
#define WIND_H

#include <cmath>

#include <QColor>
#include <QPainter>
#include <QPolygon>
#include <QtMath>

constexpr double maxAmplitudeButTODORemove{ 10.0 };
constexpr double pi{3.14};
constexpr double scale{3.0};

class Wind
{
public:
	Wind();
	~Wind() = default;
	Wind(const Wind& w) = delete;
	Wind(Wind&& w) = delete;
	Wind& operator=(const Wind& w) = delete;
	Wind& operator=(Wind&& w) = delete;

	void computeWind(double elapsedTime);
	double windAmplitude() const;
	double windOrientation() const;
	void draw(QPainter* paint) const;

private:
	QColor mCol;
	QPolygon mPoly;

	double mLastAmplitude;		// m/s
	double mLastOrientation;	// RAD

	double mTotalTime;
};

#endif