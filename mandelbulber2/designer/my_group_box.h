/**
 * Mandelbulber Designer Plugin — Designer-safe wrapper for MyGroupBox
 * This lightweight version has NO Mandelbulber dependencies.
 */

#ifndef MANDELBULBER_DESIGNER_MY_GROUP_BOX_H_
#define MANDELBULBER_DESIGNER_MY_GROUP_BOX_H_

#include <QGroupBox>

class MyGroupBox : public QGroupBox
{
	Q_OBJECT

public:
	MyGroupBox(QWidget *parent = nullptr) : QGroupBox(parent) {}
	~MyGroupBox() override = default;
};

#endif // MANDELBULBER_DESIGNER_MY_GROUP_BOX_H_
