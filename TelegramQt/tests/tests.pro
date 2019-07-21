TEMPLATE = subdirs
SUBDIRS += tst_crypto
SUBDIRS += tst_CTelegramTransport
#SUBDIRS += tst_CTelegramConnection
SUBDIRS += tst_MTProtoStream
#SUBDIRS += tst_CTelegramDispatcher
SUBDIRS += tst_UniqueLazyPointer
SUBDIRS += tst_utils
SUBDIRS += tst_RpcError
SUBDIRS += tst_RpcLayer

OTHER_FILES += \
    CMakeLists.txt
