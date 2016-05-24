make
time ./program.exe < "jp_public_entrada.txt" > out.o
diff "jp_public_sortida.txt" out.o > diff.o