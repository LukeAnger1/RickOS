### To run the iso file
qemu-system-x86_64 -cdrom x86_calculator.iso -monitor stdio
Or can use
./run.sh

It is also importnat to note ./run.sh compiles a number of things and if there is any error it may run with an older file and look like it works even if it doesnt (if doesnt run after ./clean.sh this is prob the issue)