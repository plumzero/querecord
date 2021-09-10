
from airflow import DAG
from airflow.operators.bash_operator import BashOperator
from datetime import datetime


default_args = {
    "owner": "airflow",
    "start_date": datetime(2021, 9, 7)
}

dag = DAG("Hello-World", 
        description="第一个DAG",
        default_args=default_args, 
        schedule_interval='25 * * * *')

t1 = BashOperator(task_id="hello", bash_command="echo 'Hello World, today is {{ ds }}'", dag=dag)
