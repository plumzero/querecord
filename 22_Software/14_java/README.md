


Linux 安装 JDK 开发环境

### 提前告知

[Download Page](https://www.oracle.com/java/technologies/javase/javase-jdk8-downloads.html)

全包名称为: jdk-8u281-linux-x64.tar.gz

采用官方提供的二进制包安装，建议以 `root` 权限安装。


### 安装步骤

将 tarball 解压至 `/usr/local` 下:
```sh
    tar -zxvf jdk-8u281-linux-x64.tar.gz -C /usr/local/
```

在 `/etc/profile` 中添加如下配置:
```sh
    export JAVA_HOME=/usr/local/jdk1.8.0_281
    export JRE_HOME=${JAVA_HOME}/jre
    export CLASSPATH=.:${JAVA_HOME}/lib:${JRE_HOME}/lib
    export PATH=${JAVA_HOME}/bin:$PATH
```

更新:
```sh
    source /etc/profile
```

确认:
```sh
    java -version
```

### 编写程序测试

文件名称: HelloWorld.java
```java
    public class HelloWorld {
        public static void main(String[] args){
            System.out.println("Hello World!");
        }
    }
```

编译产生字节码文件:
```sh
    javac HelloWorld.java
```
会产生一个具有相同前缀名的字节码文件 `HelloWorld.class` 。

执行:
```sh
    java HelloWorld
```
预期会打印: `Hello World!` 。
