#!/usr/bin/env bash

#
# debug.sh
#
# Created by Jean-Pierre Höhmann on 18-08-30.
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
# Background a debuggable instance of qemu running mivios.
#

. ./config.sh

mkdir -p ${PIDDIR}

# Workaround: kill existing qemu's
if [[ -f ${PIDDIR}/dbg.pid ]]
then
    ps -p $(<${PIDDIR}/dbg.pid) &> /dev/null \
        && kill -INT $(<${PIDDIR}/dbg.pid)
    rm ${PIDDIR}/dbg.pid
fi

# Run in qemu, stop the CPU and listen for a debugger on :1234.
./run.sh -S -s &
echo $! > ${PIDDIR}/dbg.pid

# Wait to give qemu some time to start.
sleep 2
