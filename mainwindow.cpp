#include "mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("数字化工厂信息中心");
    setStyleSheet("background-color: #0a1029; color: #ffffff;");
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(15);
    gridLayout->setContentsMargins(10, 10, 10, 10);

    initUI();
    resize(1600, 900);
}

MainWindow::~MainWindow()
{
}

void MainWindow::initUI()
{
    // 1. 左上角：模具产量柱状图
    QStringList moldCat = {"设变", "修模", "新模"};
    QList<int> moldVal = {4, 2, 4};
    auto moldBar = createBarChart("模具产量", moldCat, moldVal);
    gridLayout->addWidget(moldBar, 0, 0);
    QPushButton *but1 = new QPushButton("打开", this);
    gridLayout->addWidget(but1, 0, 1);
    // 2. 每月模具产量趋势折线图
    QList<QPointF> moldTrend = {{1,60},{2,20},{3,30},{4,70},{5,100},{6,60}};
    auto moldLine = createLineChart("每月模具产量趋势图", moldTrend);
    gridLayout->addWidget(moldLine, 0, 1);

    // 3. 中间地图背景（用标签模拟）
    QLabel *mapLabel = new QLabel;
    mapLabel->setStyleSheet("background-color: #101838; border-radius: 8px;");
    mapLabel->setText("<div style='text-align:center; font-size:16px;'>数字化工厂信息中心<br><span style='font-size:12px; color:#888;'>地图区域</span></div>");
    mapLabel->setAlignment(Qt::AlignCenter);
    gridLayout->addWidget(mapLabel, 0, 2, 2, 1);

    // 4. 右上角品质占比饼图
    QStringList qualityLabels = {"延期", "正常交付", "加工中"};
    QList<double> qualityVals = {35, 36, 29};
    auto qualityPie = createPieChart(qualityLabels, qualityVals);
    gridLayout->addWidget(qualityPie, 0, 3);

    // 5. 班组合格率柱状图
    QStringList teamCat = {"CNC", "EDM", "线割", "磨床", "铣床", "外协"};
    QList<int> teamVal = {86,66,42,67,51,30};
    auto teamBar = createBarChart("班组合格率", teamCat, teamVal);
    gridLayout->addWidget(teamBar, 0, 4);

    // 6. 零件产量柱状图
    QStringList partCat = {"其他", "钢件", "电极"};
    QList<int> partVal = {5000,5000,6765};
    auto partBar = createBarChart("零件产量", partCat, partVal);
    gridLayout->addWidget(partBar, 1, 0);

    // 7. 每月零件产量趋势折线图
    QList<QPointF> partTrend = {{1,100},{2,20},{3,80},{4,30},{5,90},{6,40}};
    auto partLine = createLineChart("每月零件产量趋势图", partTrend);
    gridLayout->addWidget(partLine, 1, 1);

    // 8. 每日合格率统计折线图
    QList<QPointF> dailyQual;
    for(int i=1; i<=20; i++){
        dailyQual.append(QPointF(i, QRandomGenerator::global()->bounded(20,100)));
    }
    auto dailyLine = createLineChart("每日合格率统计", dailyQual);
    gridLayout->addWidget(dailyLine, 1, 3);

    // 9. 左下角模具进度表格（用标签卡片模拟）
    QWidget *progressWidget = new QWidget;
    QVBoxLayout *progressLayout = new QVBoxLayout(progressWidget);
    progressLayout->addWidget(new QLabel("模具进度"));
    for(int i=1; i<=5; i++){
        progressLayout->addWidget(createLabelCard(QString("FK%1").arg(i), "加工中"));
    }
    progressWidget->setStyleSheet("background-color: #101838; border-radius: 8px; padding:10px;");
    gridLayout->addWidget(progressWidget, 2, 0, 1, 2);

    // 10. 当月计划达成率柱状图
    QStringList planCat = {"模仁", "镶件", "辅件", "电极"};
    QList<int> planVal = {600,400,300,200};
    auto planBar = createBarChart("当月计划达成率", planCat, planVal);
    gridLayout->addWidget(planBar, 2, 2);

    // 11. 零件数卡片
    auto partCard = createLabelCard("零件数", "5275");
    gridLayout->addWidget(partCard, 2, 3);

    // 12. 合格率仪表盘（用标签模拟）
    auto rateCard = createLabelCard("合格率", "68%");
    gridLayout->addWidget(rateCard, 2, 4);
}

QChartView* MainWindow::createBarChart(const QString &title, const QStringList &categories, const QList<int> &values)
{
    QChart *chart = new QChart();
    chart->setTitle(title);
    chart->setBackgroundBrush(QBrush(QColor("#101838")));
    chart->setTitleBrush(QBrush(Qt::white));
    chart->setTitleFont(QFont("Arial", 10, QFont::Bold));

    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("");
    set->setColor(QColor("#00d4ff"));
    for(int v : values) set->append(v);
    series->append(set);
    chart->addSeries(series);

    // ========== 修复 1：循环添加分类 ==========
    QCategoryAxis *axisX = new QCategoryAxis();
    for (int i = 0; i < categories.size(); ++i) {
        axisX->append(categories.at(i), i);
    }
    axisX->setLabelsBrush(QBrush(Qt::white));

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelsBrush(QBrush(Qt::white));

    // ========== 修复 2：Qt5 正确绑定轴方式 ==========
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setStyleSheet("background-color: transparent;");
    return view;
}

QChartView* MainWindow::createLineChart(const QString &title, const QList<QPointF> &points)
{
    QChart *chart = new QChart();
    chart->setTitle(title);
    chart->setBackgroundBrush(QBrush(QColor("#101838")));
    chart->setTitleBrush(QBrush(Qt::white));
    chart->setTitleFont(QFont("Arial", 10, QFont::Bold));

    QLineSeries *series = new QLineSeries();
    series->setColor(QColor("#00d4ff"));
    series->setPen(QPen(QColor("#00d4ff"), 2));
    for(auto p : points) series->append(p);
    chart->addSeries(series);

    QValueAxis *axisX = new QValueAxis();
    axisX->setLabelsBrush(QBrush(Qt::white));
    chart->setAxisX(axisX, series);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100);
    axisY->setLabelsBrush(QBrush(Qt::white));
    chart->setAxisY(axisY, series);

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setStyleSheet("background-color: transparent;");
    return view;
}

QChartView* MainWindow::createPieChart(const QStringList &labels, const QList<double> &values)
{
    QChart *chart = new QChart();
    chart->setBackgroundBrush(QBrush(QColor("#101838")));
    chart->setTitleBrush(QBrush(Qt::white));

    QPieSeries *series = new QPieSeries();
    QList<QColor> colors = {QColor("#ff4444"), QColor("#44dd44"), QColor("#4488ff")};
    for(int i=0; i<labels.size(); i++){
        auto slice = series->append(labels[i], values[i]);
        slice->setColor(colors[i%colors.size()]);
        slice->setLabelBrush(QBrush(Qt::white));
    }
    series->setLabelsVisible(true);
    chart->addSeries(series);

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setStyleSheet("background-color: transparent;");
    return view;
}

QWidget* MainWindow::createLabelCard(const QString &title, const QString &value)
{
    QWidget *card = new QWidget;
    card->setStyleSheet("background-color: #101838; border-radius: 8px; padding:10px;");
    QVBoxLayout *layout = new QVBoxLayout(card);
    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("color: #aaa; font-size:12px;");
    QLabel *valueLabel = new QLabel(value);
    valueLabel->setStyleSheet("color: #00d4ff; font-size:24px; font-weight:bold;");
    valueLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);
    layout->addWidget(valueLabel);
    return card;
}
