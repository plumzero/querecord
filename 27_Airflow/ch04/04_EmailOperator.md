
参考: [airflow.operators.email](https://airflow.apache.org/docs/apache-airflow/2.1.3/_api/airflow/operators/email/index.html#module-airflow.operators.email)

关键在于设置 airflow.cfg 关于邮箱部分的配置项。这里通过授权码方式进行设置。


```cfg
    [email]
    email_backend = airflow.utils.email.send_email_smtp
```
这个一般使用默认项。

这里以腾讯企业邮箱为例:
```cfg
    [smtp]
    smtp_host = smtp.exmail.qq.com
    smtp_starttls = False
    smtp_ssl = True
    smtp_user = fromwhere@gogo.org
    smtp_password = ur_password
    smtp_port = 465
    smtp_mail_from = fromwhere@gogo.org
    smtp_timeout = 30
    smtp_retry_limit = 5
```

DAG task 可以这样写:
```py
    send_email_task = EmailOperator(
        task_id='send_email_task',
        to='towhere@gogo.org',
        subject='Test Run',
        html_content='The quick brown fox jumps over the lazy dog',
        files=["/tmp/haha.txt"],
        dag=dag,
    )
```

[纯发送邮件示例](t/example_email_operator.py)

[错误时发送邮件示例](t/email_while_error.py)
