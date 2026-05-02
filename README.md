# Generator šestkotniških labirintov
## Ideja
Idejo za projekt sem dobil iz dveh youtube videov
- https://www.youtube.com/watch?v=thOifuHs6eY
- https://www.youtube.com/watch?v=uctN47p_KVk

## Za pomoč sem uporabil:
- https://www.w3schools.com/cpp/cpp_ref_fstream.asp (za uporabo std::fstream)
- Google gemini (pomoč pri uporabi std::fstream in pisanju SVG datotek)

## Doseženi cilji
- funkcija, ki naredi 6-kotno polje z velikostjo stranice N
- funkcija, ki naredi skozi to polje natanko 1 naključno pot
- funkcija, ki robove celic polja nariše
- prestrukturiranje kode

## Preostali cilji
- možnost labirinta v obliki PNG
- možnost uporabe programa v CLI
- označevanje začetka in konca

## Problemi
- uporabljen algoritem je DFS, implementiran z rekurzijo, zato se program sesuje če je n > 100