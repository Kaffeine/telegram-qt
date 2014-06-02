/*
    Copyright (C) 2014 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef CTELEGRAMCORE_HPP
#define CTELEGRAMCORE_HPP

#include <QObject>
#include <QMap>
#include <QVector>

#include "SDcInfo.hpp"

class CTelegramConnection;

class CTelegramCore : public QObject
{
    Q_OBJECT
public:
    explicit CTelegramCore(QObject *parent = 0);

    void setAppId(quint32 newId);
    bool setAppHash(const QString &newHash);

    void initConnection(const QString &address, quint32 port);

signals:
    void configurationChanged();

protected slots:
    void whenConnectionAuthChanged(int dc, int newState);
    void whenConnectionConfigurationUpdated(int dc);
    void whenConnectionDcIdUpdated(int connectionId, int newDcId);

protected:
    CTelegramConnection *createConnection(const SDcInfo &dc);

    quint32 m_appId;
    QString m_appHash;

    int m_activeDc;

    QMap<int, CTelegramConnection *> m_connections;

    QVector<SDcInfo> m_dcConfiguration;
};

#endif // CTELECORE_HPP
