# Define the Oracle libraries and flags
ORACLE_LIBS := -L${ORACLE_HOME}/lib -lclntsh -lpthread -ldl -lm -lecpg
CFLAGS := -g

# Define the list of Pro*C source files
PRO_C_FILES := hello.pc ctx_shared.pc ctx_local.pc

# Define the list of targets
TARGETS := $(PRO_C_FILES:.pc=)

# Default target
ALL: $(TARGETS)

# Pattern rule to compile Pro*C source files
%: %.pc
	proc iname=$<
	gcc $(patsubst %.pc, %.c, $<) -o $@ $(ORACLE_LIBS) $(CFLAGS)

# Clean target
.PHONY: clean
clean:
	rm -f *.lis *.c $(TARGETS)
