#./src/Makefile
SUB_DIR = main libc		#这里就添加源文件的目录结构

all:$(SUB_DIR)

$(SUB_DIR):ECHO
	make -C $@			#进入底层目录的Makefile

#这里这个echo比较神奇，因为SUB_DIR变量定义应是两个目录名，也不是绝对路径，
#如果被展开执行make -C main libc这是一个未知的路径，但是加入echo后就会变量make -C main和make -C libc就能遍历执行make -C
#这个也可以使用CLEANDIR:的执行规则遍历执行各个目录

ECHO:
	@echo $@


CLEANDIR:
	@for dir in $$(echo $(SUB_DIR)); \
	do make -C $$dir clean; \
	done
.PHONY:clean
clean:CLEANDIR