make
./program.exe < "jp_test.txt" > out.mine.o
./pau.sh < "jp_test.txt" > out.pau.o

diff out.mine.o out.pau.o > diff2.o
