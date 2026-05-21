#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QChart>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QLineSeries>
#include <QPieSeries>
#include <QPieSlice>
#include <QValueAxis>
#include <QPainter>
#include <QChartView>
#include <QCategoryAxis>
#include <QPushButton>

using namespace QtCharts;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initUI();
    QWidget *centralWidget;
    QGridLayout *gridLayout;

    // 辅助函数：创建柱状图
    QChartView* createBarChart(const QString &title, const QStringList &categories, const QList<int> &values);
    // 辅助函数：创建折线图
    QChartView* createLineChart(const QString &title, const QList<QPointF> &points);
    // 辅助函数：创建饼图
    QChartView* createPieChart(const QStringList &labels, const QList<double> &values);
    // 辅助函数：创建标签卡片
    QWidget* createLabelCard(const QString &title, const QString &value);
};
#endif // MAINWINDOW_H
