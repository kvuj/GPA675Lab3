#include "Wind.h"

Wind::Wind()
	: mCol(Qt::darkGray)
	, mLastAmplitude{}
	, mLastOrientation{}
	, mTotalTime{}
{
	mPoly << QPoint(7, 8);
	mPoly << QPoint(-7, 8);
	mPoly << QPoint(0, -40);
}

void Wind::computeWind(double elapsedTime)
{
	mTotalTime += elapsedTime;
	mLastAmplitude = sin(mTotalTime) * maxAmplitudeButTODORemove;
	mLastOrientation = cos(mTotalTime);
}

double Wind::windAmplitude(double elapsedTime) const
{
	return mLastAmplitude;
}

double Wind::windOrientation(double elapsedTime) const
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

	paint->rotate(qRadiansToDegrees(mLastOrientation) * pi);
	paint->scale(scale, scale);
	paint->scale(abs(mLastAmplitude) / maxAmplitudeButTODORemove
		, abs(mLastAmplitude) / maxAmplitudeButTODORemove);
	paint->drawConvexPolygon(mPoly);

	paint->restore();
}
