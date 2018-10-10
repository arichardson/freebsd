FROM ubuntu:16.04
LABEL maintainer="arichardson@FreeBSD.org"

RUN apt-get update && apt-get install -y \
  make ninja-build git \
  python3-minimal \
  lsb-release wget \
  bzip2 gperf libz-dev libbz2-dev libarchive-dev

# INSTALL clang 6.0
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
RUN echo "deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-7 main" > /etc/apt/sources.list.d/llvm.list
# RUN echo "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu trusty main" > /etc/apt/sources.list.d/r-toolchain.list
# RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 1E9377A2BA9EF27F
RUN apt-get update && apt-get install -y clang-7 lld-7

VOLUME ["/source", "/build", "/output"]
CMD /bin/bash
