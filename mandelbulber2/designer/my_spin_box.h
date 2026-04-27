/**
 * Mandelbulber Designer Plugin — Designer-safe wrapper for MySpinBox
 * This lightweight version has NO Mandelbulber dependencies.
 */

#ifndef MANDELBULBER_DESIGNER_MY_SPIN_BOX_H_
#define MANDELBULBER_DESIGNER_MY_SPIN_BOX_H_

#include <QSpinBox>

class MySpinBox : public QSpinBox
{
	Q_OBJECT

public:
	MySpinBox(QWidget *parent = nullptr) : QSpinBox(parent) {}
	~MySpinBox() override = default;
};

#endif // MANDELBULBER_DESIGNER_MY_SPIN_BOX_H_
