#!/usr/bin/env bash

#
# config.sh
#
# Created by Jean-Pierre Höhmann on 25.08.18.
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

# FIXME None of STATICDIR ISODIR ISOFILE TMPDIR PIDDIR SYSROOT PROJECTDIR can contain spaces.
# FIXME The individual file names in FILES, as well as the individual project names in PROJECTS cannot contain spaces.

PROJECTS="${PROJECTS:-$(./txt.pl build-order.txt)}"
FILES="${FILES:-$(./txt.pl files-to-install.txt)}"
GRUBENV="${GRUBENV:-$(./txt.pl grub.env)}"

MAKE=${MAKE:-make}
HOST=${HOST:-$(./txt.pl default-host.txt)}

AR=${HOST}-ar
AS=${HOST}-as
CC=${HOST}-gcc

PREFIX=/usr
EXEC_PREFIX=${PREFIX}
BOOTDIR=/boot
LIBDIR=${EXEC_PREFIX}/lib
INCLUDEDIR=${PREFIX}/include

CFLAGS='-O2 -g'
CPPFLAGS=''
LDFLAGS=''

STATICDIR="$(pwd)/src/static"
ISODIR="$(pwd)/build/isodir"
ISOFILE="$(pwd)/mivios.iso"
TMPDIR="$(pwd)/tmp"
PIDDIR="$(pwd)/pids"

# Configure the cross-compiler to use the desired system root.
SYSROOT="$(pwd)/build/sysroot"
CC="$CC --sysroot=$SYSROOT"

# Work around that the -elf gcc targets doesn't have a system include directory,
# if it was configured with --without-headers rather than with --with-sysroot.
if echo "$HOST" | grep -Eq -- '-elf($|-)'
then
    CC="$CC -isystem=$INCLUDEDIR"
fi

export MAKE HOST AR AS CC PREFIX EXEC_PREFIX BOOTDIR LIBDIR INCLUDEDIR CFLAGS CPPFLAGS SYSROOT CC
