FROM ubuntu:18.04
LABEL maintainer="arichardson@FreeBSD.org"

RUN apt-get update && apt-get install -y \
  make ninja-build git \
  python3-minimal \
  lsb-release wget \
  bzip2 gperf libz-dev libbz2-dev libarchive-dev

RUN apt-get install -y --no-install-recommends gnupg


# INSTALL clang 9.0
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
RUN echo "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-9 main" > /etc/apt/sources.list.d/llvm.list
RUN apt-get update && apt-get install -y --no-install-recommends clang-9 lld-9

VOLUME ["/source", "/build", "/output"]
CMD /bin/bash
