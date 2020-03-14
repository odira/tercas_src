#pragma once

#if ! defined(Q_OS_IOS)

#include <QProcess>
#include <QVariantList>

#include <QDebug>

class Process : public QProcess {
    Q_OBJECT

public:
    Process(QObject *parent = Q_NULLPTR) : QProcess(parent) { }

    Q_INVOKABLE void start(const QString &program, const QVariantList &arguments = QVariantList())
    {
        if (arguments.isEmpty())
        {
            QProcess * process = new QProcess;
            connect(process, &QProcess::errorOccurred, [=](QProcess::ProcessError error)
            {
                qDebug() << "error enum val = " << error << Qt::endl;
            });

            process->start(program, QStringList());
            process->waitForStarted(1000);
            process->waitForFinished(1000);
            foreach(QString line, QString(process->readAll()).split("\n")) {
                qDebug() << line;
            }
        }
        else
        {
            QStringList args;
            // convert QVariantList from QML to QStringList for QProcess
            for (int i = 0; i < arguments.length(); i++)
                args << arguments[i].toString();

            QProcess::start(program, args);
        }
    }

    Q_INVOKABLE QByteArray readAll() {
        return QProcess::readAll();
    }
};

#else

#include <QObject>

class Process {
public:
    Process() {}
};

#endif
