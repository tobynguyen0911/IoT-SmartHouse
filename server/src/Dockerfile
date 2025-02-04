FROM python
COPY . /app
WORKDIR "/app"
RUN python -m pip install -r requirements.txt
CMD python -m flask run --host=0.0.0.0