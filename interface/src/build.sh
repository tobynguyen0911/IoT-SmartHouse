rm -r /data/*
npm run build
cp -r build/* /data

cp nginx.conf /etc/nginx/nginx.conf
nginx -s reload
