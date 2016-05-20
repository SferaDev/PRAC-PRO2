make
./program.exe < "jp_test.txt" > out0.o
./privat1.sh < "jp_test.txt" > out1.o
#./privat3.sh < "jp_test.txt" > out3.o

diff out0.o out1.o > diff1.o
#diff out0.o out3.o > diff3.o
