build:
	-docker build -f Dockerfile.alpine -t permission-experiment-alpine .
	-docker build -f Dockerfile.debian -t permission-experiment-debian .
	-docker build -f Dockerfile.debalp -t permission-experiment-debalp .

run:
	-docker run --rm -it permission-experiment-alpine
	-docker run --rm -it permission-experiment-debian
	-docker run --rm -it permission-experiment-debalp

attack:
	-docker run --rm -it --entrypoint /bin/sh permission-experiment-alpine /app/attack.sh
	-docker run --rm -it --entrypoint /bin/sh permission-experiment-debian /app/attack.sh
	-docker run --rm -it --entrypoint /bin/sh permission-experiment-debalp /app/attack.sh

.PHONY: build run attack