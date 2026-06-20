#ifndef MANDELBULBER2_QT_CMUTATIONSYSTEMSGROUP3_H_
#define MANDELBULBER2_QT_CMUTATIONSYSTEMSGROUP3_H_
#include <QWidget>
#include "ui_mutation_systems_group3.h"
class cMutationSystemsGroup3 : public QWidget {
	Q_OBJECT
public:
	explicit cMutationSystemsGroup3(QWidget *parent = nullptr);
	~cMutationSystemsGroup3() override;
	Ui::cMutationSystemsGroup3 *groupUi() const { return ui; }
private:
	Ui::cMutationSystemsGroup3 *ui;
};
#endif
