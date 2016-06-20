# adocker
This is the program that wrap the docker program  to restrict the docker share volume command. User can only mount  the host folder if they have write permission on it.

Check the docker daemon attack surface [security issues](https://docs.docker.com/engine/security/security/).

Examples:
The follow command with original docker will let user to mount the etc folder into container and having fully access to the content,

```docker run -it -v /etc:/etc ubuntu```

Using `adocker`, we can restrict the permission,

```adocker run -it -v /etc:/etc ubuntu```
-> output: You don't have write permission on "/etc:/data"
