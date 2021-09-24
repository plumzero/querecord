from airflow import DAG
from subdag import subdag
from airflow.operators.dummy import DummyOperator
from airflow.operators.subdag import SubDagOperator
from airflow.utils.dates import days_ago

DAG_NAME = 'example_subdag_operator'

args = {
    'owner': 'airflow',
}

with DAG(
    dag_id=DAG_NAME, default_args=args, start_date=days_ago(2), schedule_interval="@once", tags=['example']
) as dag:

    start = DummyOperator(
        task_id='start',
    )

    section_1 = SubDagOperator(
        task_id='section-1',
        subdag=subdag(DAG_NAME, 'section-1', args),
    )

    some_other_task = DummyOperator(
        task_id='some-other-task',
    )

    section_2 = SubDagOperator(
        task_id='section-2',
        subdag=subdag(DAG_NAME, 'section-2', args),
    )

    end = DummyOperator(
        task_id='end',
    )

    start >> section_1 >> some_other_task >> section_2 >> end
