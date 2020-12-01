// SPDX-License-Identifier: LGPL-2.1-or-later
/*
 * Copyright (C) 2020 Alexandr Akulich <akulichalexander@gmail.com>
 *
 * This file is a part of TelegramQt project.
 */

#include "telegramqt_global.h"

#include "MTProto/TLNumbers.hpp"
#include "Crypto/Aes.hpp"

namespace Telegram {

class TELEGRAMQT_INTERNAL_EXPORT BaseDhSession
{
public:
    enum class State {
        // Both
        //      Client
        //              Server
        Initial,
                PqRequested,                 // #1 Client sends ReqPq (or ReqPqMulti)
                        PqReplied,           // #2 Server sends ResPq
                PqAccepted,                  // #3 Client processes ResPQ
                DhRequested,                 // #4 Client sends ReqDHParams with PQInnerData (or PQInnerDataDc)
                        DhRepliedOK,         // #5a Server sends ServerDHParamsOk with ServerDHInnerData
                        DhRepliedFail,       // #5b Server sends ServerDHParamsFail
                DhGenerationResultRequested, // #6 Client sends SetClientDHParams with ClientDHInnerData)
                                             // #7, #8 The possible auth key and the key id is known to server and client
                        DhGenOk,             // #9a Server sends DhGenOk
                        DhGenRetry,          // #9b Server sends DhGenRetry
                        DhGenFail,           // #9c Server sends DhGenFail
        Failed,
        HasKey,
    };

    TLNumber128 clientNonce;
    TLNumber128 serverNonce;
    TLNumber256 newNonce;
    quint64 pq = 0;
    quint32 p = 0;
    quint32 q = 0;

    // quint32 expiresIn = 0;
    quint32 g = 0;
    QByteArray dhPrime;
    QByteArray gA;

    // void generateKey();
    // bool isTemporary() const { return expiresIn; }

    Crypto::AesKey tmpAesKey;
    State state = State::Initial;
};

} // Telegram namespace
