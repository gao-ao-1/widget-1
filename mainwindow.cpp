#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    edit = new QTextEdit(this);
    this->resize(1000, 1000);
    edit->resize(400,400);
    QString path = "E:/UI/text.xml";
    QFile file(path);


}

MainWindow::~MainWindow()
{
}

void MainWindow::xmlOpenRead()
{
    QString path = "E:/UI/text.xml";
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "打开失败：" << file.errorString();
        return;
    }
    QXmlStreamReader xmlReader(&file);  // 直接用，不需要 new
    while (xmlReader.atEnd() && !xmlReader.hasError()) {

    }
      

}

