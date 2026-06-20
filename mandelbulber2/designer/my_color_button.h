/**
 * Mandelbulber Designer Plugin — Designer-safe wrapper for MyColorButton
 * This lightweight version has NO Mandelbulber dependencies.
 * Renders as a QPushButton with "Color" text in Designer.
 */

#ifndef MANDELBULBER_DESIGNER_MY_COLOR_BUTTON_H_
#define MANDELBULBER_DESIGNER_MY_COLOR_BUTTON_H_

#include <QPushButton>

class MyColorButton : public QPushButton
{
	Q_OBJECT

public:
	MyColorButton(QWidget *parent = nullptr) : QPushButton(parent)
	{
		setText("Color");
	}
	~MyColorButton() override = default;
};

#endif // MANDELBULBER_DESIGNER_MY_COLOR_BUTTON_H_
