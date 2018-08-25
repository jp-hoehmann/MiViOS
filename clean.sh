#!/usr/bin/env bash

#
# clean.sh
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
# Remove all build artifacts.
#

. ./config.sh

for project in ${PROJECTS}
do
    cd src/projects/${project}
    ${MAKE} clean
    cd ../../../
done

# Force used to keep the script from aborting if something could not be deleted.
rm -rf ${SYSROOT} ${ISODIR} ${ISOFILE}
