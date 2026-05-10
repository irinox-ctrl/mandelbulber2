#include "color_gradient.h"
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	cColorGradient grad;
	QString testGradient = "0 ff0000 5000 00ff00 10000 0000ff";
	grad.SetColorsFromString(testGradient);

	qDebug() << "Number of colors:" << grad.GetNumberOfColors();

	auto colors = grad.GetListOfSortedColors();
	qDebug() << "\nSorted colors:";
	for (int i = 0; i < colors.size(); i++)
	{
		qDebug() << "  [" << i << "] Position:" << colors[i].position
						 << " Color: R=" << colors[i].color.R
						 << " G=" << colors[i].color.G
						 << " B=" << colors[i].color.B;
	}

	qDebug() << "\nInterpolated colors:";
	for (float pos = 0.0f; pos <= 1.0f; pos += 0.25f)
	{
		sRGB color = grad.GetColor(pos, false);
		qDebug() << "  Position" << pos << ": R=" << color.R << "G=" << color.G << "B=" << color.B;
	}

	return 0;
}
