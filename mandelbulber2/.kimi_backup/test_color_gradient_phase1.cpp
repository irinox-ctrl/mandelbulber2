/**
 * Mandelbulber v2, a 3D fractal generator
 *
 * Phase 1+2 Regression Test for cColorGradient
 *
 * Phase 1: Added IsFormatV2() private method
 * Phase 2: Added opacity and midpoint fields to sColor struct
 *
 * Compile with:
 *   qmake test_phase1.pro && make
 */

#include "color_gradient.h"
#include <QCoreApplication>
#include <QDebug>
#include <iostream>

bool testBasicGradientCreation()
{
	cColorGradient grad;
	if (grad.GetNumberOfColors() != 2)
	{
		qCritical() << "FAIL: Basic gradient should have 2 colors, got" << grad.GetNumberOfColors();
		return false;
	}
	qDebug() << "PASS: Basic gradient creation";
	return true;
}

bool testAddColor()
{
	cColorGradient grad;
	sRGB red = {255, 0, 0};
	grad.AddColor(red, 0.5f);
	if (grad.GetNumberOfColors() != 3)
	{
		qCritical() << "FAIL: After adding color, should have 3 colors, got"
								<< grad.GetNumberOfColors();
		return false;
	}
	qDebug() << "PASS: Add color";
	return true;
}

bool testV1FormatParsing()
{
	cColorGradient grad;

	// V1 format: "0 ff0000 5000 00ff00 10000 0000ff"
	// This creates: red@0.0, green@0.5, red@1.0 (auto-added), blue@1.0
	// So 4 colors total due to the auto-added cyclic color
	QString v1Gradient = "0 ff0000 5000 00ff00 10000 0000ff";
	grad.SetColorsFromString(v1Gradient);

	// Should have 4 colors (including auto-added cyclic color)
	if (grad.GetNumberOfColors() != 4)
	{
		qCritical() << "FAIL: V1 format parsing should produce 4 colors (with cyclic), got"
								<< grad.GetNumberOfColors();
		return false;
	}

	grad.SortGradient();
	auto colors = grad.GetListOfSortedColors();

	// Verify first color is red at 0.0
	if (colors[0].position != 0.0f || colors[0].color.R != 255 || colors[0].color.G != 0
			|| colors[0].color.B != 0)
	{
		qCritical() << "FAIL: First sorted color should be red at 0.0";
		return false;
	}

	// Verify second color is green at 0.5
	if (colors[1].position != 0.5f || colors[1].color.R != 0 || colors[1].color.G != 255
			|| colors[1].color.B != 0)
	{
		qCritical() << "FAIL: Second sorted color should be green at 0.5";
		return false;
	}

	qDebug() << "PASS: V1 format parsing";
	return true;
}

bool testColorInterpolation()
{
	cColorGradient grad;

	// Create a simple 2-color gradient from black to white
	grad.DeleteAll();
	sRGB black = {0, 0, 0};
	sRGB white = {255, 255, 255};
	grad.AddColor(black, 0.0f);
	grad.AddColor(white, 1.0f);
	grad.SortGradient();

	// Get color at 50% - should be mid-gray
	sRGB midColor = grad.GetColor(0.5f, false);

	// Mid color should be around 127-128 for all components
	if (midColor.R < 120 || midColor.R > 135 || midColor.G < 120 || midColor.G > 135
			|| midColor.B < 120 || midColor.B > 135)
	{
		qCritical() << "FAIL: Interpolated color at 0.5 should be mid-gray (~127), got" << midColor.R
								<< "," << midColor.G << "," << midColor.B;
		return false;
	}

	qDebug() << "PASS: Color interpolation";
	return true;
}

