from nginx

RUN rm -r -f /etc/nginx/nginx.conf /etc/nginx/conf.d/default.conf /etc/nginx/sites-available/ /etc/nginx/sites-enabled/ /etc/nginx/conf.d
COPY nginx.conf /etc/nginx/nginx.conf

CMD nginx -c /etc/nginx/nginx.conf; sleep infinity