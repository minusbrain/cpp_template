# To build the image use the following command:
#
#    docker build --build-arg HOST_USER=$USER --build-arg USER_ID=$(id -u) --build-arg GROUP_ID=$(id -g) -t cpp-builder:latest .
#
# To run the container and build the source code use these commands:
#
#    docker run --rm -it -v $HOME/dev/cpp_template:$HOME/prj -w $HOME/prj cpp-builder:latest
# Base Image
FROM alpine:3.16.2

# Meta info
LABEL description="CPP build environment"

ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

RUN apk add --no-cache build-base cmake gtest-dev

# This small setuid program changes the uid:groupid of
# user to match the on passed in via -u to docker run.
# When ID-Mapped mounts arrive remove this ugly workaround
# Reference: https://lwn.net/Articles/896255/
COPY useridinit.c /tmp/useridinit.c
RUN cd /tmp && gcc useridinit.c -o useridinit
RUN cp /tmp/useridinit /usr/local/bin/useridinit
RUN chmod 4555 /usr/local/bin/useridinit

COPY entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x  /usr/local/bin/entrypoint.sh

# Mirror host user inside container
ARG HOST_USER=build
ARG USER_ID=1000
ARG GROUP_ID=1000
RUN getent group ${HOST_USER} 2>/dev/null || addgroup -g ${GROUP_ID} $HOST_USER
RUN id ${HOST_USER} 2>/dev/null || adduser -D -u ${USER_ID} -G $HOST_USER --home /home/${HOST_USER} --shell /bin/bash ${HOST_USER}

ENV USER=$HOST_USER
USER $HOST_USER
WORKDIR /home/$HOST_USER

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
CMD [ "/bin/sh" ]
