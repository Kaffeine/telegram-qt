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
    connect(m_core, SIGNAL(authStateChanged()), SLOT(whenAuthChanged()));
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

void MainWindow::whenAuthChanged()
{
    if (m_core->authState() == CTelegramCore::AuthSuccess)
        ui->authState->setText(tr("Success!"));
    else
        ui->authState->setText(QString::number(m_core->authState()));
}

void MainWindow::on_connectButton_clicked()
{
    if (ui->mainDcRadio->isChecked()) {
        // MainDC
        m_core->transport()->connectToDc("173.240.5.1", 443);
    } else {
        // TestingDC
        m_core->transport()->connectToDc("173.240.5.253", 443);
    }
}

void MainWindow::on_authButton_clicked()
{
    m_core->initAuth();
}

void MainWindow::on_dcHelpButton_clicked()
{
    m_core->getConfiguration();
}
