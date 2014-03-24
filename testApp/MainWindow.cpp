#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "CTelegramCore.hpp"
#include "CTcpTransport.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_core = new CTelegramCore(this);
    m_core->setTransport(new CTcpTransport(m_core));

    connect(m_core->transport(), SIGNAL(connected()), SLOT(whenConnected()));
    connect(m_core, SIGNAL(pqReceived()), SLOT(whenPqReceived()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::whenConnected()
{
    ui->connectionState->setText(tr("Connected"));
}

void MainWindow::whenPqReceived()
{
    ui->nonce->setText(QByteArray(m_core->clientNonce().data, 16).toHex());
    ui->serverNonce->setText(QByteArray(m_core->serverNonce().data, 16).toHex());

    ui->pq->setText(QString::number(m_core->pq()));
    ui->p->setText(QString::number(m_core->p()));
    ui->q->setText(QString::number(m_core->q()));

    ui->serverPublicFingersprint->setText(QString::number(m_core->serverPublicFingersprint(), 16));
}

void MainWindow::on_connectButton_clicked()
{
    SDataCenter testingDc;
    testingDc.address = "173.240.5.253";
    testingDc.port = 443;

    SDataCenter mainDc;
    mainDc.address = "173.240.5.1";
    mainDc.port = 443;

    if (ui->mainDcRadio->isChecked()) {
        m_core->transport()->connectToDc(mainDc);
    } else {
        m_core->transport()->connectToDc(testingDc);
    }
}

void MainWindow::on_reqPqButton_clicked()
{
    m_core->requestPqAuthorization();
}

void MainWindow::on_dhParametersButton_clicked()
{
    m_core->requestDhParameters();
}
