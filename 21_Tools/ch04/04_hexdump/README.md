
查看二进制文件(但不限于)的十六进制编码
```shell
    hexdump -e '16/1 "%02X " "\n"' a.out
    hexdump -e '16/1 "%02X " "  |  "' -e '16/1 "%_p" "\n"' en.txt
```
