C++FLAGS = -g
C++COMPILER = g++
OUT_FILE = main
GRAPH_FILE = graph

main: main.cpp
	 $(C++COMPILER) $(C++FLAGS) -o $(OUT_FILE) main.cpp

graph: $(GRAPH_FILE).txt	
	./$(OUT_FILE) >> $(GRAPH_FILE).txt
	dot -Tpng ./$(GRAPH_FILE).dot -o $(GRAPH_FILE).png
