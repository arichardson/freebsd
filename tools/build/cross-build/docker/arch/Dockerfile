FROM archlinux/base:latest
LABEL maintainer="arichardson@FreeBSD.org"

RUN pacman -Sy && pacman -S --noconfirm clang lld autoconf binutils make automake python

RUN pacman -Sy && pacman -S --noconfirm git

VOLUME ["/source", "/build", "/output"]
CMD /bin/bash
