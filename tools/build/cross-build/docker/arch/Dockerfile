FROM archlinux/base:latest
LABEL maintainer="arichardson@FreeBSD.org"
RUN pacman -Sy && pacman -S --noconfirm clang lld autoconf binutils make automake python git which inetutils gperf readline awk
# Patch signature is broken
# RUN pacman -Sy && pacman -S --noconfirm patch
RUN pacman -Syu --noconfirm

VOLUME ["/source", "/build", "/output"]
CMD /bin/bash
