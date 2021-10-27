
import datetime

from airflow.models.dag import DAG
from airflow.operators.email import EmailOperator
from airflow.utils.dates import days_ago

with DAG(
    'example_email_operator',
    default_args={
        'owner': 'airflow',
        'start_date': days_ago(1),
    },
    schedule_interval='30 11 * * *',
    tags=['email', 'daily'],
) as dag:

    send_email_task = EmailOperator(
        task_id='send_email_task',
        to='airflow@example.com',
        subject='Test Run',
        html_content='The quick brown fox jumps over the lazy dog',
        files=["/tmp/231.txt"],
        dag=dag,
    )

    send_email_task
