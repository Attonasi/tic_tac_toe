targets = ttt-server

cfiles = final.h main.c tttgame.c rest_server.c json.c constructors.c

flags = -Wall -Werror -ljansson -lulfius

libpath = LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

all: $(targets)

$(targets): $(cfiles)
	gcc -o $(targets) $(cfiles) $(flags)

run: $(targets)
	gcc -o $(targets) $(cfiles) $(flags)
	$(libpath) ./$(targets)

copy_libs:
	mkdir -p libs
	cp /usr/local/lib/libjansson.so ./libs/
	cp /usr/local/lib/libulfius.so ./libs/
	cp /usr/local/lib/libyder.so ./libs/
	cp /usr/local/lib/liborcania.so ./libs/

docker_server_run: $(targets) copy_libs
	gcc -o $(targets) $(cfiles) $(flags)
	docker build -t $(targets) .
	docker run -i -t -p 8080:8080 $(targets):latest

clean:
	rm -rf $(targets) ./libs
	sudo docker ps -a | grep '$(targets)' | awk '{print $1}' | xargs docker container rm

