/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Quick Studio Components.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "app_environment.h"
#include <QDebug>

#ifdef WINDOWS
#include "win/BaseInfoDataModel.h"
#include "win/CenterViewDataModel.h"
#include "win/GaugeDataModel.h"
#include "win/TelltaleDataModel.h"
#include "win/WarningPopupDataModel.h"
#elif LINUX
#include "linux/BaseInfoDataModel.h"
#include "linux/CenterViewDataModel.h"
#include "linux/GaugeDataModel.h"
#include "linux/TelltaleDataModel.h"
#include "linux/WarningPopupDataModel.h"
#include "sm_telltalesm.h"
#include "zl_log.h"
#else
#include "zl_log.h"
#include "BaseInfoDataModel.h"
#include "CenterViewDataModel.h"
#include "GaugeDataModel.h"
#include "TelltaleDataModel.h"
#include "WarningPopupDataModel.h"
#include "sm_telltalesm.h"
#endif

#ifndef WINDOWS
static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type) {
    case QtDebugMsg:
        logDebug("%s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtInfoMsg:
        logInfo("%s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtWarningMsg:
        logWarning("%s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtCriticalMsg:
        logError("%s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtFatalMsg:
        logFatal("%s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    }
}
#endif

int main(int argc, char *argv[])
{
#ifndef WINDOWS
    logInit("HMI");
    qInstallMessageHandler(myMessageOutput);

    qWarning() << "HMIEnter main.cpp currentTime!!!";
#endif

    set_qt_environment();

    QGuiApplication app(argc, argv);

    BaseInfoDataModel baseinfodatamodel;
    CenterViewDataModel centerviewdatamodel;
    GaugeDataModel gaugedatamodel;
    TelltaleDataModel telltaledatamodel;
    WarningPopupDataModel warningpopupdatamodel;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/content/App.qml"));
    QObject::connect(
                &engine, &QQmlApplicationEngine::objectCreated, &app,
                [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");

    engine.rootContext()->setContextProperty("baseinfodatamodel", &baseinfodatamodel);
    engine.rootContext()->setContextProperty("centerviewdatamodel", &centerviewdatamodel);
    engine.rootContext()->setContextProperty("gaugedatamodel", &gaugedatamodel);
    engine.rootContext()->setContextProperty("telltaledatamodel", &telltaledatamodel);
    engine.rootContext()->setContextProperty("warningpopupdatamodel", &warningpopupdatamodel);

    engine.load(url);

    #ifndef WINDOWS
        qWarning() << "Load qml currentTime!!!";
    #endif

    if (engine.rootObjects().isEmpty()) {
    #ifndef WINDOWS
        qWarning() << "Failed to load qml component!!!";
    #endif
        return -1;
    }

#ifndef WINDOWS

    IsHMILaunched.setValue(true);

//程序退出时执行操作的两种方式
//    if(!app.exec())
//    {
//    qDebug()<<"quit";
//    }
    QObject::connect(&app, &QGuiApplication::aboutToQuit, [&]()
    {
        IsHMILaunched.setValue(false);
        qWarning() << "HMI quit!!!";
    });
#endif

    return app.exec();
}
