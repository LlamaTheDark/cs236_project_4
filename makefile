all: compile

compile:
	g++ -Wall -Werror -std=c++17 -g *.cpp vendor/lexer/*.cpp vendor/parser/*.cpp -o project_3


compile_win:
	cl /EHsc /WX *.cpp vendor/lexer/*.cpp vendor/parser/*.cpp /link /out:project_3.exe
	rm *.obj

clean:
	rm project_3.exe
