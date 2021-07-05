#!/bin/bash
echo "start tranlate"
../core/translate
echo "Done trans, start uploading..."

echo "input your username:"
read your_username
echo "input your password"
read -s your_password
ftp -n home.ustc.edu.cn <<EOF
passive mode
user $your_username $your_password
cd public_html
put index.html index.html
bye
EOF
echo "Upload successfully."