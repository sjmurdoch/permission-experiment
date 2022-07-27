build:
	-docker build -f Dockerfile.alpine -t permission-experiment-alpine .
	-docker build -f Dockerfile.debian -t permission-experiment-debian .

run:
	@echo ">>> Testing alpine..."
	-docker run --rm -it permission-experiment-alpine
	@echo "\n\n>>> Testing debian..."
	-docker run --rm -it permission-experiment-debian

attack:
	@echo ">>> Running attack on alpine..."
	-docker run --rm -it --entrypoint /bin/sh -u 1000 permission-experiment-alpine /app/attack.sh
	@echo "\n\n>>> Running attack on debian..."
	-docker run --rm -it --entrypoint /bin/sh -u 1000 permission-experiment-debian /app/attack.sh

publish:
	docker build -t sjmurdoch/permission-experiment:alpine-latest -f Dockerfile.alpine .
	docker build -t sjmurdoch/permission-experiment:debian-latest -f Dockerfile.debian .
	docker push sjmurdoch/permission-experiment:alpine-latest
	docker push sjmurdoch/permission-experiment:debian-latest

permutil: permutil.c
	gcc -Wall -o permutil permutil.c

.PHONY: build run attack
