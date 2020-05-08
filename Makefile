CFLAGS = -g -O0 -I. -std=c11
CFLAGS += -pedantic -Wall -Wno-unused-result
# CFLAGS += --coverage -ftest-coverage -fprofile-arcs
LDFLAGS = -lm

SRCS  = tex
SRCS += inipool pure_func
SRCS += funcs inputln
SRCS += texmath str printout print
SRCS += lexer fonts dviout expand scan error
CSRCS = $(addsuffix .c,${SRCS})
OBJS  = $(addsuffix .o,${SRCS})

# 输出二进制的文件名
EXEC_NAME = ttex


## 编译
all: ${EXEC_NAME}

${EXEC_NAME}: deps ${OBJS}
	${CC} ${CFLAGS} -o ${EXEC_NAME} ${OBJS} ${LDFLAGS}


## 测试与运行
debug: clean_test ${EXEC_NAME}
	cp ${EXEC_NAME} _test

# clean && run && load plainTeX
r: debug
	cd _test && ./${EXEC_NAME} plain

codecov:
	./${EXEC_NAME} test/helloworld
	gcov tex.c


## 清理
.PHONY: clean clean_test
clean:
	-rm -f ${EXEC_NAME} ${OBJS}
	-rm -f test/*.dvi test/*.log
	-rm -f *.gcno *.gcda *.gcov

clean_test: clean
	-rm -f _test/${EXEC_NAME} _test/*.dvi _test/*.log


## 自动产生依赖
deps: ${CSRCS}
	-rm -f deps.1
	for A in ${CSRCS} ; do \
		${CC} -MM $$A >> deps.1 ; \
	done
	cmp deps deps.1 || mv deps.1 deps

include deps
