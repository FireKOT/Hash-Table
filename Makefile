main: main.o hashtable.o list.o hashfuncs.o hash_test.o hashTableFind.o
	@g++ -o $@ $^
	./$@

main.o: main.cpp
	@g++ -c -o $@ $< $(FLAGS) 

hashtable.o: hashtable.cpp hashtable.hpp
	@g++ -c -o $@ $< $(FLAGS)

list.o: list.cpp list.hpp
	@g++ -c -o $@ $< $(FLAGS)

hashfuncs.o: hashfuncs.cpp hashfuncs.hpp
	@g++ -c -o $@ $< $(FLAGS)

hash_test.o: hash_test.cpp hash_test.hpp
	@g++ -c -o $@ $< $(FLAGS)

hashTableFind.o: hashTableFind.s
	@nasm -f elf64 -o $@ $^



clear:
	rm -f main main.o hashtable.o list.o hashfuncs.o hash_test.o hashTableFind.o







FLAGS = -O1 -Wno-unused-result -mavx2 -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code\
 		-Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall\
		-g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2\
		-Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual\
		-Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits\
		-Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE 