FROM alpine:3.8
LABEL maintainer="arichardson@FreeBSD.org"

# clang 5.0 is too old (but let's try anyway)
RUN apk add clang git python3 binutils autoconf automake
RUN apk add lld libtool make

# we need gcc and musl-dev to build any host binary
RUN apk add gcc musl-dev linux-headers

VOLUME ["/source", "/build", "/output"]
CMD /bin/bash
