// Xedithor : 2D sprite editor
// Copyright [2011] Edi Ermawan <edi.ermawan@gmail.Com>

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
    QString exportDirSrc;
    QString package;
};

class AppConfig : public QObject
{
    Q_OBJECT
public:
    static AppConfig *getInstance();
    static void deleteInstance();

    QSettings *appSettings() const { return m_setting; }
    configurationValue Config;
    void saveWorkingDir(QString wDir,QString eDir,QString eDirSrc,QString package);

private:
    QSettings* m_setting;
    static AppConfig *m_Instance;
    AppConfig();

signals:

public slots:

};

#endif // APPCONFIG_H
