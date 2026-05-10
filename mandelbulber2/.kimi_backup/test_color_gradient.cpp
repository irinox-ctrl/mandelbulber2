/**
 * Mandelbulber v2, a 3D fractal generator
 *
 * Unit tests for cColorGradient - Phase 1: Regression Tests
 *
 * Phase 1 adds IsFormatV2() as a private method without integrating it yet.
 * These tests verify that existing functionality still works correctly.
 * Full IsFormatV2() testing will be added in Phase 3 when it's integrated.
 */

#include "color_gradient.h"
#include <QTest>
#include <QDebug>

class TestColorGradient : public QObject
{
	Q_OBJECT

private slots:
	void testBasicGradientCreation()
	{
		cColorGradient grad;
		QCOMPARE(grad.GetNumberOfColors(), 2); // Default: 2 colors at 0.0 and 1.0
	}

	void testAddColor()
	{
		cColorGradient grad;
		sRGB red = {255, 0, 0};
		grad.AddColor(red, 0.5f);
		QCOMPARE(grad.GetNumberOfColors(), 3); // Now 3 colors
	}

	void testV1FormatParsing()
	{
		cColorGradient grad;

		// V1 format: "0 ff0000 5000 00ff00 10000 0000ff"
		// Position 0 (0.0) = red, Position 5000 (0.5) = green, Position 10000 (1.0) = blue
		QString v1Gradient = "0 ff0000 5000 00ff00 10000 0000ff";
		grad.SetColorsFromString(v1Gradient);

		// Should have 3 colors
		QCOMPARE(grad.GetNumberOfColors(), 3);

		// Verify first color is red
		sRGB color0 = grad.GetColorByIndex(0);
		QCOMPARE(color0.R, 255);
		QCOMPARE(color0.G, 0);
		QCOMPARE(color0.B, 0);

		// Verify middle color is green
		sRGB color1 = grad.GetColorByIndex(1);
		QCOMPARE(color1.R, 0);
		QCOMPARE(color1.G, 255);
		QCOMPARE(color1.B, 0);
	}

	void testV1FormatRoundTrip()
	{
		cColorGradient grad;
		QString original = "0 ff0000 5000 00ff00 10000 0000ff";
		grad.SetColorsFromString(original);
		QString serialized = grad.GetColorsAsString();

		// Should preserve the gradient data (exact string match not required,
		// but should have same number of color stops)
		cColorGradient grad2;
		grad2.SetColorsFromString(serialized);
		QCOMPARE(grad2.GetNumberOfColors(), grad.GetNumberOfColors());
	}

	void testColorInterpolation()
	{
		cColorGradient grad;

		// Create red-to-blue gradient
		QString gradient = "0 ff0000 10000 0000ff";
		grad.SetColorsFromString(gradient);
		grad.SortGradient();

		// Get color at 50% - should be purple-ish
		sRGB midColor = grad.GetColor(0.5f, false);

		// Mid color should have both red and blue components
		QVERIFY(midColor.R > 0);
		QVERIFY(midColor.B > 0);
	}
};

QTEST_MAIN(TestColorGradient)
#include "test_color_gradient.moc"
