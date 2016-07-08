SUBDIR+=	boost-1
SUBDIR+=	boost-2
SUBDIR+=	hello-fork
SUBDIR+=	popen
SUBDIR+=	thread-fork

.PHONY: build clean
.DEFAULT: build


build:
.for SUBD in ${SUBDIR}
	${MAKE} -C ${SUBD}
.endfor

clean:
.for SUBD in ${SUBDIR}
	${MAKE} -C ${SUBD} clean
.endfor
