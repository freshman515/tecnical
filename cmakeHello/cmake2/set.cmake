cmake_minimum_required(VERSION 3.20)
set(VAR1 hello)
message(${VAR1})
message("-----------------------------")
#设置多个值
set(LISTVALUES hello world)
message(${LISTVALUES})


#path
message($ENV{PATH})

set(ENV{CXX} "g++")
message($ENV{CXX})

#unset
unset(ENV{CXX})
#message($ENV{CXX})