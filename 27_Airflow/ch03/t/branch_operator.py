
# The DAG object
from airflow import DAG

# Operators
from airflow.operators.bash import BashOperator
from airflow.operators.dummy import DummyOperator
from airflow.operators.python import BranchPythonOperator
from airflow.utils.dates import days_ago

from datetime import datetime

# import pendulum

# local_tz = pendulum.timezone("Asia/Shanghai")
# local_tz.convert(execution_date)

def branch_func(ti):
    xcom_value = int(ti.xcom_pull(task_ids='start_task'))
    if xcom_value >= 5:
        return 'continue_task'
    else:
        return 'stop_task'

with DAG (
    "example_test_branch_operator",
    default_args = {
        'owner': 'airflow',
        'start_date': days_ago(2),
    },
    schedule_interval = '3 10 * * *',
    tags = ['example', 'BranchOperator'],
) as dag:

# 更多请查看文档 UPDATING.md
# `BranchPythonOperator` will now return a value equal to the `task_id` of the chosen branch,
# where previously it returned None. Since it inherits from BaseOperator it will do an
# `xcom_push` of this value if `do_xcom_push=True`. This is useful for downstream decision-making.

    start_op = BashOperator(
        task_id='start_task',
        bash_command="echo 5",
        do_xcom_push=True,
        dag=dag,
    )

    branch_op = BranchPythonOperator(
        task_id='branch_task',
        python_callable=branch_func,
        dag=dag,
    )

    continue_op = DummyOperator(task_id='continue_task', dag=dag)
    stop_op = DummyOperator(task_id='stop_task', dag=dag)

    start_op >> branch_op >> [continue_op, stop_op]
