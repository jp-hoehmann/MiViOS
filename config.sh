#!/usr/bin/env bash

#
# config.sh
#
# Created by Jean-Pierre Höhmann on 18-08-25.
#
# Copyright 2018 Jean-Pierre Höhmann (@NuvandaPV) <jean-pierre@höhmann.info>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

set -euxo pipefail

#
# Build configuration.
#

export MAKE HOST AR AS CC PREFIX EXEC_PREFIX BOOTDIR LIBDIR INCLUDEDIR CFLAGS CPPFLAGS SYSROOT LD_LIBRARY_PATH PATH

MAKE="${MAKE:-}"
HOST="${HOST:-}"

# FIXME None of STATICDIR ISODIR ISOFILE TMPDIR PIDDIR SYSROOT PROJECTDIR can contain spaces.
# FIXME The individual file names in FILES, as well as the individual project names in PROJECTS cannot contain spaces.

TARGET="${TARGET:-Default}"

DEFAULT_CFLAGS='-O2 -gdwarf -g2'
DEFAULT_CPPFLAGS=''
DEFAULT_LDFLAGS=''
DEBUG_CFLAGS='-O0 -ggdb -g3'
DEBUG_CPPFLAGS=''
DEBUG_LDFLAGS=''
RELEASE_CFLAGS='-O3 -g1'
RELEASE_CPPFLAGS=''
RELEASE_LDFLAGS=''

PATH="${PWD}/bin:${PATH}"
LD_LIBRARY_PATH=''

PROJECTS="${PROJECTS:-$(./build-order.txt)}"
FILES="${FILES:-$(./files-to-install.txt)}"
GRUBENV="${GRUBENV:-$(./grub.env)}"

MAKE=${MAKE:-make}
HOST=${HOST:-$(./default-host.txt)}

AR=${HOST}-ar
AS=${HOST}-as
CC=${HOST}-gcc

PREFIX=/usr
EXEC_PREFIX=${PREFIX}
BOOTDIR=/boot
LIBDIR=${EXEC_PREFIX}/lib
INCLUDEDIR=${PREFIX}/include

TARGET="${TARGET^^*}"
CFLAGS="${TARGET}_CFLAGS"
CPPFLAGS="${TARGET}_CPPFLAGS"
LDFLAGS="${TARGET}_LDFLAGS"
CFLAGS="${!CFLAGS}"
CPPFLAGS="${!CPPFLAGS}"
LDFLAGS="${!LDFLAGS}"

STATICDIR="${PWD}/src/static"
ISODIR="${PWD}/build/isodir"
ISOFILE="${PWD}/mivios.iso"
TMPDIR="${PWD}/tmp"
PIDDIR="${PWD}/pids"

# Configure the cross-compiler to use the desired system root.
SYSROOT="$(pwd)/build/sysroot"
CC="$CC --sysroot=$SYSROOT"

# Work around that the -elf gcc targets doesn't have a system include directory,
# if it was configured with --without-headers rather than with --with-sysroot.
if echo "$HOST" | grep -Eq -- '-elf($|-)'
then
    CC="$CC -isystem=$INCLUDEDIR"
fi
