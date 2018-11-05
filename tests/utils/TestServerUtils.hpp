#ifndef TEST_SERVER_UTILS_HPP
#define TEST_SERVER_UTILS_HPP

#include "TestUserData.hpp"
#include "LocalCluster.hpp"
#include "TelegramServerUser.hpp"

Telegram::Server::User *tryAddUser(Telegram::Server::LocalCluster *cluster, const UserData &data)
{
    Telegram::Server::User *u = cluster->addUser(data.phoneNumber, data.dcId);
    if (u) {
        u->setFirstName(data.firstName);
        u->setLastName(data.lastName);
        if (!data.passwordHash.isEmpty()) {
            u->setPassword(data.passwordSalt, data.passwordHash);
        } else {
            u->setPlainPassword(data.password);
        }
    } else {
        qCritical() << "Unable to add a user";
    }
    return u;
}

#endif // TEST_SERVER_UTILS_HPP
