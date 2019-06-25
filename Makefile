find_srcs = $(wildcard $(DIR)/*.c)
CHAPTERS := Chapter1 Chapter2 Chapter3 Chapter4 Chapter5 Chapter6 Chapter7 Chapter8
EXERCISE_DIRS := $(foreach CHAPTER, $(CHAPTERS),$(addsuffix /Exercises ,$(addprefix ./, $(CHAPTER))))
SRCS := $(foreach DIR,$(EXERCISE_DIRS),$(find_srcs))

Os := $(sort $(patsubst %.c,%.o,$(SRCS)))
all:$(Os)
%.o:%.c
	@echo Compiling $@
	@gcc $^ -o $@ -lm
clean:
	rm -i $(patsubst %.c,%.o,$(SRCS))
