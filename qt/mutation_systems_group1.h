#ifndef MANDELBULBER2_QT_CMUTATIONSYSTEMSGROUP1_H_
#define MANDELBULBER2_QT_CMUTATIONSYSTEMSGROUP1_H_
#include <QWidget>
#include "ui_mutation_systems_group1.h"
class cMutationSystemsGroup1 : public QWidget {
	Q_OBJECT
public:
	explicit cMutationSystemsGroup1(QWidget *parent = nullptr);
	~cMutationSystemsGroup1() override;
	Ui::cMutationSystemsGroup1 *groupUi() const { return ui; }
private:
	Ui::cMutationSystemsGroup1 *ui;
};
#endif
