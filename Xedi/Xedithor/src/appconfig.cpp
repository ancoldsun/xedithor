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
    Config.exportDirSrc  = m_setting->value("exportDirSrc","").toString();
    Config.package       = m_setting->value("package","").toString();

    if(Config.workingDir =="")
    {
        m_setting->setValue("workingDir",QApplication::applicationDirPath());
        m_setting->setValue("exportDir",QApplication::applicationDirPath());
        m_setting->setValue("exportDirSrc",QApplication::applicationDirPath());
        m_setting->setValue("package","");

        Config.workingDir    = QApplication::applicationDirPath();
        Config.exportDir     = QApplication::applicationDirPath();
        Config.exportDirSrc  = QApplication::applicationDirPath();
        Config.package       = "";
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

void AppConfig::saveWorkingDir(QString wDir,QString eDir,QString eDirSrc,QString package)
{
    m_setting->beginGroup("WorkingDirectory");

    m_setting->setValue("workingDir",wDir);
    m_setting->setValue("exportDir",eDir);
    m_setting->setValue("exportDirSrc",eDirSrc);
    m_setting->setValue("package",package);

    m_setting->endGroup();
}