bool testV1FormatRoundTrip()
{
	cColorGradient grad;
	QString original = "0 ff0000 5000 00ff00 10000 0000ff";
	grad.SetColorsFromString(original);
	int originalCount = grad.GetNumberOfColors();
	QString serialized = grad.GetColorsAsString();

	// Parse the serialized string back
	cColorGradient grad2;
	grad2.SetColorsFromString(serialized);

	if (grad2.GetNumberOfColors() != originalCount)
	{
		qCritical() << "FAIL: Round-trip should preserve number of colors, got"
								<< grad2.GetNumberOfColors() << "expected" << originalCount;
		return false;
	}

	qDebug() << "PASS: V1 format round-trip";
	return true;
}

bool testModifyColor()
{
	cColorGradient grad;
	sRGB red = {255, 0, 0};
	grad.AddColor(red, 0.5f);

	// Modify the color
	sRGB blue = {0, 0, 255};
	grad.ModifyColor(1, blue); // Index 1 is the middle color we added

	sRGB retrieved = grad.GetColorByIndex(1);
	if (retrieved.R != 0 || retrieved.G != 0 || retrieved.B != 255)
	{
		qCritical() << "FAIL: Modified color should be blue, got" << retrieved.R << ","
								<< retrieved.G << "," << retrieved.B;
		return false;
	}

	qDebug() << "PASS: Modify color";
	return true;
}

// NEW Phase 2 tests
bool testDefaultOpacityAndMidpoint()
{
	cColorGradient grad;

	// Default colors should have opacity=255 and midpoint=50
	int opacity0 = grad.GetOpacityByIndex(0);
	int midpoint0 = grad.GetMidpointByIndex(0);

	if (opacity0 != 255)
	{
		qCritical() << "FAIL: Default opacity should be 255, got" << opacity0;
		return false;
	}

	if (midpoint0 != 50)
	{
		qCritical() << "FAIL: Default midpoint should be 50, got" << midpoint0;
		return false;
	}

	qDebug() << "PASS: Default opacity and midpoint";
	return true;
}

bool testModifyOpacity()
{
	cColorGradient grad;
	sRGB red = {255, 0, 0};
	grad.AddColor(red, 0.5f);

	// Modify opacity
	grad.ModifyOpacity(1, 128);

	int opacity = grad.GetOpacityByIndex(1);
	if (opacity != 128)
	{
		qCritical() << "FAIL: Modified opacity should be 128, got" << opacity;
		return false;
	}

	qDebug() << "PASS: Modify opacity";
	return true;
}

bool testModifyMidpoint()
{
	cColorGradient grad;
	sRGB red = {255, 0, 0};
	grad.AddColor(red, 0.5f);

	// Modify midpoint
	grad.ModifyMidpoint(1, 75);

	int midpoint = grad.GetMidpointByIndex(1);
	if (midpoint != 75)
	{
		qCritical() << "FAIL: Modified midpoint should be 75, got" << midpoint;
		return false;
	}

	qDebug() << "PASS: Modify midpoint";
	return true;
}

bool testOpacityBoundsClamping()
{
	cColorGradient grad;
	sRGB red = {255, 0, 0};
	grad.AddColor(red, 0.5f);

	// Try to set opacity out of bounds (should clamp to 0-255)
	grad.ModifyOpacity(1, 300); // Should clamp to 255
	int opacity1 = grad.GetOpacityByIndex(1);
	if (opacity1 != 255)
	{
		qCritical() << "FAIL: Opacity should clamp to 255, got" << opacity1;
		return false;
	}

	grad.ModifyOpacity(1, -10); // Should clamp to 0
	int opacity2 = grad.GetOpacityByIndex(1);
	if (opacity2 != 0)
	{
		qCritical() << "FAIL: Opacity should clamp to 0, got" << opacity2;
		return false;
	}

	qDebug() << "PASS: Opacity bounds clamping";
	return true;
}

