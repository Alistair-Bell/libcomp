-include config.mk

SOURCES       = src/rle.c
OBJECTS       = ${SOURCES:.c=.o}
OUT           = comp
OUT_LIB       = lib${OUT}.a

E_SOURCES      = example.c
E_OBJECTS      = ${E_SOURCES:.c=.o}
E_OUT          = example

.c.o:
	@echo "cc $@"
	@$(CC) -c ${CONFIG_CC_FLAGS} $< -o $@

all: ${OUT}

${OUT}: ${OBJECTS}
	@echo "ar ${OUT_LIB}"
	@$(AR) rcs ${OUT_LIB} ${OBJECTS}

${E_OUT}: ${OUT} ${E_OBJECTS}
	@echo "cc $@"
	@$(CC) -L . -o $@ ${E_OBJECTS} -l${OUT}

clean:
	rm ${OUT_LIB}
	rm src/*.o
