#include "appconfig.h"
#include "qapplication.h"

AppConfig *AppConfig::m_Instance = 0;

AppConfig::AppConfig()
{
    m_setting = new QSettings(QApplication::applicationDirPath()+"/xedithor.conf",
                              QSettings::IniFormat);

    m_setting->beginGroup("WorkingDirectory");
    Config.workingDir = m_setting->value("workingDir","").toString();
    Config.exportDir  = m_setting->value("exportDir","").toString();

    if(Config.workingDir =="")
    {
        m_setting->setValue("workingDir",QApplication::applicationDirPath());
        m_setting->setValue("exportDir",QApplication::applicationDirPath());
        Config.workingDir =QApplication::applicationDirPath();
        Config.exportDir  =QApplication::applicationDirPath();
    }
    m_setting->endGroup();

}

AppConfig* AppConfig::getInstance()
{
    if(!m_Instance)
        m_Instance = new AppConfig();
    return m_Instance;
}

void AppConfig::deleteInstance()
{
    delete m_Instance;
    m_Instance = 0;
}

void AppConfig::saveWorkingDir(QString wDir,QString eDir)
{
    m_setting->beginGroup("WorkingDirectory");

    m_setting->setValue("workingDir",wDir);
    m_setting->setValue("exportDir",eDir);

    m_setting->endGroup();
}
