opt -S -instcombine tf.ll -o tf.o1.ll
opt -S -deadargelim tf.ll -o tf.o2.ll

clang -emit-llvm -S m.c -o m.1.ll
clang -cc1 -emit-llvm m.c -o m.2.ll

opt -mem2reg -S m.1.ll -o m.1-1.ll

llvm-as t.ll -o t.1.bc

llc t.1.bc -o t.1.s
clang -S t.1.bc -o t.2.s -fomit-frame-pointer

llvm-dis t.1.bc -o t.1-1.ll


clang ct.c -o ct.1.exe
clang ct.c -E > ct.1.txt
clang -cc1 ct.c -ast-dump > ct.ast.txt
clang ct.c -S -emit-llvm -o - > ct.out.txt
clang ct.c -S ct.c -o - > ct.o.txt


clang -emit-llvm -S lt1.c -o lt1.1.ll
clang -emit-llvm -S lt2.c -o lt2.1.ll
llvm-as lt1.1.ll -o lt1.1.bc
llvm-as lt2.1.ll -o lt2.1.bc
llvm-link lt1.1.bc lt2.1.bc -o lt.0.bc

lli lt.0.bc
