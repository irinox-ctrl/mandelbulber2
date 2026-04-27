/**
 * Mandelbulber Designer Plugin — Designer-safe wrapper for MyComboBox
 * This lightweight version has NO Mandelbulber dependencies.
 */

#ifndef MANDELBULBER_DESIGNER_MY_COMBO_BOX_H_
#define MANDELBULBER_DESIGNER_MY_COMBO_BOX_H_

#include <QComboBox>

class MyComboBox : public QComboBox
{
	Q_OBJECT

public:
	MyComboBox(QWidget *parent = nullptr) : QComboBox(parent) {}
	~MyComboBox() override = default;
};

#endif // MANDELBULBER_DESIGNER_MY_COMBO_BOX_H_
