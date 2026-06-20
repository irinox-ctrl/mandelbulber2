/**
 * Mandelbulber Designer Plugin — Designer-safe wrapper for MyDoubleSpinBox
 * This lightweight version has NO Mandelbulber dependencies.
 * It provides the same Qt API so Qt Designer can instantiate and render it.
 */

#ifndef MANDELBULBER_DESIGNER_MY_DOUBLE_SPIN_BOX_H_
#define MANDELBULBER_DESIGNER_MY_DOUBLE_SPIN_BOX_H_

#include <QDoubleSpinBox>

class MyDoubleSpinBox : public QDoubleSpinBox
{
	Q_OBJECT

public:
	MyDoubleSpinBox(QWidget *parent = nullptr) : QDoubleSpinBox(parent) {}
	~MyDoubleSpinBox() override = default;
};

#endif // MANDELBULBER_DESIGNER_MY_DOUBLE_SPIN_BOX_H_
