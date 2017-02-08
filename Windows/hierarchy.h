#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <QDockWidget>

namespace Ui {
class Hierarchy;
}

class Hierarchy : public QDockWidget
{
    Q_OBJECT

public:
    explicit Hierarchy(QWidget *parent = 0);
    ~Hierarchy();

private:
    Ui::Hierarchy *ui;
};

#endif // HIERARCHY_H
