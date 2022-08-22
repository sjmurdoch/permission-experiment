# Experimenting with negative group permissions in Linux containers

This repository contains code for conducting experiments on how negative group permissions behave within containers (Docker, Kubernetes, etc).
For more details see my blog post on Bentham's Gaze:
[Vulnerability in Linux containers – investigation and mitigation](https://www.benthamsgaze.org/2022/08/22/vulnerability-in-linux-containers-investigation-and-mitigation/).

## Demonstration Docker files

In `permission-experiment` there are Dockerfiles implementing the demonstration for both Alpine Linux and Debian. These images include a proof-of-concept
attack script `attack.sh` and a utility program `permutil`. Run `make build` to build the Docker images. The other Makefile rules show how to run
various attack demonstration scenarios.

In the container run `./permutil -h` to see how this utility can be used.

This directory also includes `logging-runc` which 
implements part of the API for the `runc` low-level container runtime but saves a copy of the image used and logs command line arguments.
This can be used instead of the real `runc` to explore what the container image passed to `runc` looks like.

## Scanning for negative permissions

The `scanperms` directory contains a utility to recursively scan for files and directories with negative group permissions. Run `python3 scanperms.py -h`
to see how to use it.
