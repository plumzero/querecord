
from datetime import timedelta
from datetime import datetime
# The DAG object; we'll need this to instantiate a DAG
from airflow import DAG

from airflow.decorators import task
from airflow.sensors.filesystem import FileSensor

with DAG(
    'file_sensor',
    default_args= {
        'owner': 'airflow',
        'start_date': datetime(2021,11,8),
    },
    description='检测到文件生成即触发',
    schedule_interval='@daily',
    catchup=False,
    tags=['filesensor'],
) as dag:

    # 除了利用 Operator 创建任务之外，Airfow 也支持通过 @task 修饰器创建任务，另外 FileSensor 也是一种任务。
    @task()
    def extract_from_file():
        """
        #### Extract from file task
        A simple Extract task to get data ready for the rest of the data
        pipeline, by reading the data from a file into a pandas dataframe
        """
        order_data_file = '/tmp/order_data.csv'
        # order_data_df = pd.read_csv(order_data_file)
        print("检测到生成了文件: ", order_data_file)

    """
    params:
        filepath: File or folder name (relative to the base path set within the connection), can be a glob.
        fs_conn_id: reference to the File (path)
        poke_interval: Poke interval to check dag run status when wait_for_completion=True. (default: 60)
    """
    """
        FileSensor 的任务(不是DAG)，应该没有必要设置重试(比如没有必要设置 retries 和 retry_delay 参数)
    """
    file_task = FileSensor(task_id = 'check_file',
                           filepath = '/tmp/order_data.csv',
                           fs_conn_id='fs_default', # 需要通过 Web 页面 Admin -> Connections 创建
                           dag = dag,
                           poke_interval = 30,      # 每隔 30 秒检测一次文件是否存在。如果在 10:10:10 时刻检测，在 10:10:20 时刻生成了文件，则任务会在 10:10:40 时刻触发
                           timeout=60 * 20,         # 20 分钟超时内如果未检测到文件，则失败
                           )
    order_data = extract_from_file()
    
    file_task >> order_data
