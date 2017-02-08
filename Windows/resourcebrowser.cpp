#include "resourcebrowser.h"
#include "ui_resourcebrowser.h"

ResourceBrowser::ResourceBrowser(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::ResourceBrowser)
{
    ui->setupUi(this);
}

ResourceBrowser::~ResourceBrowser()
{
    delete ui;
}
