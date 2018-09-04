FROM opensuse/leap:15.0
LABEL maintainer="arichardson@FreeBSD.org"

# clang 5.0 is too old
RUN zypper -n refresh && zypper in -y \
  python3-base gcc-c++ \
  lsb-release which \
  bzip2 gperf zlib-devel libbz2-devel libarchive-devel \
  libbsd-devel

# Add lorder (TODO: build without it)
RUN zypper addrepo https://download.opensuse.org/repositories/devel:/tools:/building/openSUSE_Leap_15.0/devel:tools:building.repo && \
	zypper --gpg-auto-import-keys refresh && zypper -n install lorder

# Install clang 6.0
RUN zypper addrepo  https://download.opensuse.org/repositories/devel:tools:compiler/openSUSE_Leap_15.0/devel:tools:compiler.repo && \
	zypper --gpg-auto-import-keys refresh && zypper -n install clang6 lld6

RUN zypper -n in hostname patch which

VOLUME ["/source", "/build", "/output"]
CMD /bin/bash
