#ifndef PROJECT_H
#define PROJECT_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class project; }
QT_END_NAMESPACE

class project : public QDialog
{
    Q_OBJECT

public:
    project(QWidget *parent = nullptr);
    ~project();

private:
    Ui::project *ui;
};
#endif // PROJECT_H
