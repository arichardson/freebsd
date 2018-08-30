#!/usr/bin/env python3
import os
from pathlib import Path
import shlex
import subprocess
import sys

docker_image = "freebsd-crossbuild-ubuntu"

subprocess.check_call(["docker", "build", "-q", "-t", docker_image,
                       str(Path(__file__).parent / "docker/ubuntu")])
makeobjdirprefix = os.getenv("MAKEOBJDIRPREFIX")
if not makeobjdirprefix:
    sys.exit("Must set MAKEOBJDIRPREFIX")
if not Path(makeobjdirprefix).is_dir():
    sys.exit("MAKEOBJDIRPREFIX must be a directory")
makeobjdirprefix = str(Path(makeobjdirprefix).absolute())
srcroot = Path(__file__).parent.parent.parent.parent
if not (srcroot / "Makefile.inc1").exists():
    sys.exit("script moved but srcroot not updated")
srcroot = str(srcroot.resolve())

env_flags = ["--env", "MAKEOBJDIRPREFIX=/build"]
make_args = []
if docker_image == "freebsd-crossbuild-ubuntu":
    # Build everything with clang 7.0 (using /usr/bin/cc causes strange errors)
    env_flags += [
        "--env", "LD=/usr/bin/ld",
        # Need to pass -nobuiltininc since the clang 7.0 stddef.h, etc
        # are incompatible with the FreeBSD ones
        # TODO: fix them
        # We also need to pass -fuse-ld=lld to avoid linker errors
        "--env", "XCFLAGS=-integrated-as -nobuiltininc -fuse-ld=lld -Qunused-arguments",
        "--env", "XCXXFLAGS=-integrated-as -nobuiltininc -fuse-ld=lld -Qunused-arguments",
    ]
    make_args += [
        "--host-bindir=/usr/lib/llvm-7/bin",
        "--cross-bindir=/usr/lib/llvm-7/bin",
    ]

docker_args = ["docker", "run", "-t", "--rm",
               # mount the FreeBSD sources read-only
               "-v", str(srcroot) + ":" + srcroot + ":ro",
               "-v", makeobjdirprefix + ":/build",
               # "-v", makeobjdirprefix + ":/output",
               ] + env_flags + [docker_image]
make_cmd = [srcroot + "/tools/build/make.py"] + make_args + sys.argv[1:]
print("Running", " ".join(shlex.quote(s) for s in docker_args + make_cmd))
os.execvp("docker", docker_args + make_cmd)
