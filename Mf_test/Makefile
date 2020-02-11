#TOP Makefile
CC := gcc					#编译工具
FLAGS = 					#编译规则
TAG = test					#目标文件

SRCS = $(wildcard src/libc/*.c)
SRCS += $(wildcard src/main/*.c)
OBJS = $(patsubst %.c, %.o, $(SRCS)) 

#TOP_DIR := ./		#顶层Makefile所在目录
OBJ_DIR := obj	#目标文件存放的目录
BIN_DIR := bin	#可执行文件存放的目录
SRC_DIR := src	#源文件路径

INC = -l ./include			#指定头文件检索的路径
#保存所有子Makefile的路径
#SUB_DIR := main src/libc src obj	
					
export CC TAG SRC_DIR OBJ_DIR BIN_DIR INC
#export将上述变量声明为全局变量，在子Makefile里面可以直接使用这些变量

all:CHECKDIR $(SRC_DIR) $(TAG)
#all能让多个目标依次执行
#直接make可以依次执行CHECKDIR和$(SUB_DIR)的编译命令
#若all后面没有参数，会把第一个目标作为默认的目标

CHECKDIR:					#检测并创建需要的目录					
	mkdir -p $(OBJ_DIR) $(BIN_DIR)
#执行对应目录中的Makefile文件
$(SRC_DIR):ECHO				#大写的C,离开目录前执行该目录下的Makefile	
	make -C $@						

$(TAG):		#生成目标文件，查找源文件目录下的所有.o文件编译生成目标到指定路径下
	$(CC) -o $(TAG) $(OBJS)
	#$(CC) -o $(addprefix $(BIN_DIR)/,$(TAG)) $$(find ./${SRC_DIR} -name '*.o')

ECHO:
	@echo $@

CLEANDIR:ECHO
	make -C $(SRC_DIR) clean

clean:
	rm $(OBJS)
