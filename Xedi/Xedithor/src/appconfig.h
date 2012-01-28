// Xedithor : 2D sprite editor
// Copyright (C) 2011-2012 Edi Ermawan <edi.ermawan@gmail.Com>
// License  :
//

#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QObject>
#include <qsettings.h>

/* class for manage (open, save ) app configuration
 * this is singleton class
 * fileconfig format : INI
 */

class QSettings;

struct configurationValue
{
    QString workingDir;
    QString exportDir;
};

class AppConfig : public QObject
{
    Q_OBJECT
public:
    static AppConfig *getInstance();
    static void deleteInstance();

    QSettings *appSettings() const { return m_setting; }
    configurationValue Config;
    void saveWorkingDir(QString wDir,QString eDir);

private:
    QSettings* m_setting;
    static AppConfig *m_Instance;
    AppConfig();

signals:

public slots:

};

#endif // APPCONFIG_H
