
# The DAG object
from airflow import DAG

# Operators
from airflow.operators.bash import BashOperator
from airflow.utils.dates import days_ago

with DAG (
    "jingle_example",
    default_args = {
        'owner': 'airflow',
        'start_date': days_ago(2),
    },
    schedule_interval = '3 10 * * *',
    tags = ['example', 'jinja'],
) as dag:

    # The execution date as YYYY-MM-DD
    # date = "{{ ds }}"
    t = BashOperator(
        task_id='test_env',
        bash_command='bash jinja_example.sh',
        dag=dag,
        # env={'EXECUTION_DATE': date}
        )

    t
