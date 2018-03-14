SUBDIR+=	boost-1
SUBDIR+=	boost-2
SUBDIR+=	hello-fork
SUBDIR+=	mthr-attach
SUBDIR+=	popen
SUBDIR+=	pthread-2
SUBDIR+=	system
SUBDIR+=	thread-fork
SUBDIR+=	thread-test

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

show-tests:
	@echo ${SUBDIR}