bool testMidpointBoundsClamping()
{
	cColorGradient grad;
	sRGB red = {255, 0, 0};
	grad.AddColor(red, 0.5f);

	// Try to set midpoint out of bounds (should clamp to 0-100)
	grad.ModifyMidpoint(1, 150); // Should clamp to 100
	int midpoint1 = grad.GetMidpointByIndex(1);
	if (midpoint1 != 100)
	{
		qCritical() << "FAIL: Midpoint should clamp to 100, got" << midpoint1;
		return false;
	}

	grad.ModifyMidpoint(1, -10); // Should clamp to 0
	int midpoint2 = grad.GetMidpointByIndex(1);
	if (midpoint2 != 0)
	{
		qCritical() << "FAIL: Midpoint should clamp to 0, got" << midpoint2;
		return false;
	}

	qDebug() << "PASS: Midpoint bounds clamping";
	return true;
}

// NEW Phase 3 tests
bool testV2FormatParsing()
{
	cColorGradient grad;

	// V2 format: "0 ff0000 255 50 5000 00ff00 128 75 10000 0000ff 200 25"
	// red@0.0 (opacity=255, midpoint=50)
	// green@0.5 (opacity=128, midpoint=75)
	// blue@1.0 (opacity=200, midpoint=25)
	QString v2Gradient = "0 ff0000 255 50 5000 00ff00 128 75 10000 0000ff 200 25";
	grad.SetColorsFromString(v2Gradient);

	// Should have 4 colors (including auto-added cyclic color)
	if (grad.GetNumberOfColors() != 4)
	{
		qCritical() << "FAIL: V2 format parsing should produce 4 colors (with cyclic), got"
								<< grad.GetNumberOfColors();
		return false;
	}

	grad.SortGradient();
	auto colors = grad.GetListOfSortedColors();

	// Verify first color: red at 0.0 with opacity=255, midpoint=50
	if (colors[0].position != 0.0f || colors[0].color.R != 255 || colors[0].color.G != 0
			|| colors[0].color.B != 0 || colors[0].opacity != 255 || colors[0].midpoint != 50)
	{
		qCritical() << "FAIL: First V2 color should be red@0.0 with opacity=255, midpoint=50";
		return false;
	}

	// Verify second color: green at 0.5 with opacity=128, midpoint=75
	if (colors[1].position != 0.5f || colors[1].color.R != 0 || colors[1].color.G != 255
			|| colors[1].color.B != 0 || colors[1].opacity != 128 || colors[1].midpoint != 75)
	{
		qCritical() << "FAIL: Second V2 color should be green@0.5 with opacity=128, midpoint=75";
		return false;
	}

	qDebug() << "PASS: V2 format parsing";
	return true;
}

bool testV2FormatRoundTrip()
{
	cColorGradient grad;

	// Create gradient with custom opacity/midpoint
	grad.DeleteAll();
	sRGB red = {255, 0, 0};
	sRGB green = {0, 255, 0};
	sRGB blue = {0, 0, 255};

	int idx0 = grad.AddColor(red, 0.0f);
	grad.ModifyOpacity(idx0 - 1, 255);
	grad.ModifyMidpoint(idx0 - 1, 50);

	int idx1 = grad.AddColor(green, 0.5f);
	grad.ModifyOpacity(idx1 - 1, 128);
	grad.ModifyMidpoint(idx1 - 1, 75);

	int idx2 = grad.AddColor(blue, 1.0f);
	grad.ModifyOpacity(idx2 - 1, 200);
	grad.ModifyMidpoint(idx2 - 1, 25);

	// Serialize to V2 format
	QString serialized = grad.GetColorsAsString();

	// Parse back
	cColorGradient grad2;
	grad2.SetColorsFromString(serialized);

	if (grad2.GetNumberOfColors() != grad.GetNumberOfColors())
	{
		qCritical() << "FAIL: V2 round-trip should preserve number of colors";
		return false;
	}

	// Verify opacity and midpoint are preserved using sorted colors
	grad2.SortGradient();
	auto sortedColors = grad2.GetListOfSortedColors();

	// First sorted color should be red@0.0 with opacity=255, midpoint=50
	if (sortedColors[0].opacity != 255 || sortedColors[0].midpoint != 50)
	{
		qCritical() << "FAIL: V2 round-trip should preserve first color opacity/midpoint, got"
								<< sortedColors[0].opacity << sortedColors[0].midpoint;
		return false;
	}

	// Second sorted color should be green@0.5 with opacity=128, midpoint=75
	if (sortedColors[1].opacity != 128 || sortedColors[1].midpoint != 75)
	{
		qCritical() << "FAIL: V2 round-trip should preserve second color opacity/midpoint, got"
								<< sortedColors[1].opacity << sortedColors[1].midpoint;
		return false;
	}

	qDebug() << "PASS: V2 format round-trip";
	return true;
}

