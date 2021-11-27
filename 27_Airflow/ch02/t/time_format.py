
# Airflow 时间格式测试脚本
# 须在 Airflow 所在用户环境下运行

from airflow.utils import timezone
from datetime import datetime, timedelta
import datetime

def days_ago(n, hour=0, minute=0, second=0, microsecond=0):
    """
    Get a datetime object representing `n` days ago. By default the time is
    set to midnight.
    """
    today = timezone.utcnow().replace(
        hour=hour,
        minute=minute,
        second=second,
        microsecond=microsecond)
    return today - timedelta(days=n)
    
print(days_ago(2))

print(timezone.utcnow())

print(timezone.utcnow() - timedelta(days=1))