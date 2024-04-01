#include "GPA675Lab3.h"

GPA675Lab3::GPA675Lab3(QWidget* parent)
	: QMainWindow(parent)
	, mGen(mRd())
	, mDistrib(1, 6)
	, mParams{}
	, mState{ DrawingType::Help }
	, mFont("Selection", 18)
{
	/*
		Pour un raison inconnue, le premier appel de drawText() prend de 200 ms
		à 400 ms sur Windows, ce qui est ridicule (probablement construction de
		cache de glyphe). On commence donc avec le texte d'aide pour que l'utilisateur
		ne soit pas surpris par la performance lorsqu'il change de state.

		- Timothée L-F
	*/

	hide();
	mConf.show();
	mConf.setFocus();
	resize(800, 800);
	setMinimumSize(150, 150);

	QPalette pal = palette();
	pal.setColor(QPalette::Window, QColor(171, 215, 235));
	setAutoFillBackground(true);
	setPalette(pal);

	mKeyboardActions[Qt::Key_H] = &GPA675Lab3::key_h;
	mKeyboardActions[Qt::Key_Space] = &GPA675Lab3::key_space;
	mKeyboardActions[Qt::Key_Enter] = &GPA675Lab3::key_enter;
	mKeyboardActions[Qt::Key_Return] = &GPA675Lab3::key_enter;
	mKeyboardActions[Qt::Key_Backspace] = &GPA675Lab3::key_backSpace;

	mDrawingActions[DrawingType::Simulation] = &GPA675Lab3::drawingSimulation;
	mDrawingActions[DrawingType::Help] = &GPA675Lab3::drawingHelp;

	connect(&mConf, &Configuration::done, this, &GPA675Lab3::configurationDone);

	mTimer.setSingleShot(true);
	connect(&mTimer, &QTimer::timeout, this, &GPA675Lab3::tic);
	mTimer.start();
}

void GPA675Lab3::paintEvent(QPaintEvent* event)
{
	std::invoke(mDrawingActions[mState], this, event);
}

void GPA675Lab3::keyPressEvent(QKeyEvent* event)
{
	if (mKeyboardActions.contains(static_cast<Qt::Key>(event->key())))
		std::invoke(mKeyboardActions[static_cast<Qt::Key>(event->key())], this);
}

void GPA675Lab3::tic()
{
	if (mState == DrawingType::Simulation) {
		double elapsedTime{ mElapsedTimer.restart() / 1.0e3 };

		mForest.update(elapsedTime);
		mWind.computeWind(elapsedTime);

	}

	repaint();
	mTimer.start(16);
}

void GPA675Lab3::key_h()
{
	mState = DrawingType::Help;
}

void GPA675Lab3::key_space()
{
}

void GPA675Lab3::key_enter()
{
	mState = DrawingType::Simulation;
}

void GPA675Lab3::key_backSpace()
{
}

void GPA675Lab3::drawingSimulation(QPaintEvent* event)
{
	QPainter paint(this);
	paint.setRenderHint(QPainter::Antialiasing);
	paint.setPen(Qt::NoPen);

	// Dessiner la zone de plantation
	float plantingZoneHeight = height() * mPlantingArea; // 30% de la hauteur de la fenêtre
	QRect plantingZoneRect(0, height() - plantingZoneHeight, width(), plantingZoneHeight);
	paint.fillRect(plantingZoneRect, QColor(200, 255, 200)); // Couleur verte claire pour la zone de plantation


	mWind.draw(&paint);
	mForest.draw(&paint);
}

void GPA675Lab3::drawingHelp(QPaintEvent* event)
{
	QPainter paint(this);
	paint.setRenderHint(QPainter::Antialiasing);
	paint.setFont(mFont);
	paint.setPen(QPen(Qt::black, 1, Qt::SolidLine));

	paint.drawText(100, 100, "H: Help");
	paint.drawText(100, 125, "Space: Pause/Play");
	paint.drawText(100, 150, "Enter: Simulation");
	paint.drawText(100, 175, "Backspace: Reset la simulation");
}

void GPA675Lab3::configurationDone(Parameters params)
{
	mParams = params;
	float plantingZoneHeight = height() * mPlantingArea; // 30% de la hauteur de la fenêtre
	auto childrenLambda = [&]() -> size_t {
		std::uniform_int_distribution<> _r(2, 6);
		return _r(mGen);
		};
	auto attachDistLambda = [&]() -> double {
		std::uniform_real_distribution<> _r(0.6, 0.8);
		return _r(mGen);
		};
	auto angleLambda = [&]() -> double { // En deg
		std::uniform_int_distribution<> _r(-60, 60);
		return _r(mGen);
		};
	auto lengthLambda = [&]() -> double {
		std::uniform_real_distribution<> _r(0.6, 0.8);
		return _r(mGen);
		};
	auto widthBaseLambda = []() -> double {
		return 1.0;
		};
	auto widthPointLambda = []() -> double {
		return 1.0;
		};

	mForest.clear();

	std::uniform_real_distribution<> treeLocationX(100, width() - 100);
	std::uniform_real_distribution<> treeLocationY(height() - plantingZoneHeight, height());

	for (size_t i{}; i < params.treeCount; i++){
		auto tree = std::make_unique<Buisson>(params.treeDepth,
			childrenLambda,
			attachDistLambda,
			angleLambda,
			lengthLambda,
			widthBaseLambda,
			widthPointLambda,
			500.0, 40.0, 20.0,
			treeLocationX(mGen),
			treeLocationY(mGen), &mWind);
		mForest.addTree(std::move(tree));
	}

	show();
}

void GPA675Lab3::resizeEvent(QResizeEvent* event) {
	QMainWindow::resizeEvent(event);
	mForest.updateTreePositions(height(), mPlantingArea);
	update(); // Demander une mise à jour du dessin
}