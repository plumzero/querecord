
"""
Example LatestOnlyOperator and TriggerRule interactions
"""

# [START example]
from airflow import DAG
from airflow.operators.dummy import DummyOperator
from airflow.operators.latest_only import LatestOnlyOperator
from airflow.operators.bash import BashOperator
from airflow.utils import timezone
from datetime import timedelta

with DAG(
    dag_id='fixed_point_start',
    default_args={
        'owner': 'airflow',
        'start_date': timezone.utcnow() - timedelta(days=5),
    },
    description='定点触发，只运行最后一次',
    schedule_interval='15 10 * * 1-5',
    tags=['example', 'last_only'],
) as dag:

    latest_only = LatestOnlyOperator(
        task_id='latest_only',
        dag=dag,
    )

    shell_task = BashOperator(
        task_id='shell_task',
        bash_command='echo 1 >> /tmp/fixed_point.txt',
        dag=dag,
    )

    latest_only >> shell_task
# [END example]