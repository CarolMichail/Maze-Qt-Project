#include "project.h"
#include "ui_project.h"

project::project(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::project)
{
    ui->setupUi(this);
}

project::~project()
{
    delete ui;
}

