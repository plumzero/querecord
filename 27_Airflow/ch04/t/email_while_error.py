
# The DAG object
from airflow import DAG

# Operators
from airflow.operators.bash import BashOperator
from airflow.operators.dummy import DummyOperator
from airflow.operators.python import BranchPythonOperator
from airflow.operators.email import EmailOperator
from airflow.utils.dates import days_ago


def branch_func(ti):
    xcom_value = int(ti.xcom_pull(task_ids='ur_task'))
    if xcom_value == 0:
        return 'normal_task'
    else:
        return 'email_task'

with DAG (
    "email_while_error",
    default_args = {
        'owner': 'airflow',
        'start_date': days_ago(1),
    },
    schedule_interval = '00 13 * * *',
    tags = ['example', 'BranchPythonOperator'],
) as dag:

    ur_task = BashOperator(
        task_id = 'ur_task',
        bash_command = 'expr 1 / 0; echo $?',       ## 将 expr 1 / 0 换成 exprt 1 / 1 测试非邮件流
        do_xcom_push=True,
        dag = dag,
    )

    email_task = EmailOperator(
        task_id = 'email_task',
        to = 'towhere@gogo.org',
        subject = '这是邮件标题',
        html_content = '这是邮件正文内容',
        files = [ "/tmp/231.txt" ],
        dag = dag,
    )

    branch_task = BranchPythonOperator(
        task_id = 'branch_task',
        python_callable = branch_func,
        dag = dag,
    )

    normal_task = DummyOperator(
        task_id = 'normal_task',
        dag = dag,
    )

    ur_task >> branch_task >> [email_task, normal_task]

