FROM archlinux/base:latest
LABEL maintainer="arichardson@FreeBSD.org"
RUN pacman -Sy && pacman -S --noconfirm clang lld autoconf binutils make automake python git which inetutils gperf readline awk
RUN pacman -Sy && pacman -S --noconfirm patch
RUN pacman -Syu --noconfirm
RUN pacman -Sy && pacman -S --noconfirm aarch64-linux-gnu-binutils

VOLUME ["/source", "/build", "/output"]
CMD /bin/bash
