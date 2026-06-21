#include "mutation_systems_group1.h"
#include "ui_mutation_systems_group1.h"
cMutationSystemsGroup1::cMutationSystemsGroup1(QWidget *parent) : QWidget(parent), ui(new Ui::cMutationSystemsGroup1) { ui->setupUi(this); }
cMutationSystemsGroup1::~cMutationSystemsGroup1() { delete ui; }
