ARCH=$(shell uname -m)

build:
	-docker build -f Dockerfile.alpine -t permission-experiment-alpine .
	-docker build -f Dockerfile.debian -t permission-experiment-debian .
	-docker build -f Dockerfile.checker -t permission-experiment-checker .

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
	docker build -t sjmurdoch/permission-experiment:alpine-latest-$(ARCH) -f Dockerfile.alpine .
	docker build -t sjmurdoch/permission-experiment:debian-latest-$(ARCH) -f Dockerfile.debian .
	docker build -t sjmurdoch/permission-experiment:checker-latest-$(ARCH) -f Dockerfile.checker .
	docker push sjmurdoch/permission-experiment:alpine-latest-$(ARCH)
	docker push sjmurdoch/permission-experiment:debian-latest-$(ARCH)
	docker push sjmurdoch/permission-experiment:checker-latest-$(ARCH)

manifest:
	docker manifest create sjmurdoch/permission-experiment:alpine-latest \
	   --amend sjmurdoch/permission-experiment:alpine-latest-x86_64 --amend sjmurdoch/permission-experiment:alpine-latest-aarch64
	docker manifest push sjmurdoch/permission-experiment:alpine-latest
	docker manifest create sjmurdoch/permission-experiment:debian-latest \
	   --amend sjmurdoch/permission-experiment:debian-latest-x86_64 --amend sjmurdoch/permission-experiment:debian-latest-aarch64
	docker manifest push sjmurdoch/permission-experiment:debian-latest
	docker manifest create sjmurdoch/permission-experiment:checker-latest \
	   --amend sjmurdoch/permission-experiment:checker-latest-x86_64 --amend sjmurdoch/permission-experiment:checker-latest-aarch64
	docker manifest push sjmurdoch/permission-experiment:checker-latest

permutil: permutil.c
	gcc -Wall -o permutil permutil.c

.PHONY: build run attack attackroot workaround publish manifest
