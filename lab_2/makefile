CС=gcc
CFLAGS= -Wall -Werror -Wextra
CLIBS= -lm

SOURCES=task_1.c task_2.c task_3.c
OUTPUT_DIR=./output
LIB_DIR=./my_lib
TEST_TEMPLATES_DIR=../test_templates
EXECUTABLES=$(SOURCES:.c=.out)
MY_LIBS=my_string.lib
BASH=bash


SUCCESS_CMD=$(BASH) $(TEST_TEMPLATES_DIR)/success_cmd
FAILED_CMD=$(BASH) $(TEST_TEMPLATES_DIR)/failed_cmd

SUCCESS_RFILE_CMD=$(BASH) $(TEST_TEMPLATES_DIR)/success_rfile_cmd

SUCCESS_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/success_ofile
FAILED_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/failed_ofile

SUCCESS_RFILE_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/success_rfile_ofile

SUCCESS_IFILE_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/success_ifile_ofile
SUCCESS_IFILE_RFILE_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/success_ifile_rfile_ofile
FAILED_IFILE_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/failed_ifile_ofile
FAILED_IFILE_RFILE_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/failed_ifile_rfile_ofile


.PHONY: all test clean

all: libs $(EXECUTABLES)

%.out: %.c
	$(CC) $(CFLAGS) $< $(CLIBS) ./mlb.lib -o $(OUTPUT_DIR)/$@

