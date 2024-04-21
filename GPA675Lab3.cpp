#include "GPA675Lab3.h"

GPA675Lab3::GPA675Lab3(QWidget* parent)
	: QMainWindow(parent)
	, mGen(mRd())
	, mDistrib(1, 6)
	, mParams{}
	, mState{ DrawingType::Help }
	, mFont("Selection", 18)
	, mTimeBeforePause{}
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

	// Actions in game
	keyActions[Qt::Key_H] = [this]() { key_h(); };
	keyActions[Qt::Key_Space] = [this]() { key_space(); };
	keyActions[Qt::Key_Return] = [this]() { key_enter(); };
	keyActions[Qt::Key_Enter] = [this]() { key_enter(); };
	keyActions[Qt::Key_Backspace] = [this]() { key_backSpace(); };
	keyActions[Qt::Key_Tab] = [this]() { key_tabulation(); };
	// Actions pour le nombre d'arbres
	for (int key = Qt::Key_1; key <= Qt::Key_9; ++key)
	{
		keyActions[key] = [this, key]() { setTreeCount(key - Qt::Key_0); };
	}
	keyActions[Qt::Key_0] = [this]() { setTreeCount(10); };
	keyActions[Qt::Key_Minus] = [this]() { randomizeTreeCount(2, 5); };
	keyActions[Qt::Key_Equal] = [this]() { randomizeTreeCount(4, 10); };



	mKeyTreeType =
	{
		{Qt::Key_Z, TreeType::Buisson},
		{Qt::Key_X, TreeType::Sapin},
		{Qt::Key_C, TreeType::Baobab},
		{Qt::Key_V, TreeType::Random},
	};
	// Actions pour la profondeur de l'arbres
	mKeyDepth =
	{
		{Qt::Key_Q, 2},
		{Qt::Key_W, 3},
		{Qt::Key_E, 4},
		{Qt::Key_R, 5},
		{Qt::Key_T, 6},
		{Qt::Key_Y, 7},
		{Qt::Key_U, 8},
		{Qt::Key_I, 9}
	};

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

	auto key = event->key();
	if (keyActions.find(key) != keyActions.end())
	{
		keyActions[key]();
	}
	else if (mKeyDepth.find(key) != mKeyDepth.end())
	{
		setTreeDepth(mKeyDepth[key]);
	}
	else if (mKeyTreeType.find(key) != mKeyTreeType.end())
	{
		setTreeType(mKeyTreeType[key]);
	}

}

void GPA675Lab3::tic()
{
	if (mState == DrawingType::Simulation)
	{
		double elapsedTime{ mElapsedTimer.restart() / 1.0e3 };

		if (!mVirus && mVirusTimer.hasExpired(mTimeVirus))
		{
			mVirus = true;
			// Infecter un arbre aléatoire dans la forêt
			mForest.infectTree();
		}

		if (mVirus)
		{
			if (mVirusTimer.hasExpired(5000))
			{
				mForest.updateInfection();
				mVirusTimer.restart();
			}
		}
		mForest.update(elapsedTime);
		mWind.computeWind(elapsedTime);
		mTimeBeforePause = 0.0;

	}

	repaint();
	mTimer.start();
}

void GPA675Lab3::key_h()
{
	mState = DrawingType::Help;
}

// Mettre en pause ou reprendre la simulation
void GPA675Lab3::key_space()
{
	if (mState != DrawingType::Pause)
	{
		mTimeBeforePause = mElapsedTimer.elapsed() / 1.0e3;
		mState = DrawingType::Pause;
		mTimer.stop();
	}
	else
	{
		mState = DrawingType::Simulation;
		mElapsedTimer.restart();
		mTimer.start();
	}

}

void GPA675Lab3::key_enter()
{
	mState = DrawingType::Simulation;
	mVirusTimer.start();
}
// Reset la simulation avec la configuration actuelle
void GPA675Lab3::key_backSpace()
{
	configurationDone(mParams);
	mState = DrawingType::Simulation;
	mVirus = false;

}

void GPA675Lab3::key_tabulation()
{
	mWind.changeConfig();
}

void GPA675Lab3::setTreeCount(int count)
{
	mParams.treeCount = count;
	configurationDone(mParams);
}

void GPA675Lab3::randomizeTreeCount(int min, int max)
{
	std::uniform_int_distribution<> mDistrib(min, max);
	mParams.treeCount = mDistrib(mGen);

}

void GPA675Lab3::setTreeType(TreeType type)
{
	mParams.treeType = type;
}


void GPA675Lab3::setTreeDepth(int depth)
{
	mParams.treeDepth = depth;
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
	paint.drawText(100, 200, "0-9: Change le nombre d'arbres");
	paint.drawText(100, 225, "-: Randomize le nombre d'arbres (2-5)");
	paint.drawText(100, 250, "=: Randomize le nombre d'arbres (4-10)");
	paint.drawText(100, 275, "Z: Buisson");
	paint.drawText(100, 300, "X: Sapin");
	paint.drawText(100, 325, "C: Baobab");
	paint.drawText(100, 350, "V: Random");
	paint.drawText(100, 375, "Q-I: Change la profondeur de l'arbre");
	paint.drawText(100, 400, "Tab: Change la configuration du vent");
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

	for (size_t i{}; i < params.treeCount; i++)
	{
		mForest.addSpecificTree(mParams.treeType, params.treeDepth,
			childrenLambda,
			attachDistLambda,
			angleLambda,
			lengthLambda,
			widthBaseLambda,
			widthPointLambda,
			500.0, 40.0, 20.0,
			treeLocationX(mGen),
			treeLocationY(mGen), &mWind);
	}

	show();
}

void GPA675Lab3::resizeEvent(QResizeEvent* event)
{
	QMainWindow::resizeEvent(event);
	mForest.updateTreePositions(height(), mPlantingArea);
	update(); // Demander une mise à jour du dessin
}