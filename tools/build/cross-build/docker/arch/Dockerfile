FROM archlinux/base:latest
LABEL maintainer="arichardson@FreeBSD.org"

RUN pacman -Sy && pacman -S --noconfirm clang lld autoconf binutils make automake python

RUN pacman -Sy && pacman -S --noconfirm git
# hostname,which,patch are not included by default:
RUN pacman -Sy && pacman -S --noconfirm which inetutils patch
RUN pacman -Sy && pacman -S --noconfirm gperf

VOLUME ["/source", "/build", "/output"]
CMD /bin/bash
