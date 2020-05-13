FROM ubuntu:20.04 as base
ENV DEBIAN_FRONTEND=noninteractive
RUN \
    apt update && \
    apt -y upgrade && \
    apt -y install --no-install-recommends \
        libqt5gui5 \
        libqt5network5 \
        && \
    rm -rf /var/lib/apt/lists/*

FROM base as builder

RUN \
    apt update && \
    apt -y install --no-install-recommends \
        bash \
        build-essential \
        cmake \
        git \
        nano \
        qt5-default \
        ninja-build \
        libssl-dev \
        libz-dev \
        && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir -p /work/build
COPY . /work/source

WORKDIR /work/build

RUN /work/source/server/docker/build.sh
RUN /work/source/server/docker/install.sh /work/install

ENTRYPOINT ["/bin/bash"]

FROM base as runner

COPY --from=builder /work/install /

RUN mkdir -p /data
WORKDIR /data
ENTRYPOINT ["/usr/bin/TelegramTestServer"]
