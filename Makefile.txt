ok       := (echo -e "\033[1;32mOK\033[0m")
fail     := (echo -e "\033[1;31mfail\033[0m"; exit 1)
srcs=   ../Add.cpp \
		../BigInt.cpp \
		../Calc.cpp \
		../Multiply.cpp \
		../OperandPusher.cpp \
		../Power.cpp

objs=$(srcs:%.cpp=%.o)
incl=$(srcs:%.cpp=%.h)
ifndef CXX
CXX=g++
endif
ifndef CXXFLAGS
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
endif
INCLUDES+=-I../../../examples/ -I/var2/lopt/include

CXXFLAGS+= ${INCLUDES}

files    := $(incl) $(srcs) Handler.h main.cpp

PROGS := step1 step2 step3 step4 step5 step6 step7 step8 step9 step10 step11 step12 step13

.PHONY: clean $(PROGS)

all: ${PROGS}

step1:
	@for f in $(files); do \
		echo -n "verify $$f exists: "; \
		test -r $$f && $(ok) || $(fail); \
	done

step2: clean
	@echo -e "\033[1;32mtest constants mesa::one and mesa::zero\033[0m"
	c++ ${CXXFLAGS} ${@}.cpp ../BigInt.cpp -o $@ 
	./$@

step3: clean
	@echo -e "\033[1;32mtest default,string,long constructors\033[0m"
	c++ ${CXXFLAGS} ${@}.cpp ../BigInt.cpp -o $@ 
	./$@

step4: clean
	@echo -e "\033[1;32mtest equivalence overloads\033[0m"
	c++ ${CXXFLAGS} ${@}.cpp ../BigInt.cpp -o $@ 
	./$@

step5: clean
	@echo -e "\033[1;32mtest copy and move constructors and assignment operators\033[0m"
	c++ ${CXXFLAGS} ${@}.cpp ../BigInt.cpp -o $@ 
	./$@

step6: clean
	@echo -e "\033[1;32mtest BigInt + and += operators\033[0m"
	c++ ${CXXFLAGS} ${@}.cpp ../BigInt.cpp -o $@ 
	./$@

step7: clean
	@echo -e "\033[1;32mtest BigInt ++ operators\033[0m"
	c++ ${CXXFLAGS} ${@}.cpp ../BigInt.cpp -o $@ 
	./$@

step8: clean
	@echo -e "\033[1;32mtest BigInt * and *= operators\033[0m"
	c++ ${CXXFLAGS} ${@}.cpp ../BigInt.cpp -o $@ 
	./$@

step9: clean
	@echo -e "\033[1;32mtest BigInt pow function\033[0m"
	c++ ${CXXFLAGS} ${@}.cpp ../BigInt.cpp -o $@ 
	./$@

step10: clean
	@echo -e "\033[1;32mtest Command::OperandPusher::execute function\033[0m"
	c++ ${CXXFLAGS} ${@}.cpp ../BigInt.cpp ../OperandPusher.cpp -o $@ 
	./$@

step11: clean
	@echo -e "\033[1;32mtest Command::Add::execute function\033[0m"
	c++ ${CXXFLAGS} ${@}.cpp ../BigInt.cpp ../Add.cpp -o $@ 
	./$@

step12: clean
	@echo -e "\033[1;32mtest Command::Multiply::execute function\033[0m"
	c++ ${CXXFLAGS} ${@}.cpp ../BigInt.cpp ../Multiply.cpp -o $@ 
	./$@

step13: clean
	@echo -e "\033[1;32mtest Command::Power::execute function\033[0m"
	c++ ${CXXFLAGS} ${@}.cpp ../BigInt.cpp ../Power.cpp -o $@ 
	./$@

clean : 
	rm -f ${PROGS}






