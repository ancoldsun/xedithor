#include "exportdialog.h"
#include "ui_exportdialog.h"
#include <iostream>

ExportDialog::ExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDialog)
{
    ui->setupUi(this);

    m_expFormat=0;
    m_pathTexturePacker = QApplication::applicationDirPath()+"/extbin/texturepacker.jar";

    ui->comboBoxFormat->addItem("F_LGDX",binLibGDX);
    ui->comboBoxFormat->addItem("F_DEFAULT",binCommon);
    ui->lineEditTexturePath->setText(m_pathTexturePacker);

    connect(ui->comboBoxFormat,SIGNAL(currentIndexChanged(int)),this,SLOT(setExportFormat(int)));
    connect(ui->toolButtonTexturePath, SIGNAL(clicked()), this, SLOT(setPathTexturePacker()));
    connect(ui->toolButtonExportOut, SIGNAL(clicked()), this, SLOT(setPathOut()));


}

void ExportDialog::setPathTexturePacker()
{
    m_pathTexturePacker=QFileDialog::getOpenFileName(this,tr("Open TexturePacker.jar"), QDir::currentPath());
    ui->lineEditTexturePath->setText(m_pathTexturePacker);
}

void ExportDialog::setPathOut()
{
    m_pathOut =QFileDialog::getSaveFileName(this, tr("Export File"),
                                QDir::currentPath()+"/untitled.bin",
                                tr("xdsprite (*.bin)"));
    ui->lineEditExportOut->setText(m_pathOut);

}

void ExportDialog::setExportFormat(int index)
{
    m_expFormat=index;
    if(m_expFormat==1){
        ui->toolButtonTexturePath->setDisabled(true);
        ui->lineEditTexturePath->setDisabled(true);
        ui->label_3->setDisabled(true);
    } else if(m_expFormat==0) {
        ui->toolButtonTexturePath->setEnabled(true);
        ui->lineEditTexturePath->setEnabled(true);
        ui->label_3->setEnabled(true);
    }
    std::cout<<" format: "<<index<<std::endl;
}

ExportDialog::~ExportDialog()
{
    delete ui;
}
