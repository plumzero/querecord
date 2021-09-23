"""
Example DAG demonstrating the usage of labels with different branches.
"""

from airflow import DAG
from airflow.operators.dummy import DummyOperator
from airflow.utils.dates import days_ago
from airflow.utils.edgemodifier import Label

with DAG("example_branch_labels", schedule_interval="@daily", start_date=days_ago(2)) as dag:

    ingest = DummyOperator(task_id="ingest")
    analyse = DummyOperator(task_id="analyze")
    check = DummyOperator(task_id="check_integrity")
    describe = DummyOperator(task_id="describe_integrity")
    error = DummyOperator(task_id="email_error")
    save = DummyOperator(task_id="save")
    report = DummyOperator(task_id="report")

    ingest >> analyse >> check
    check >> Label("No errors") >> save >> report
    check >> Label("Errors found") >> describe >> error >> report
