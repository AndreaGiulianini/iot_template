FROM python:3.14-slim-bullseye

WORKDIR /app

COPY mqtt_to_logstash.py .

RUN pip install --no-cache-dir paho-mqtt requests

CMD ["python", "./mqtt_to_logstash.py"]
