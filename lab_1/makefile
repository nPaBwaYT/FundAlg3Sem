NUM=
EPS=
PAR=
all: m1 m2 m3 m4 m5
m1:
	gcc task_1.c -o output/solution_1 -lm
m2:
	gcc task_2.c -o output/solution_2 -lm
m3:
	gcc task_3.c -o output/solution_3 -lm
m4:
	gcc task_4.c -o output/solution_4
m5:
	gcc task_5.c -o output/solution_5 -lm
c1:
	rm -f output/solution_1
c2:
	rm -f output/solution_2
c3:
	rm -f output/solution_3
c4:
	rm -f output/solution_4
	rm -f resourses/out_*
c5:
	rm -f output/solution_5
c: c1 c2 c3 c4 c5
o1:
	./output/*1 $(NUM) -h
	./output/*1 $(NUM) -p
	./output/*1 $(NUM) -s
	./output/*1 $(NUM) -a
	./output/*1 $(NUM) -f
	./output/*1 $(NUM) -e
o2:
	./output/*2 $(EPS)
o3:
	./output/*3 $(PAR)
o4:
	./output/*4 $(PAR)
o5:
	./output/*5 $(EPS) $(NUM)
