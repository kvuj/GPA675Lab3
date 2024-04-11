#include "Wind.h"

Wind::Wind()
	: mCol(Qt::darkGray)
	, mLastAmplitude{}
	, mLastOrientation{}
	, mTotalTime{}
	, mVecX{}
	, mVecY{}
{
	mPoly << QPoint(7, 8);
	mPoly << QPoint(-7, 8);
	mPoly << QPoint(0, -40);
}

void Wind::computeWind(double elapsedTime)
{
	mTotalTime += elapsedTime;
	
	switch (mWindConfig)
	{
	case WindConfiguration::Swirling:
		mLastAmplitude = sin(mTotalTime) * maxAmplitude;
		mLastOrientation = cos(mTotalTime) * pi;
		mVecX = sin(mLastOrientation);
		mVecY = cos(mLastOrientation);
		break;
	case WindConfiguration::Horizontal:
		mLastAmplitude = maxAmplitude; // ou une autre logique pour l'intensit�
		mLastOrientation = 0; // Vent horizontal vers la droite
		break;
	case WindConfiguration::Oscillating:
		// Vous pouvez utiliser une fonction sinuso�dale limit�e � un certain angle pour osciller
		mLastOrientation = pi / 6 * sin(mTotalTime);
		break;
	}
}

double Wind::windAmplitude() const
{
	return mLastAmplitude;
}

double Wind::windOrientation() const
{
	return mLastOrientation;
}

void Wind::draw(QPainter* paint) const
{
	paint->save();
	paint->setPen(Qt::NoPen);
	paint->setBrush(mCol);

	// Position
	paint->translate(QPoint(100, 100));

	paint->rotate(qRadiansToDegrees(mLastOrientation));
	paint->scale(scale, scale);
	paint->scale(abs(mLastAmplitude) / maxAmplitude
		, abs(mLastAmplitude) / maxAmplitude);
	paint->drawConvexPolygon(mPoly);

	paint->restore();
}

double Wind::yPower()
{
	return mVecY;
}

double Wind::xPower()
{
	return mVecX;
}

void Wind::changeConfig()
{
	if (mWindConfig == WindConfiguration::Swirling)
	{
		mWindConfig = WindConfiguration::Horizontal;
	}
	else if (mWindConfig == WindConfiguration::Horizontal)
	{
		mWindConfig = WindConfiguration::Oscillating;
	}
	else
	{
		mWindConfig = WindConfiguration::Swirling;
	}
}
