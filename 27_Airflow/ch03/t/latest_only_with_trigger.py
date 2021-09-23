
"""
Example LatestOnlyOperator and TriggerRule interactions
"""

# [START example]
import datetime as dt

from airflow import DAG
from airflow.operators.dummy import DummyOperator
from airflow.operators.latest_only import LatestOnlyOperator
from airflow.utils.dates import days_ago
from airflow.utils.trigger_rule import TriggerRule

with DAG(
    dag_id='latest_only_with_trigger',
    schedule_interval=dt.timedelta(hours=4),
    start_date=days_ago(1),
    tags=['example3'],
) as dag:

    latest_only = LatestOnlyOperator(task_id='latest_only')
    task1 = DummyOperator(task_id='task1')
    task2 = DummyOperator(task_id='task2')
    task3 = DummyOperator(task_id='task3')
    task4 = DummyOperator(task_id='task4', trigger_rule=TriggerRule.ALL_DONE)

    latest_only >> task1 >> [task3, task4]
    task2 >> [task3, task4]
# [END example]