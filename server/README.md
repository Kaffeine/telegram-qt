TelegramQt Server
=======================

TelegramQt-based Telegram Server

This server is developed to test a Telegram client without bothering the official server.

There is also no intention to make it a "production-ready" server and though it runs as
a cluster there is no purpose to make it scalable or performant.

Key Generation
==============

    mkdir ~/TelegramServer
    cd ~/TelegramServer
    openssl genpkey -algorithm RSA -out private_key.pem -pkeyopt rsa_keygen_bits:2048
    openssl rsa -pubout -in private_key.pem -out public_key.pem
    openssl rsa -pubin -in public_key.pem -RSAPublicKey_out > public_key_PKCS1.pem

Implemented API
===============

Registration/Authorization:

- auth.checkPassword
- auth.checkPhone
- auth.exportAuthorization
- auth.importAuthorization
- auth.sendCode
- auth.signIn
- auth.signUp

Account:

- account.checkUsername
- account.getPassword
- account.updateProfile
- account.updateStatus
- account.updateUsername

Contacts:

- contacts.getContacts
- contacts.importContacts
- contacts.resolveUsername

Users:

- users.getFullUser
- users.getUsers

Messages:

- messages.sendMessage
- messages.sendMedia (contact and uploaded document)
- messages.setTyping
- messages.getDialogs
- messages.getHistory
- messages.readHistory

Files:

- upload.getFile
- upload.saveFilePart

Photos:

- photos.getUserPhotos
- photos.uploadProfilePhoto

Note
=============

The server is expected to work with any Telegram client, though now there is no plan for
multilayer support and currently it work only with layer 72.

License
=======

This application is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License,
or (at your option) any later version.
