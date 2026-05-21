#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTextEdit>
#include <QFile>
#include <QDebug>
#include <QXmlReader>
#include <QXmlStreamReader>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void xmlOpenRead();
private:
    QTextEdit *edit;

};
#endif // MAINWINDOW_H
