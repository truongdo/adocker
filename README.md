# adocker
Instead of the simple wrapper approach in the master branch, this patch modify directly [the docker source code](https://github.com/docker/docker) .

## What's inside this patch? ##
This patch contains modified code of docker that make it possible to prevent users to mount folder that they don't have write permission on it.
The output is exactly as the simple wrapper program in __master__ branch, but this is more secure.

## Installation ##
1. Clones [Docker](https://github.com/docker/docker)
2. Checkout tag v1.11.2 `git checkout v1.11.2`
2. Applies this patch: `patch -p1 < docker.1.11.2.patch`
3. Builds docker using [this tutorial](https://docs.docker.com/v1.5/contributing/devenvironment/)
