make
./program.exe < "jp_test.txt" > out0.o
./privat1.sh < "jp_test.txt" > out1.o
./privat2.sh < "jp_test.txt" > out2.o

diff out0.o out1.o > diff1.o
diff out0.o out2.o > diff2.o
