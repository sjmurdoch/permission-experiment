build:
	-docker build -f Dockerfile.alpine -t permission-experiment-alpine .
	-docker build -f Dockerfile.debian -t permission-experiment-debian .

run:
	@echo ">>> Testing alpine..."
	-docker run --rm -it -u user permission-experiment-alpine
	@echo "\n\n>>> Testing debian..."
	-docker run --rm -it -u user permission-experiment-debian

attack:
	@echo ">>> Running attack on alpine..."
	-docker run --rm -it --entrypoint /bin/sh -u user permission-experiment-alpine /app/attack.sh
	@echo "\n\n>>> Running attack on debian..."
	-docker run --rm -it --entrypoint /bin/sh -u user permission-experiment-debian /app/attack.sh

attackroot:
	@echo ">>> Running attack (root) on alpine..."
	-docker run --rm -it --entrypoint /app/permutil -u root permission-experiment-alpine -s 1000 1000 root_sekrit.txt
	@echo "\n\n>>> Running attack (root) on debian..."
	-docker run --rm -it --entrypoint /app/permutil -u root permission-experiment-debian -s 1000 1000 root_sekrit.txt

workaround:
	@echo ">>> Running attack on alpine (with workaround)..."
	-docker run --rm -it --entrypoint /bin/su -u 0 permission-experiment-alpine -l user -c /app/attack.sh
	@echo "\n\n>>> Running attack on debian (with workaround)..."
	-docker run --rm -it --entrypoint /bin/su -u 0 permission-experiment-debian -l user -c /app/attack.sh

publish:
	docker build -t sjmurdoch/permission-experiment:alpine-latest -f Dockerfile.alpine .
	docker build -t sjmurdoch/permission-experiment:debian-latest -f Dockerfile.debian .
	docker push sjmurdoch/permission-experiment:alpine-latest
	docker push sjmurdoch/permission-experiment:debian-latest

permutil: permutil.c
	gcc -Wall -o permutil permutil.c

.PHONY: build run attack attackroot workaround publish
