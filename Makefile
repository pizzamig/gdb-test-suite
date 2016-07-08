SUBDIR+=	boost-1
SUBDIR+=	boost-2
SUBDIR+=	popen

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