clean:
	rm -r -f $(OUTPUT_DIR)/*.out
	rm -r -f files/*_out.txt
	rm -f ./*.lib

libs: $(MY_LIBS)
	ar r ./mlb.lib $(LIB_DIR)/*.lib
	rm $(LIB_DIR)/*.lib

%.lib: $(LIB_DIR)/%.c
	$(CC) $(CFLAGS) -c $< $(CLIBS) -o $(LIB_DIR)/$@

# Принцип формирования названия выполняемого теста:
#
# (SUCESS|FAILED)[_IFILE][_RFILE](CMD|OFILE)
#		 1			2		3		 4
#
# 1){ОБЯЗАТЕЛЬНЫЙ} В зависимости от предполагаемого окончания теста мы выбираем либо успешный вариант - SUCCESS, либо провальный - FAILED 
# 2){ОПЦИОНАЛЬНЫЙ} При необходимости ввода в консоль программы (использвуя scanf или аналоги) добавляется суффикс _IFILE
# 3){ОПЦИОНАЛЬНЫЙ} Если программа предполагает наличие выходного файла с данными добавляется суффикс _RFILE
# 4){ОБЯЗАТЕЛЬНЫЙ} В зависимости от того однострочный или многострочный вывод в консоль ожидается у программы выбираем окончание CMD - для однострочного вывода и OFILE для многострочного
#


# Все тесты разделены на категории по результату работы программы и формату ввода:
#
# В случае если ввод в программу только с помощью аругментов командной строки:
# 	В случае если вывод в консоль у программы однострочный:
# 		1) Успешный с выводом в консоль (вывод сравнивается со строкой) - $(SUCCESS_CMD)
# 		2) Провальный с выводом в консоль (вывод сравнивается со строкой) - $(FAILED_CMD)
# 		3) Успешный с выводом в консоль и в файл (вывод сравнивается со строкой, а выходной файл с подготовленным файлом) - $(SUCCESS_RFILE_CMD)
#	
# 	В случае если вывод в консоль у программы многострочный:
# 		1) Успешный с выводом в консоль (вывод сравнивается со строками из файла) - $(SUCCESS_OFILE)
# 		2) Провальный с выводом в консоль (вывод сравнивается со строками из файла) - $(FAILED_OFILE)
# 		3) Успешный с выводом в консоль и в выходной файл (вывод сравнивается со строками из файла, а выходной файл с подготовленным файлом) - $(SUCCESS_RFILE_OFILE)
#
# В случае если ввод в консоль программы осуществляется из подготовленного файла а вывод у программы многострочный:  
# 	1) Успешный с вводом из файла, выводом в консоль (вывод сравнивается со строками из файла) - $(SUCCESS_IFILE_OFILE)
# 	2) Успешный с водом из файла, выводом в консоль и выходной файл (вывод сравнивается со строками из файла, а выходной файл с подготовленным файлом) - $(SUCCESS_IFILE_RFILE_OFILE)
# 	3) Провальный с вводом из файла, выводом в консоль (вывод сравнивается со строками из файла) - $(FAILED_IFILE_OFILE)
#


# Использование тестов:
#
# 1) $(SUCCESS_CMD) "<вызов исполняемого файла с его аргументами>" "<ожидаемый в консоль вывод>"
# 2) $(FAILED_CMD) "<вызов исполняемого файла с его аргументами>" "<ожидаемый код возврата отличный от 0>" "<ожидаемый в консоль вывод>"
# 3) $(SUCCESS_RFILE_CMD) "<вызов исполняемого файла с его аргументами>" "<ожидаемый в консоль вывод>" "<выходной файл>" "<файл с которым должен совпадать выходной файл>"
#
# 1) $(SUCCESS_OFILE) "<вызов исполняемого файла с его аргументами>" "<файл с ожидаемым в консоль выводом>"
# 2) $(FAILED_OFILE) "<вызов исполняемого файла с его аргументами>" "<ожидаемый код возврата отличный от 0>" "<файл с ожидаемым в консоль выводом>"
# 3) $(SUCCESS_RFILE_OFILE) "<вызов исполняемого файла с его аргументами>" "<файл с ожидаемым в консоль выводом>" "<выходной файл>" "<файл с которым должен совпадать выходной файл>"
# 
# 1) $(SUCCESS_IFILE_OFILE) "<вызов исполняемого файла с его аргументами>" "<файл данными которые вводятся в консоль через stdin>" "<файл с ожидаемым в консоль выводом>" 
# 2) $(SUCCESS_IFILE_RFILE_OFILE) "<вызов исполняемого файла с его аргументами>" "<файл данными которые вводятся в консоль через stdin>" "<файл с ожидаемым в консоль выводом>" "<выходной файл>" "<файл с которым должен совпадать выходной файл>"
# 3) $(FAILED_IFILE_OFILE) "<вызов исполняемого файла с его аргументами>" "<ожидаемый код возврата отличный от 0>" "<файл данными которые вводятся в консоль через stdin>" "<файл с ожидаемым в консоль выводом>"



#
# Ниже приведены примеры тестов. В выводе после теста должна быть краткая информация о том что это был за тест. "TEST N PASSED" это не информативно и принято не будет.
# Символ @ необходимо писать для подавления лишнего вывода в консоль при выполнении make файла.
#  

test_task_1: test_command_args_failed_1 test_command_args_success_1
	

test_command_args_failed_1:
	@$(FAILED_CMD) "./$(OUTPUT_DIR)/task_1.out -l" 1 "error 1: Wrong number of arguments"
	@$(FAILED_CMD) "./$(OUTPUT_DIR)/task_1.out -l abc abc" 1 "error 1: Wrong number of arguments"
	@$(FAILED_CMD) "./$(OUTPUT_DIR)/task_1.out -r" 1 "error 1: Wrong number of arguments"
	@$(FAILED_CMD) "./$(OUTPUT_DIR)/task_1.out -r abc abc" 1 "error 1: Wrong number of arguments"
	@$(FAILED_CMD) "./$(OUTPUT_DIR)/task_1.out -u" 1 "error 1: Wrong number of arguments"
	@$(FAILED_CMD) "./$(OUTPUT_DIR)/task_1.out -u abc abc" 1 "error 1: Wrong number of arguments"
	@$(FAILED_CMD) "./$(OUTPUT_DIR)/task_1.out -n" 1 "error 1: Wrong number of arguments"
	@$(FAILED_CMD) "./$(OUTPUT_DIR)/task_1.out -n abc abc" 1 "error 1: Wrong number of arguments"
	@$(FAILED_CMD) "./$(OUTPUT_DIR)/task_1.out -c" 1 "error 1: Wrong number of arguments"
	@$(FAILED_CMD) "./$(OUTPUT_DIR)/task_1.out -c 123" 1 "error 1: Wrong number of arguments"
	@$(FAILED_CMD) "./$(OUTPUT_DIR)/task_1.out p a" 2 "error 2: First argument must be a flag"
	@$(FAILED_CMD) "./$(OUTPUT_DIR)/task_1.out -p a" 3 "error 3: Flag is not supported"
	@$(FAILED_CMD) "./$(OUTPUT_DIR)/task_1.out -c a abc" 4 "error 4: Second argument must be uint"
	@$(FAILED_CMD) "./$(OUTPUT_DIR)/task_1.out -c -2 abc" 4 "error 4: Second argument must be uint"
	@$(FAILED_CMD) "./$(OUTPUT_DIR)/task_1.out -c /13 abc" 4 "error 4: Second argument must be uint"
	@$(FAILED_CMD) "./$(OUTPUT_DIR)/task_1.out -c 1.5 abc" 4 "error 4: Second argument must be uint"
	@$(FAILED_CMD) "./$(OUTPUT_DIR)/task_1.out -c 123213n1 abc" 4 "error 4: Second argument must be uint"
	@echo "TEST 1 PASSED"

test_command_args_success_1:
	@$(SUCCESS_CMD) "./$(OUTPUT_DIR)/task_1.out -l a" "1"
	@$(SUCCESS_CMD) "./$(OUTPUT_DIR)/task_1.out -l abc_" "4"
	@$(SUCCESS_CMD) "./$(OUTPUT_DIR)/task_1.out -r b" "b"
	@$(SUCCESS_CMD) "./$(OUTPUT_DIR)/task_1.out -r abc" "cba"
	@$(SUCCESS_CMD) "./$(OUTPUT_DIR)/task_1.out -u a" "a"
	@$(SUCCESS_CMD) "./$(OUTPUT_DIR)/task_1.out -u abcde123ABCDE" "aBcDe123ABCDE"
	@$(SUCCESS_CMD) "./$(OUTPUT_DIR)/task_1.out -n a" "a"
	@$(SUCCESS_CMD) "./$(OUTPUT_DIR)/task_1.out -n 1ab2!c3d@4e" "1234abcde!@"
	@$(SUCCESS_CMD) "./$(OUTPUT_DIR)/task_1.out -c 1 abc" "abc"
	@echo "TEST 2 PASSED"

test_task_2: test_ifile_ofile_success_2

test_ifile_ofile_success_2:
	@$(SUCCESS_IFILE_OFILE) "./$(OUTPUT_DIR)/task_2.out" "files/task_2_in_1.txt" "files/task_2_test_1.txt"
	@$(SUCCESS_IFILE_OFILE) "./$(OUTPUT_DIR)/task_2.out" "files/task_2_in_2.txt" "files/task_2_test_2.txt"
	@$(SUCCESS_IFILE_OFILE) "./$(OUTPUT_DIR)/task_2.out" "files/task_2_in_3.txt" "files/task_2_test_3.txt"
	@$(SUCCESS_IFILE_OFILE) "./$(OUTPUT_DIR)/task_2.out" "files/task_2_in_4.txt" "files/task_2_test_4.txt"
	@$(SUCCESS_IFILE_OFILE) "./$(OUTPUT_DIR)/task_2.out" "files/task_2_in_5.txt" "files/task_2_test_5.txt"
	@echo "TEST 3 PASSED"

test_task_3: test_ifile_ofile_success_3

test_ifile_ofile_success_3:
	@$(SUCCESS_IFILE_OFILE) "./$(OUTPUT_DIR)/task_3.out" "files/task_3_in_1.txt" "files/task_3_test_1.txt"
	@$(SUCCESS_IFILE_OFILE) "./$(OUTPUT_DIR)/task_3.out" "files/task_3_in_2.txt" "files/task_3_test_2.txt"
	@$(SUCCESS_IFILE_OFILE) "./$(OUTPUT_DIR)/task_3.out" "files/task_3_in_3.txt" "files/task_3_test_3.txt"
	@echo "TEST 4 PASSED"

test: test_task_1 test_task_2 test_task_3