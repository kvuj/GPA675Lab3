#include "Configuration.h"

Configuration::Configuration()
	: QWidget(nullptr), mTreeCount{ 2 }, mTreeDepth{ 4 }
{
	resize(400, 600);

	auto* layout = new QVBoxLayout;

	auto* start = new QPushButton("Start", this);
	connect(start, &QPushButton::clicked, this, &Configuration::startClicked);

	auto treeCountLabel = new QLabel("Nombre d'arbres");

	auto* treeCount = new QSpinBox;
	treeCount->setMinimum(1);
	treeCount->setMaximum(7);
	treeCount->setValue(mTreeCount);
	connect(treeCount, &QSpinBox::valueChanged, this, &Configuration::treeCountClicked);

	auto treeDepthLabel = new QLabel("Profondeur des arbres");

	auto* treeDepth = new QSpinBox;
	treeDepth->setMinimum(1);
	treeDepth->setMaximum(7);
	treeDepth->setValue(mTreeDepth);
	connect(treeDepth, &QSpinBox::valueChanged, this, &Configuration::treeDepthClicked);


	layout->addWidget(treeCountLabel);
	layout->addWidget(treeCount);
	layout->addWidget(treeDepthLabel);
	layout->addWidget(treeDepth);
	layout->addWidget(start);
	layout->addStretch();
	this->setLayout(layout);
}

Configuration::~Configuration()
{
}

void Configuration::treeCountClicked(int value)
{
	mTreeCount = value;
}

void Configuration::treeDepthClicked(int value)
{
	mTreeDepth = value;
}

void Configuration::startClicked()
{
	emit done({ .treeCount = mTreeCount, .treeDepth = mTreeDepth });
	hide();
}
