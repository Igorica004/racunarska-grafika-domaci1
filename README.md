U korenu projekta se već nalazi kompajliran program, tako da je moguće pokrenuti ga bez kompajliranja. Izvršna datoteka sa kojom se pokreće projekat se zove main.exe.

Projekat koristi CMake build sistem. CMake automatski prepoznaje Visual Studio 2022 kompajler ako je instaliran na računaru, ne znam koja je procedura za druge kompajlere.

Uputstvo za kompajliranje:
1. Otvoriti terminal u folderu projekta.
2. Pokrenuti sledeće komande (svaka linija je odvojena komanda):

(inicijalizacija cmake-a)
cd .\build\
cmake ..

(vracanje u koren projekta)
cd ..

(kompajliranje projekta)
cmake --build build

(pokretanje projekta)
.\build\Debug\main.exe

Opis projekta:
Projekat je imitacija poznate igrice za telefon Flappy Bird. Komande: Na space se skače, na 1,2,3,4 se menjaju nivoi. Svaki nivo ima drugačiji vizuelni efekat. Projekat je pravljen u C++ koristeći OpenGL.
