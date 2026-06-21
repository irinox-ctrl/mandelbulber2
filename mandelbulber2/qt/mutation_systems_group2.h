#ifndef MANDELBULBER2_QT_CMUTATIONSYSTEMSGROUP2_H_
#define MANDELBULBER2_QT_CMUTATIONSYSTEMSGROUP2_H_
#include <QWidget>
#include "ui_mutation_systems_group2.h"
class cMutationSystemsGroup2 : public QWidget {
	Q_OBJECT
public:
	explicit cMutationSystemsGroup2(QWidget *parent = nullptr);
	~cMutationSystemsGroup2() override;
	Ui::cMutationSystemsGroup2 *groupUi() const { return ui; }
private:
	Ui::cMutationSystemsGroup2 *ui;
};
#endif
