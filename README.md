# MiViOS

The MInimum VIable Operating System, a tiny OS to act as the starting point for more ambitious projects. 

## LICENSE

**Copyright 2018 Jean-Pierre Höhmann (@NuvandaPV) <jean-pierre@höhmann.info>**

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this project except in compliance with the License.
A copy of the License should have been included with the software as `LICENSE`.
If not, you may obtain a copy of the License at:

> http://www.apache.org/licenses/LICENSE-2.0
  
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

## Build instructions

The build is meant to run inside the project directory (the same directory this file is in).

To get started quickly:

* Build a bootable CD-ROM image of the operating system by invoking `$ ./iso.sh`.
* Build a bootable CD-ROM image and run it in qemu by in invoking `$ ./qemu.sh`.  

The build is split into three steps, which are exposed as scripts, so they can be hooked into an IDE:

* Build the OS by invoking `$ ./build.sh`.
* After running the build, install the OS into a bootable CD-ROM image by invoking `$ ./install.sh`.
* After installing, run the OS in qemu by invoking `$ ./run.sh`.

There are two additional scripts that might be useful in certain situations:

* Copy all the headers into the `sysroot` (without compiling anything) by invoking `$ ./headers.sh`.
* Clean up the source tree by invoking `$ ./clean.sh`.
