time ./program.exe < "jp/jp_public_entrada.txt" > out.o
diff -bB "jp/jp_public_sortida.txt" out.o > diff.o