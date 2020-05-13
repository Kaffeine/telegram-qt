# TelegramQt Server Docker

This Docker image will run a Telegram Test Server.

Note: the auth code is always "11111".

## Building the image

You need to obtain the source code in order to build the image. For example,
you can get the clone like this:

```
git clone https://github.com/Kaffeine/telegram-qt.git --depth 1
```

If you need to build an image from a telegram-qt sources, use the following `docker
 build` command from the top source directory:

```
cd telegram-qt
docker build -t telegramqt/server -f server/docker/Dockerfile .
```

If you have a "very stable" host system with old docker version (less than 17.06),
confider to use another docker file:

```
docker build -t telegramqt/server -f server/docker/Dockerfile-legacy .
```

## Running the server

Once you built the server, you can start it as follows:

```
TELEGRAM_ADDRESS=127.0.0.1
TELEGRAM_PORT=10443
HOST_DATA_DIR=~/TelegramServer
mkdir -p $HOST_DATA_DIR
docker run --rm --detach \
    --name telegram-server \
    -v $HOST_DATA_DIR:/data \
    -p $TELEGRAM_PORT:$TELEGRAM_PORT \
    telegramqt/server -a $TELEGRAM_ADDRESS -p $TELEGRAM_PORT
```

Set `TELEGRAM_ADDRESS` to the public (host) address for incoming connections.

Set `TELEGRAM_PORT` to the public (host) port for incoming connections.

Set `HOST_DATA_DIR` to the directory for all server data.

Use `--rm` to automatically remove the container when it exits (all data kept on the host).

Use `--detach` to run container in background.

Use `-v $HOST_DATA_DIR:/data` or `--mount type=bind,src=$HOST_DATA_DIR,dst=/data` to expose
the host data directory to the server.

Use `-p` to expose the server port from the container to the host system.

Use `-a $TELEGRAM_ADDRESS -p $TELEGRAM_PORT` to propagate the correct DC configuration to the clients.

You can then check that it has started correctly with:

```
docker logs telegram-server -f
```

Use the following command to kill the server:

```
docker kill telegram-server
```
