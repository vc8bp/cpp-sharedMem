BIN=./bin/


run: $(BIN)sharedMemTest
	@clear
	@./$(BIN)sharedMemTest

$(BIN):
	mkdir -p $(BIN)

$(BIN)sharedMemTest: main.cpp | $(BIN)
	g++ -o $(BIN)sharedMemTest main.cpp

reader: reader.cpp
	g++ -o $(BIN)reader reader.cpp


clean:
	rm -f $(BIN)*
