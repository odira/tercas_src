#include <QtWidgets>
#include <QtSql>

#include "imagedelegate.h"
#include "emblemdialog.h"


ImageDelegate::ImageDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    m_state = QStyle::State_Enabled;
}

void ImageDelegate::paint(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    const QAbstractItemModel *model = index.model();
    int id = model->data(model->index(index.row(), 0)).toInt();


    QPixmap pixmap;

    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.prepare("SELECT emblem FROM org WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();
    while (query.next()) {
        QByteArray emblem = query.value(0).toByteArray();
        QSqlDatabase::database().commit();

        pixmap.loadFromData(emblem);
    }




    QRect mainRect = option.rect;

    QRect pixmapRect = mainRect;
    pixmapRect.setHeight(mainRect.height() - 4);
    pixmapRect.setWidth(pixmapRect.height());
    pixmapRect.setX(mainRect.x() + 2);
    pixmapRect.setY(mainRect.y() + 2);
    pixmap = pixmap.scaled(pixmapRect.width(), pixmapRect.height(),
                           Qt::KeepAspectRatio,
                           Qt::SmoothTransformation);


    QRect buttonRect = mainRect;
    buttonRect.setWidth(mainRect.width() - 2 - pixmapRect.width() - 4);
    buttonRect.setHeight(mainRect.height() - 4);
    buttonRect.setX(mainRect.x() + 2 + pixmapRect.width() + 2);
    buttonRect.setY(mainRect.y() + 2);

    QStyleOptionButton button;
    button.rect  = buttonRect;
    button.text  = QString(trUtf8("Изменить эмблему"));
    button.state = m_state;

    QApplication::style()->drawItemPixmap(painter, pixmapRect, Qt::AlignCenter, pixmap);
    QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);


//    QTableView *view = dynamic_cast<QTableView *>(this->parent());
//    if (view) {
//        QPushButton *menuButton = dynamic_cast<QPushButton *>(view->indexWidget(index));
//        if (!menuButton) {
//            QPushButton *menuButton = new QPushButton(trUtf8("Menu"));
//            connect(menuButton, SIGNAL(clicked()),
//                    SLOT(on_menuButtonClicked()));
//            view->setIndexWidget(index, menuButton);
//        }
//    }



//    QByteArray emblem = index.data().toByteArray();

//    QTableView *view = dynamic_cast<QTableView *>(this->parent());
//    if (view) {
//        QLabel *emblemLabel = dynamic_cast<QLabel *>(view->indexWidget(index));
//        if (!emblemLabel) {
//            QByteArray emblem = index.data().toByteArray();
//            QFile file("/tmp/image.jpg");
//            if (!file.open(QFile::WriteOnly)) {
//                qDebug() << "Unable to write /tmp/image.jpg";
//            }
//            file.write(emblem);
//            file.close();

//            QPixmap pixmap(file.fileName());
//            pixmap = pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);

//            QLabel *emblemLabel = new QLabel;
//            emblemLabel->setPixmap(pixmap);
//            //            emblemLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//            emblemLabel->setMinimumSize(32, 32);
//            emblemLabel->setMaximumSize(32, 32);

//            view->setIndexWidget(index, emblemLabel);
//        }
//    }



//    QTableView *view = dynamic_cast<QTableView *>(this->parent());
//    if (view) {
//        QComboBox *comboBox = dynamic_cast<QComboBox *>(view->indexWidget(index));
//        if (!comboBox) {
//            QComboBox *comboBox = new QComboBox;
//            comboBox->addItem(trUtf8("Добавить..."));
//            comboBox->addItem(trUtf8("Смотреть..."));
//            connect(comboBox, SIGNAL(activated(int)),
//                    SLOT(on_comboBoxActivated()));
//            view->setIndexWidget(index, comboBox);
//        }
//    }

//    QAbstractItemModel *model = view->model();
//    m_id = model->data(model->index(index.row(), 0)).toInt();

}

QSize ImageDelegate::sizeHint(const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    return QSize(48, 48);
}

bool ImageDelegate::editorEvent(QEvent *event,
                                QAbstractItemModel *model,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index)
{
    Q_UNUSED(model)
    Q_UNUSED(option)
    Q_UNUSED(index)

    if (event->type() == QEvent::MouseButtonPress) {
        m_state = QStyle::State_Sunken;

        const QAbstractItemModel *model = index.model();
        int m_id = model->data(model->index(index.row(), 0)).toInt();

        EmblemDialog dialog(m_id);
        dialog.exec();

        m_state = QStyle::State_Raised;
    }

    return true;
}

//void ImageDelegate::on_comboBoxActivated()
//{
//    QComboBox *comboBox = qobject_cast<QComboBox *>(sender());
//    QString comboBoxText = comboBox->currentText();

//    if (comboBoxText == "Добавить...") {
//        QFileDialog *fileDialog = new QFileDialog;
//        fileDialog->setFileMode(QFileDialog::AnyFile);
//        fileDialog->setDirectory("/home/kubuntu/Downloads");
//        fileDialog->setNameFilter("Images (*.jpg)");
//        if (fileDialog->exec()) {
//            QStringList fileList = fileDialog->selectedFiles();
//            if (!fileList.empty()) {
//                QFile file(fileList.at(0));
//                if (file.exists()) {
//                    if (file.open(QFile::ReadOnly)) {
//                        QByteArray emblem = file.readAll();

//                        QSqlDatabase::database().transaction();
//                        QSqlQuery query;
//                        query.prepare("UPDATE org "
//                                      "SET emblem=:emblem "
//                                      "WHERE id=:id");
//                        query.bindValue(":emblem", emblem);
//                        query.bindValue(":id", m_id);
//                        query.exec();
//                        if (query.lastError().isValid()) {
//                            qDebug() << "ERROR" << query.lastError().text();
//                            QSqlDatabase::database().rollback();
//                        } else {
//                            QSqlDatabase::database().commit();
//                        }

//                        file.close();
//                    }
//                }
//            }
//        }
//    } else if (comboBoxText == "Смотреть...") {
//        QSqlDatabase::database().transaction();
//        QSqlQuery query;
//        query.prepare("SELECT emblem FROM org WHERE id=:id");
//        query.bindValue(":id", m_id);
//        query.exec();
//        while (query.next()) {
//            QByteArray emblem = query.value(0).toByteArray();
//            QSqlDatabase::database().commit();

//            QFile file("/tmp/image.jpg");
//            if (!file.open(QFile::WriteOnly)) {
//                qDebug() << "Unable to write /tmp/image.jpg";
//            }
//            file.write(emblem);
//            file.close();
//        }

//        QLabel *label = new QLabel;
//        label->setAlignment(Qt::AlignCenter);
//        label->setFrameShape(QFrame::Box);
//        label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//        label->setBackgroundRole(QPalette::Base);
//        label->setAutoFillBackground(true);
//        label->setMinimumSize(132, 132);
//        label->show();
//    }
//}
