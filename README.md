# Markdown_to_Html
transfer makedown to html

## 用户使用说明

环境：Linux shell

在shell中，执行`cd uploader` ,进入`uploader`目录，在目录下执行`./uploader.sh` ，按照提示输入需要转换的文件名称，然后输入FTP服务器的用户名，然后输入密码，shell脚本完成自动上传。

```bash
➜  [uploader] git:(master) ✗ ./uploader.sh
start tranlate
Please input the directory of the target file:
[your markdown file path]
Done.

Done trans, start uploading...
input your username:
[your username]
input your password
[your password]
Passive mode on.
Upload successfully.
```

for example:

```
➜  [uploader] git:(master) ✗ ./uploader.sh
start tranlate
Please input the directory of the target file:
mdtt.md
Done.

Done trans, start uploading...
input your username:
wtf123456
input your password
Passive mode on.
Upload successfully.
```

在这个例子里面，文件mdtt.md是在当前uploader目录下的一个markdown文件，ftp服务器的用户名是wtf123456



## 编译说明

工具：GNU g++

在Linux shell中进入`core`目录。执行以下语句：

```bash
➜  [core] g++ -c parser.cpp fwriter.cpp fileIO.cpp main.cpp
➜  [core] g++ -o translate parser.o fileIO.o fwriter.o main.o include/constant.h include/fileIO.h include/fwriter.h include/parser.h
```

