# adocker
Instead of the simple wrapper approach in the master branch, this patch modify directly [the docker source code](https://github.com/docker/docker) .

## Why I make this program? ##
Here is the situation:
- We have many users need to run `docker` on servers.
- The server has private data and important information, and users are restricted access to some data.
- Original `docker` allows users to mount any folder (share volume) on the host machine to docker containers. It does not support to add constrains on the share volume (see [security issues](https://docs.docker.com/engine/security/security/)).

## What this program can do? ##
- This program is just a wrapper that make sure user cannot mount shared volume that they does not have write permission.

## Examples ##
The follow command with original docker will let users to mount the `etc` folder into the container, and the user will have fully access to the content,

```docker run -it -v /etc:/etc ubuntu```

This is a serious problem when the host is shared among multiple users.

Now, using `adocker`, we can restrict the permission,

```adocker run -it -v /etc:/etc ubuntu```

The program will first check if the user have write permission on `/etc`, if they don't, the program
will be refused, and the below message is printed out
`You don't have write permission on "/etc"`.

## Installation ##
1. Clones [Docker](https://github.com/docker/docker)
2. Checkout tag v1.11.2 `git checkout v1.11.2`
2. Applies this patch: `patch -p1 < docker.1.11.2.patch`
3. Builds docker using [this tutorial](https://docs.docker.com/v1.5/contributing/devenvironment/)
