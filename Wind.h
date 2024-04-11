#pragma once
#ifndef WIND_H
#define WIND_H

#include <cmath>

#include <QColor>
#include <QPainter>
#include <QPolygon>
#include <QtMath>

constexpr double maxAmplitude{ 10.0 };
constexpr double pi{3.14};
constexpr double scale{3.0};

enum class WindConfiguration : uint8_t
{
	 Swirling, Horizontal, Oscillating
};

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

	double yPower();
	double xPower();

	void changeConfig();
private:
	QColor mCol;
	QPolygon mPoly;

	double mLastAmplitude;		// m/s
	double mLastOrientation;	// RAD

	double mTotalTime;

	double mVecX;
	double mVecY;
	WindConfiguration mWindConfig = WindConfiguration::Swirling;
};

#endif