Playing with the american fuzzy lop

http://lcamtuf.coredump.cx/afl/

http://lcamtuf.coredump.cx/afl/QuickStartGuide.txt

Experiment 1:
-------------
 
Launched an EC2 instance, m3.large, ubuntu 14.04.

Download xpdf 3.04:
ftp://ftp.foolabs.com/pub/xpdf/xpdf-3.04.tar.gz

Dependencies:
sudo apt-get install zlib1g-dev libpng-dev

Follow this post:
http://unix.stackexchange.com/questions/187752/xpdf-configure-warning-couldnt-find-motif-x

I also tried to download freetype and compil using afl-gcc. There will be an error related to libpng...

Compile xpdf using afl-gcc:

CC=/home/mingyi/Downloads/afl-2.10b/afl-gcc CXX=/home/mingyi/Downloads/afl-2.10b/afl-g++ ./configure --disable-shared --with-freetype2-includes=/usr/include/freetype2 

Then run the script.

Strangely, afl cannot finish one single pdf file. But xpdf can parse the files easily without afl. Why? 
