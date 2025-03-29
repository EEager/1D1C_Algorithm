from datetime import datetime, timedelta

utc_now = datetime.utcnow()
seoul_time = utc_now + timedelta(hours=9)
print(seoul_time.strftime('%Y-%m-%d'))
