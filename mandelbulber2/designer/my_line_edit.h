/**
 * Mandelbulber Designer Plugin — Designer-safe wrapper for MyLineEdit
 * This lightweight version has NO Mandelbulber dependencies.
 */

#ifndef MANDELBULBER_DESIGNER_MY_LINE_EDIT_H_
#define MANDELBULBER_DESIGNER_MY_LINE_EDIT_H_

#include <QLineEdit>

class MyLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	MyLineEdit(QWidget *parent = nullptr) : QLineEdit(parent) {}
	~MyLineEdit() override = default;
};

#endif // MANDELBULBER_DESIGNER_MY_LINE_EDIT_H_
