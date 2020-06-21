#include <QtWidgets>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QVBarModelMapper>
#include <QtCharts/QHBarModelMapper>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QLegendMarker>

QT_CHARTS_USE_NAMESPACE

#include "chartsdialog.h"

ChartsDialog::ChartsDialog(QSqlTableModel *model, QWidget *parent, Qt::WindowFlags flags)
    : VyborgChartsDialog(model, parent, flags)
{
    createCharts();
}

void ChartsDialog::createCharts()
{
//            QChart *chart = new QChart();
//            chart->setAnimationOptions(QChart::AllAnimations);

//            QBarSeries *series = new QBarSeries;

//            QHBarModelMapper *mapper = new QHBarModelMapper(this);
//            mapper->setFirstBarSetRow(0);
//            mapper->setLastBarSetRow(m_model->rowCount());
//            mapper->setFirstColumn(1);
//            mapper->setColumnCount(m_model->columnCount());
//            mapper->setSeries(series);
//            mapper->setModel(m_model);

//            chart->addSeries(series);

//            chart->legend()->setVisible(true);
//            chart->legend()->setAlignment(Qt::AlignBottom);
//            QList<QLegendMarker *> markers = chart->legend()->markers();
//            for (int i = 0; i < markers.count(); i++)
//                markers.at(i)->setLabel(QString::number(i + 2013));

//            QStringList categories;
//            categories << "Январь"
//                       << "Февраль"
//                       << "Март"
//                       << "Апрель"
//                       << "Май"
//                       << "Июнь"
//                       << "Июль"
//                       << "Август"
//                       << "Сентябрь"
//                       << "Октябрь"
//                       << "Ноябрь"
//                       << "Декабрь";
//            QBarCategoryAxis *axis = new QBarCategoryAxis();
//            axis->append(categories);

//            chart->createDefaultAxes();
//            chart->setAxisX(axis, series);

//            QChartView *chartView = new QChartView(chart);
//            chartView->setRenderHint(QPainter::Antialiasing);
//            chartView->setMinimumSize(1200, 640);


//            QVBoxLayout *dialogLayout = layout();
//            dialogLayout->addWidget(chartView);

//            layout()->addWidget(chartView);
}
