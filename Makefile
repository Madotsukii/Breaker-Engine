#Copyright (C) 2015 <Madotsuki>

#This file is part of Breaker Engine.

#Breaker Engine is free software: you can redistribute it and/or modify
#it under the terms of the GNU Affero General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.

#Breaker Engine is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU Affero General Public License for more details.

#You should have received a copy of the GNU Affero General Public License
#along with Breaker Engine.  If not, see <http://www.gnu.org/licenses/>.

#Compiler instructions, can cross compile if needed...
ARCH=x86_64
VENDOR=pc
SYS=linux
ABI=elf

#Use clang++ you faggots, g++ sucks
CC=clang++ -target $(ARCH)-$(VENDOR)-$(SYS)-$(ABI) -std=c++14 -stdlib=libc++
CFLAGS=-O3 -c
LDFLAGS=
SOURCES=src/main.cpp src/core/io/file.cpp src/core/io/directory.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=BreakerEngine

all: $(SOURCES) $(EXECUTABLE)

unittest:

$(EXECUTABLE): $(OBJECTS)
	$(CC) -lc++abi$(LDFLAGS) $(OBJECTS) -o bin/$@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	find . -type f -name '*.o' -exec rm {} +

fresh:
	find . -type f -name '*.o' -exec rm {} +
	rm -rf bin/*
