all: run

run: tictactoe
	java -cp bin:./libs/* main.tictactoe

tictactoe: src/main/tictactoe.java
	javac -Xlint:deprecation -d bin -sourcepath src -cp ./libs/*:. src/main/tictactoe.java

clean:
	rm -rf bin/*