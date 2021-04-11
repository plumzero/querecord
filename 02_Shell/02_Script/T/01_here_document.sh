
#/usr/bin/env bash

### HERE document 内容必须保证前导为 Tab, 如果无法保证可以靠左边写，像下面这样

if [[ ! -f $luaconf ]]; then

cat <<-EOF > "out.txt"
#include <features.h>
#if defined(__UCLIBC__)
LIBC=uclibc
#elif defined(__dietlibc__)
LIBC=dietlibc
#else
LIBC=gnu
#endif
EOF

fi 
