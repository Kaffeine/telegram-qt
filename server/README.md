TelegramQt Server
=======================

TelegramQt-based Telegram Server

Key Generation
==============

    mkdir ~/TelegramServer
    cd ~/TelegramServer
    openssl genpkey -algorithm RSA -out private_key.pem -pkeyopt rsa_keygen_bits:2048
    openssl rsa -pubout -in private_key.pem -out public_key.pem

License
=======

This application is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License,
or (at your option) any later version.
