/*
    Copyright (C) 2015 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef CTESTDISPATCHER_HPP
#define CTESTDISPATCHER_HPP

#include "CTelegramDispatcher.hpp"

class CTestDispatcher : public CTelegramDispatcher
{
    Q_OBJECT
public:
    explicit CTestDispatcher(QObject *parent = 0);

    void testProcessUpdate(const TLUpdate &update);
    void testSetDcConfiguration(const QVector<TLDcOption> newDcConfiguration);
    QVector<TLDcOption> testGetDcConfiguration() const { return m_dcConfiguration; }

};

#endif // CTESTDISPATCHER_HPP
