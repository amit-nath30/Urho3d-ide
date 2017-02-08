#ifndef RESOURCEBROWSER_H
#define RESOURCEBROWSER_H

#include <QDockWidget>

namespace Ui {
class ResourceBrowser;
}

class ResourceBrowser : public QDockWidget
{
    Q_OBJECT

public:
    explicit ResourceBrowser(QWidget *parent = 0);
    ~ResourceBrowser();

private:
    Ui::ResourceBrowser *ui;
};

#endif // RESOURCEBROWSER_H
