#pragma once

#if ! defined(Q_OS_IOS)

#include <QProcess>
#include <QVariantList>

class Process : public QProcess {
    Q_OBJECT

public:
    Process(QObject *parent = Q_NULLPTR) : QProcess(parent) { }

    Q_INVOKABLE void start(const QString &program, const QVariantList &arguments = QVariantList())
    {
        if (arguments.isEmpty()) {
            QProcess::start(program);
            return;
        }

        QStringList args;

        // convert QVariantList from QML to QStringList for QProcess

        for (int i = 0; i < arguments.length(); i++)
            args << arguments[i].toString();

        QProcess::start(program, args);
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
