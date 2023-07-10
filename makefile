CC := g++
CFLAGS=-std=c++20 -Wall
BUILD_DIR := build
SRC_DIR := src
PROGRAM_DIR := program
INC_DIR = include

all : execution

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp	
	$(CC) $(CFLAGS) -c $< -o $@ 

$(BUILD_DIR)/baralho.o: $(SRC_DIR)/baralho.cpp include/baralho.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/maoJogador.o: $(SRC_DIR)/maoJogador.cpp include/maoJogador.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/monteCartasComer.o: $(SRC_DIR)/monteCartasComer.cpp include/monteCartasComer.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/monteCartasIniciais.o: $(SRC_DIR)/monteCartasIniciais.cpp include/monteCartasIniciais.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/monteCartasJogadas.o: $(SRC_DIR)/monteCartasJogadas.cpp include/monteCartasJogadas.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/cartas.o: $(SRC_DIR)/cartas.cpp include/cartas.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/cartasEspeciais.o: $(SRC_DIR)/cartasEspeciais.cpp include/cartasEspeciais.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/cartasEspeciaisPretas.o: $(SRC_DIR)/cartasEspeciaisPretas.cpp include/cartasEspeciaisPretas.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/cartasNumericas.o: $(SRC_DIR)/cartasNumericas.cpp include/cartasNumericas.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/jogador.o: $(SRC_DIR)/jogador.cpp include/jogador.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/bot.o: $(SRC_DIR)/bot.cpp include/bot.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/ciclo.o: $(SRC_DIR)/ciclo.cpp include/ciclo.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/sistema.o: $(SRC_DIR)/sistema.cpp include/sistema.hpp
	$(CC) $(CFLAGS) -c $< -o $@

execution:$(BUILD_DIR)/baralho.o $(BUILD_DIR)/maoJogador.o $(BUILD_DIR)/monteCartasComer.o $(BUILD_DIR)/monteCartasIniciais.o $(BUILD_DIR)/monteCartasJogadas.o $(BUILD_DIR)/cartas.o $(BUILD_DIR)/cartasEspeciais.o $(BUILD_DIR)/cartasEspeciaisPretas.o $(BUILD_DIR)/cartasNumericas.o $(BUILD_DIR)/jogador.o $(BUILD_DIR)/bot.o $(BUILD_DIR)/ciclo.o $(BUILD_DIR)/sistema.o $(BUILD_DIR)/main.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	del /Q "$(BUILD_DIR)\*.o" "execution.exe"