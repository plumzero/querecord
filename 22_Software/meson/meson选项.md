
<strong> meson 有两种选项，内建选项(Build-in options) 和自定义选项(Universal options) 。 </strong>


## Build-in options

核心选项

| 选项 | 缺省值 | 描述 | 受限单机器 | 受限子工程 |
|:-----|:-------|:-----|:-----------|:-----------|
| backend {ninja, vs, vs2010, vs2015, vs2017, vs2019, xcode} | ninja | Backend to use | no | no |
| buildtype {plain, debug, debugoptimized, release, minsize, custom} | debug | Build type to use | no | no |
| debug | true | Debug | no | no |
| default_library {shared, static, both} | shared | Default library type | no | yes |
| optimization {0, g, 1, 2, 3, s} | 0 | Optimization level | no | no |
| pkg_config_path {OS separated path} | '' | Additional paths for pkg-config to search before builtin paths | yes | no |
| cmake_prefix_path | [] | Additional prefixes for cmake to search before builtin paths | yes | no |
| warning_level {0, 1, 2, 3} | 1 | Set the warning level. From 0 = none to 3 = highest | no | yes |
| werror | false | Treat warnings as errors | no | yes |

[more info about core options](https://mesonbuild.com/Builtin-options.html#core-options)


编译器选项

| 选项 | 可选值 | 缺省值 | 描述 |
|:-----|:-------|:-------|:-----|
| c_std | none, c89, c99, c11, c17, c18, c2x, gnu89, gnu99, gnu11, gnu17, gnu18, gnu2x | none | C language standard to use |
| cpp_std | none, c++98, c++03, c++11, c++14, c++17, c++2a, c++1z, gnu++03, gnu++11, gnu++14, gnu++17, gnu++1z, gnu++2a, vc++14, vc++17, vc++latest | none | C++ language standard to use |
| cpp_rtti | true, false | true | Whether to enable RTTI (runtime type identification) |

[more info about compiler options](https://mesonbuild.com/Builtin-options.html#compiler-options)


## Universal options

可以像下面这样指定:
```
    -Doption=value
```

或者将它们设置在 `meson.build` 文件 `project()` 指令的 `default_options` 字段中。
