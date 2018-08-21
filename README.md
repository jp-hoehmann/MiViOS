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

* Clean up the source tree by invoking `$ ./clean.sh`.
* Install all the headers into the `sysroot` by invoking `$ ./headers.sh`.
* Build a bootable cdrom image of the operating system by invoking `$ ./iso.sh`.
* Build a bootable cdrom image and run it in qemu by in invoking `$ ./qemu.sh`.  
