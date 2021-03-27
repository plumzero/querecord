
测试覆盖你所写的测试是否执行到你所写的所有代码行

通过 gcov 来计算每行代码被程序执行的次数
```sh
  gcc -O0 -fprofile-arcs -ftest-coverge ...
```
编译过程中，每个源代码文件会产生一个或两个数据文件 `*.gcda` 和 `*.gcno`

运行 `gcov *.gcda` 。 `*.gcda` 将向 stdout 输出程序中可执行代码的被执行次数的百分比，并产生 `*.c.cov` 文件

`*.c.cov` 的第一栏将展示在你的测试中每个可执行行的被执行频率，并且将没有被执行的行用一堆 ##### 来标识。

测试示例
```sh
    vim makefile
    make ./coverage_test
    for i in *gcda; do gcov $i; done;
    grep -C3 '#####' *.c.gcov
```

可以通过 gcov 对热点代码进行分析优化，在程序调优时达到事半功倍的效果。
