FROM ubuntu:23.04

RUN apt-get -qq update -y \
      && apt-get -qq install -y --no-install-recommends \
        ca-certificates \
        build-essential \
        clang-format \
        gdb \
        vim \
    && apt-get clean -y \
    && apt-get autoremove -y \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /opt/app

