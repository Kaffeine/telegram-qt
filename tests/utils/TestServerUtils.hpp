#ifndef TEST_SERVER_UTILS_HPP
#define TEST_SERVER_UTILS_HPP

#include "TestUserData.hpp"
#include "LocalCluster.hpp"
#include "TelegramServerUser.hpp"

Telegram::Server::LocalUser *tryAddUser(Telegram::Server::LocalCluster *cluster, const UserData &data)
{
    Telegram::Server::LocalUser *u = cluster->addUser(data.phoneNumber, data.dcId);
    if (!u) {
        qCritical() << "Unable to add a user";
        return nullptr;
    }
    u->setFirstName(data.firstName);
    u->setLastName(data.lastName);
    if (!data.passwordHash.isEmpty()) {
        u->setPassword(data.passwordSalt, data.passwordHash);
    } else {
        u->setPlainPassword(data.password);
    }
    return u;
}

#endif // TEST_SERVER_UTILS_HPP
