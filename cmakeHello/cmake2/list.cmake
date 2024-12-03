cmake_minimum_required(VERSION 3.20)

#两种方法创建var
set(VAR1 a1 b2 b2)
message(${VAR1})

list(APPEND list1 hello world)
message(${list1})

#获取长度
list(LENGTH list1 len)
message(${len})

#查找
list(FIND list1 hello index)
message(${index})

#查找
list(FIND list1 world index)
message(${index})

#删除
list(REMOVE_ITEM list1 hello)
message(${list1})

#添加
list(APPEND list1 c++ go)
message(${list1})

#第二种添加方式 指定位置添加
list(INSERT list1 1 java)
message(${list1})

#反转
list(REVERSE list1)
message(${list1})

#排序
list(SORT list1)
message(${list1})