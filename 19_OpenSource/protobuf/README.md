
## 测试版本

- 当前安装及测试版本 `3.13.0`


## 安装步骤

- 生成配置文件
  ```shell
    ./autogen.sh
  ```
- 进行配置
  ```shell
    ./configure --prefix=/usr/local/protobuf
  ```
- 编译安装
  ```shell
    make
    make install
  ```


## 利用 protoc 命令创建 .cpp 文件

- 安装完成后，在 `/usr/local/protobuf/bin` 下会有产生一个可执行命令 `protoc`。将该命令添加软链接到系统执行路径:
  ```shell
    ln -s /usr/local/protobuf/bin/protoc /usr/bin/protoc
  ```
- 创建关于 `.proto` 文件的 `.h` 和 `.cc` 文件
  ```shell
    protoc --cpp_out=. addressbook.proto
  ```
  如果 `addressbook.proto` 内部还依赖其他文件，可以通过 `-I` 或 `--proto_path` 指定依赖文件所在的最深层目录。


## 测试目录说明

- 1-first: 基本使用
- 2-second: 基本使用
- 3-third: mutable_xxx 使用
- 4-forth: 通过迭代器访问 repeated 结构
- 5-fifth: 映射表的使用
- 6-sixth: 类型描述
- 7-seventh: 类型反射(alpha)
- 8-eighth: 类型反射(beta)
- 9-ninth: option 使用(alpha)
- 10-tenth: option 使用(beta)
- 11-eleventh: 反射方式向 pb 结构的 repeated 字段添加元素
- 12-twelfth: 反射方式向 pb 结构的 map 字段中添加元素
- 13-thirteenth: arena 测试
- 14-fourteenth: FieldOptions 测试
