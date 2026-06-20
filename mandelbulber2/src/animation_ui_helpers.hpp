#ifndef MANDELBULBER2_SRC_ANIMATION_UI_HELPERS_HPP_
#define MANDELBULBER2_SRC_ANIMATION_UI_HELPERS_HPP_

#include <QApplication>
#include <QMessageBox>
#include <QMetaObject>
#include <QThread>

#include "render_window.hpp"

inline QMessageBox::StandardButton AskAnimationQuestion(RenderWindow *window,
	const QString &questionTitle, const QString &questionText,
	const QMessageBox::StandardButtons buttons)
{
	if (!window) return QMessageBox::NoButton;

	if (QThread::currentThread() == QApplication::instance()->thread())
	{
		return QMessageBox::question(
			window->GetCentralWidget(), questionTitle, questionText, buttons);
	}

	QMessageBox::StandardButton reply = QMessageBox::NoButton;
	QMetaObject::invokeMethod(window, "AskQuestionBlocking", Qt::BlockingQueuedConnection,
		Q_RETURN_ARG(QMessageBox::StandardButton, reply), Q_ARG(QString, questionTitle),
		Q_ARG(QString, questionText), Q_ARG(QMessageBox::StandardButtons, buttons));
	return reply;
}

#endif /* MANDELBULBER2_SRC_ANIMATION_UI_HELPERS_HPP_ */
