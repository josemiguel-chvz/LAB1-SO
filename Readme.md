# Instrucciones

## Compilar

Compilar lab1

```
make -f makefile1
```

Compilar vis
```
make -f makefile2
```

## Test

Ejecutar los archivos de prueba

100 Visibilidades
```
./lab1 -i test100.csv -o propiedades.txt -d 200 -n 2 -b
```

10000 Visibilidades
```
./lab1 -i test10000.csv -o propiedades.txt -d 100 -n 4 -b
```

## Limpiar

```
make -f makefile1 clean
```

Compilar vis
```
make -f makefile2 clean
```
