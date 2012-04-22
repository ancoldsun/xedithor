#include "setworkdirdialog.h"
#include "ui_setworkdirdialog.h"
#include <iostream>

SetWorkDirDialog::SetWorkDirDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetWorkDirDialog)
{
    ui->setupUi(this);

    m_expFormat=0;
    m_pathTexturePacker = "";
    m_pathOut ="";

    ui->comboBoxFormat->addItem("F_LGDX",binLibGDX);
    ui->comboBoxFormat->addItem("F_DEFAULT",binCommon);
    ui->lineEditTexturePath->setText(m_pathTexturePacker);

    connect(ui->comboBoxFormat,SIGNAL(currentIndexChanged(int)),this,SLOT(setExportFormat(int)));
    connect(ui->toolButtonTexturePath, SIGNAL(clicked()), this, SLOT(setPathTexturePacker()));
    connect(ui->toolButtonExportOut, SIGNAL(clicked()), this, SLOT(setPathOut()));
}

void SetWorkDirDialog::setPrevWorkDirPath(QString workDir,QString exportDir)
{
    m_pathTexturePacker = workDir;
    m_pathOut=exportDir;

    ui->lineEditTexturePath->setText(m_pathTexturePacker);
    ui->lineEditExportOut->setText(m_pathOut);
}

void SetWorkDirDialog::setPathTexturePacker()
{
    QString workDir=QFileDialog::getExistingDirectory(this, tr("Set working directory"),
                                                          QDir::currentPath(),
                                                          QFileDialog::ShowDirsOnly
                                                          | QFileDialog::DontResolveSymlinks);
    if(workDir.compare(""))
        m_pathTexturePacker=workDir;
    ui->lineEditTexturePath->setText(m_pathTexturePacker);
}

void SetWorkDirDialog::setPathOut()
{
    QString exportDir =QFileDialog::getExistingDirectory(this, tr("Set export directory"),
                                                 QDir::currentPath(),
                                                 QFileDialog::ShowDirsOnly

                                                 | QFileDialog::DontResolveSymlinks);
    if(exportDir.compare(""))
        m_pathOut=exportDir;
    ui->lineEditExportOut->setText(m_pathOut);
}

void SetWorkDirDialog::setExportFormat(int index)
{
    m_expFormat=index;
    if(m_expFormat==1)
    {
        // todo:
    }
    else if(m_expFormat==0)
    {
        // todo:
    }
}

SetWorkDirDialog::~SetWorkDirDialog()
{
    delete ui;
}

