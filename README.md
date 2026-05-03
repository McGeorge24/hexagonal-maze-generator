# Generator šestkotniških labirintov
## Uporaba CLI

`./maze <n> <tags> <arguments>`

> [!IMPORTANT] <br>
> n must ALWAYS be specified. n must be an integer.
```
Tags:
-s      specifies seed, used to generate the maze, can be of type integer or string <br>
        DEFAULT: random integer based on time <br>
-o      specifies name of the output file without extension <br>
        DEFAULT: maze <br>
-f      specifies export format. Options: PNG, SVG <br>
        DEFAULT: SVG <br>
-h      help <br>
```
## Ideja
Idejo za projekt sem dobil iz dveh Youtube videov
- https://www.youtube.com/watch?v=thOifuHs6eY
- https://www.youtube.com/watch?v=uctN47p_KVk

## Za pomoč sem uporabil:
- https://www.w3schools.com/cpp/cpp_ref_fstream.asp (za uporabo std::fstream)
- Google gemini (pomoč pri uporabi std::fstream in pisanju SVG datotek)
n must ALWAYS be an integer
## Doseženi cilji
- funkcija, ki naredi 6-kotno polje z velikostjo stranice N
- funkcija, ki naredi skozi to polje natanko 1 naključno pot
- funkcija, ki robove celic polja nariše
- prestrukturiranje kode
- označevanje začetka in konca
- naredi se tudi rešitev labirinta
- možnost uporabe programa v CLI

## Preostali cilji
- možnost labirinta v obliki PNG

## Problemi
- uporabljen algoritem je DFS, implementiran z rekurzijo, zato se program sesuje če je n > 100. Gemini mi je predlagal, da sam uporabim stack na katerega nalagam celice, ki jih moram obdelat in se ne zanašam na call stack, ki ga hitreje zmanjka.

## Predlagane izboljšave
### Boljša implementacija grafa/drevesa
Trenutno imam zelo kompleksno funkcijo, ki celoten graf z vsemi povezavami shrani v eno-dimenzionalni vector. Morda, bi bilo bolje, da uporabim map, kjer je ključ `std::pair<vrstica, polozaj_v_vrstici>`. Gemini predlaga 3d koordinatni sistem (kjer ima vsaka točka 6 sosedov (2 v vsaki od dimenzij)), ali pa nek q in r.