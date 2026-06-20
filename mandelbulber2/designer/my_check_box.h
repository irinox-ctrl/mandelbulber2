/**
 * Mandelbulber Designer Plugin — Designer-safe wrapper for MyCheckBox
 * This lightweight version has NO Mandelbulber dependencies.
 */

#ifndef MANDELBULBER_DESIGNER_MY_CHECK_BOX_H_
#define MANDELBULBER_DESIGNER_MY_CHECK_BOX_H_

#include <QCheckBox>

class MyCheckBox : public QCheckBox
{
	Q_OBJECT

public:
	MyCheckBox(QWidget *parent = nullptr) : QCheckBox(parent) {}
	~MyCheckBox() override = default;
};

#endif // MANDELBULBER_DESIGNER_MY_CHECK_BOX_H_
