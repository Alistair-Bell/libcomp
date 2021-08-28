-include config.mk

SOURCES       = src/rle.c
OBJECTS       = ${SOURCES:.c=.o}
OUT           = comp
OUT_LIB       = lib${OUT}.a

S_SOURCES      = sandbox.c
S_OBJECTS      = ${S_SOURCES:.c=.o}
S_OUT          = sandbox

.c.o:
	$(CC) -c ${CONFIG_CC_FLAGS} $< -o $@

all: ${OUT}

${OUT}: ${OBJECTS}
	$(AR) rcs ${OUT_LIB} ${OBJECTS}

${S_OUT}: ${S_OBJECTS} ${OUT}
	$(CC) -L . -o $@ ${S_OBJECTS} -l${OUT}

clean:
	rm ${OUT_LIB}
	rm src/*.o
