#include "mutation_systems_group2.h"
#include "ui_mutation_systems_group2.h"
cMutationSystemsGroup2::cMutationSystemsGroup2(QWidget *parent) : QWidget(parent), ui(new Ui::cMutationSystemsGroup2) { ui->setupUi(this); }
cMutationSystemsGroup2::~cMutationSystemsGroup2() { delete ui; }
