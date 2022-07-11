build:
	-docker build -f Dockerfile.alpine -t permission-experiment-alpine .
	-docker build -f Dockerfile.debian -t permission-experiment-debian .

run:
	-docker run --rm -it permission-experiment-alpine
	-docker run --rm -it permission-experiment-debian

attack:
	-docker run --rm -it --entrypoint /bin/sh permission-experiment-alpine /app/attack.sh
	-docker run --rm -it --entrypoint /bin/sh permission-experiment-debian /app/attack.sh

publish:
	docker build -t sjmurdoch/permission-experiment:alpine-latest -f Dockerfile.alpine .
	docker build -t sjmurdoch/permission-experiment:debian-latest -f Dockerfile.debian .
	docker push sjmurdoch/permission-experiment:alpine-latest
	docker push sjmurdoch/permission-experiment:debian-latest

.PHONY: build run attack
