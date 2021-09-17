
使用 `BashOperator` 在 Bash Shell 环境下执行命令。

以[这个文件](example_bash_operator.py)为例。

```py
    run_this = BashOperator(
        task_id='run_after_loop',
        bash_command='echo 1',
    )
```

通常情况下，代码以非零返回值退出时，会产生一个 AiflowException，表示任务失败了。此时，相比于直接跳过，更可取的做法是以 `99` 作为退出码退出(或者为 `skip_exit_code` 赋值退出码)。
```py
    this_will_skip = BashOperator(
        task_id='this_will_skip',
        bash_command='echo "hello world"; exit 99;',
        dag=dag,
    )
```

[使用模板](https://airflow.apache.org/docs/apache-airflow/2.1.3/howto/operator/bash.html#templating)

