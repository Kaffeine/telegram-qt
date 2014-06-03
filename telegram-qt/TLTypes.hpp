#ifndef TLTYPES_HPP
#define TLTYPES_HPP

#include "TLNumbers.hpp"

struct TLFileLocation {
    TLFileLocation() :
        dc(0),
        volumeId(0),
        localId(0),
        secret(0) { }

    TLFileLocation(const TLFileLocation &anotherLocation) :
        dc(anotherLocation.dc),
        volumeId(anotherLocation.volumeId),
        localId(anotherLocation.localId),
        secret(anotherLocation.secret) { }

    TLFileLocation &operator=(const TLFileLocation &anotherLocation) {
        dc       = anotherLocation.dc;
        volumeId = anotherLocation.volumeId;
        localId  = anotherLocation.localId;
        secret   = anotherLocation.secret;

        return *this;
    }

    quint32 dc;
    quint64 volumeId;
    quint32 localId;
    quint64 secret;
};

struct TLUserProfilePhoto {
    quint64 id;
    TLFileLocation small;
    TLFileLocation big;

    TLUserProfilePhoto() :
        id(0) { }

    TLUserProfilePhoto(const TLUserProfilePhoto &anotherUserPhoto) :
        id(anotherUserPhoto.id),
        small(anotherUserPhoto.small),
        big(anotherUserPhoto.big) { }

    TLUserProfilePhoto &operator=(const TLUserProfilePhoto &anotherUserPhoto) {
        id    = anotherUserPhoto.id;
        small = anotherUserPhoto.small;
        big   = anotherUserPhoto.big;

        return *this;
    }
};

struct TLUserStatus {
    enum Type {
        Empty,
        Online,
        Offline
    };

    TLUserStatus(Type t = Empty) :
        type(t),
        expires(0),
        wasOnline(0) { }

    TLUserStatus(const TLUserStatus &anotherStatus) :
        type(anotherStatus.type),
        expires(anotherStatus.expires),
        wasOnline(anotherStatus.wasOnline) { }

    TLUserStatus &operator=(const TLUserStatus &anotherStatus) {
        type      = anotherStatus.type;
        expires   = anotherStatus.expires;
        wasOnline = anotherStatus.wasOnline;

        return *this;
    }

    Type type;
    quint32 expires;
    quint32 wasOnline;
};

struct TLUser {
    TLUser() :
        id(0),
        accessHash(0),
        inActive(false) { }

    TLUser(const TLUser &anotherUser) :
        id(anotherUser.id),
        firstName(anotherUser.firstName),
        lastName(anotherUser.lastName),
        accessHash(anotherUser.accessHash),
        phone(anotherUser.phone),
        photo(anotherUser.photo),
        status(anotherUser.status),
        inActive(anotherUser.inActive) { }

    TLUser &operator=(const TLUser &anotherUser) {
        id         = anotherUser.id;
        firstName  = anotherUser.firstName;
        lastName   = anotherUser.lastName;
        accessHash = anotherUser.accessHash;
        phone      = anotherUser.phone;
        photo      = anotherUser.photo;
        status     = anotherUser.status;
        inActive   = anotherUser.inActive;

        return *this;
    }

    quint32 id;
    QString firstName;
    QString lastName;
    quint64 accessHash;
    QString phone;
    TLUserProfilePhoto photo;
    TLUserStatus status;
    bool inActive;
};

struct TLContact {
    TLContact() :
        id(0),
        mutual(false) { }

    TLContact(const TLContact &anotherContact) :
        id(anotherContact.id),
        mutual(anotherContact.mutual) { }

    TLContact &operator=(const TLContact &anotherContact) {
        id = anotherContact.id;
        mutual = anotherContact.mutual;

        return *this;
    }

    quint32 id;
    bool mutual;
};

#endif // TLTYPES_HPP