bool testV1BackwardCompatibility()
{
	cColorGradient grad;

	// V1 format should still work
	QString v1Gradient = "0 ff0000 5000 00ff00 10000 0000ff";
	grad.SetColorsFromString(v1Gradient);

	// Should parse successfully
	if (grad.GetNumberOfColors() != 4)
	{
		qCritical() << "FAIL: V1 format should still work, got" << grad.GetNumberOfColors()
								<< "colors";
		return false;
	}

	// V1 format should use default opacity=255 and midpoint=50
	if (grad.GetOpacityByIndex(0) != 255 || grad.GetMidpointByIndex(0) != 50)
	{
		qCritical() << "FAIL: V1 format should use default opacity=255, midpoint=50";
		return false;
	}

	qDebug() << "PASS: V1 backward compatibility";
	return true;
}

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	std::cout << "\n=== Phase 1+2+3 Regression Tests for cColorGradient ===" << std::endl;
	std::cout << "Phase 1: Testing IsFormatV2() backward compatibility" << std::endl;
	std::cout << "Phase 2: Testing opacity and midpoint fields" << std::endl;
	std::cout << "Phase 3: Testing V2 serialization format\n" << std::endl;

	int passCount = 0;
	int failCount = 0;

	// Phase 1 tests (existing functionality)
	if (testBasicGradientCreation())
		passCount++;
	else
		failCount++;

	if (testAddColor())
		passCount++;
	else
		failCount++;

	if (testV1FormatParsing())
		passCount++;
	else
		failCount++;

	if (testColorInterpolation())
		passCount++;
	else
		failCount++;

	if (testV1FormatRoundTrip())
		passCount++;
	else
		failCount++;

	if (testModifyColor())
		passCount++;
	else
		failCount++;

	// Phase 2 tests (new opacity/midpoint functionality)
	if (testDefaultOpacityAndMidpoint())
		passCount++;
	else
		failCount++;

	if (testModifyOpacity())
		passCount++;
	else
		failCount++;

	if (testModifyMidpoint())
		passCount++;
	else
		failCount++;

	if (testOpacityBoundsClamping())
		passCount++;
	else
		failCount++;

	if (testMidpointBoundsClamping())
		passCount++;
	else
		failCount++;

	// Phase 3 tests (new V2 serialization format)
	if (testV2FormatParsing())
		passCount++;
	else
		failCount++;

	if (testV2FormatRoundTrip())
		passCount++;
	else
		failCount++;

	if (testV1BackwardCompatibility())
		passCount++;
	else
		failCount++;

	std::cout << "\n=== Test Results ===" << std::endl;
	std::cout << "Passed: " << passCount << std::endl;
	std::cout << "Failed: " << failCount << std::endl;

	if (failCount == 0)
	{
		std::cout << "\nAll Phase 1+2+3 regression tests passed!" << std::endl;
		std::cout << "Phase 1: IsFormatV2() did not break anything." << std::endl;
		std::cout << "Phase 2: Opacity/midpoint fields work correctly." << std::endl;
		std::cout << "Phase 3: V2 serialization format works correctly." << std::endl;
		std::cout << "All existing gradient functionality still works." << std::endl;
		return 0;
	}
	else
	{
		std::cout << "\nSome tests failed!" << std::endl;
		return 1;
	}
}
