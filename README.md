# Heb12 Lite
Bible command line interface reader.  
Comes with instructions to compile and run from 1.44mb floppy.  

## Building on Linux
```
git clone --recurse-submodules https://code.heb12.com/heb12/heb12lite
./startup.sh
./a.out
```

## Installing from pre-built (FreeDOS)

### No floppy:
Extract the 7z file to desired location, that's it.

### With Floppy:
Get a bootable FreeDOS floppy (https://www.freedos.org/download/)

Download
these drivers:
XMGR.SYS
RDISK.COM
from http://optimizr.no-ip.org/dos/file/drivers.zip
and place them on the floppy.

Change your config.sys:
(You may not need the DOS part if
you already have that file)
```
DEVICE=XMGR /W
DOS=HIGH,UMB
```

Reboot to the floppy, and type these commands:
```
rdisk
C:
A:\7zdec x A:\heb12.7z
```
And then you are done. Type "Heb12" and type in a verse.
"John 3 16"
"Heb 4 12"
"Gen 1 1-10"

## Building from source (MS-DOS/FreeDOS):
```
Lorem
i586-pc-msdosdjgpp-gcc fbrp/fbrp.c bibles/web.c main.c -o main.exe
```


CWSDPMI by Charles W. Sandmann 1996-2010
