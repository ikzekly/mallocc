#!/bin/bash

if [[ "$(docker ps -aq -f name=mallocc -f status=running)" ]]; then
    docker stop mallocc > /dev/null
fi

if [[ "$(docker ps -aq -f name=mallocc -f status=exited)" ]]; then
    docker rm mallocc > /dev/null
fi

while getopts "b" flag; do
    case "${flag}" in
        b)
            docker build -t mallocc:1.0 .
            ;;
    esac
done

echo -e "\033[0;36mmallocc \$bash\033[0m\n\r"
docker run --name mallocc -ti --rm -v $(pwd):/opt/app mallocc:1.0 bash

