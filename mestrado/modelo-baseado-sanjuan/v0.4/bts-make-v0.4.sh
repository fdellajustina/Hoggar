#!/bin/bash

# Fernanda Jaiara Dellajustina, 18/04/2016 12:57:40

# variáveis definidas para este shell
cmp=gcc
src=bts
ver=v0.42
ext=c
param=" -Wall -O2 "

# apaga o binário antigo, se houver
rm -f $src-$ver

# monta a linha de compilação
cline="$cmp $param -fopenmp $src-$ver.$ext -o $src-$ver -lm"

# mensagem
echo ""
echo "-------------------------------------------------------------------------------------"
echo ""
echo Compilando com a linha de comando
echo ""
echo "$cline"

# compila
$cline

# testa se gerou um novo binário / executável
if [ -f $src-$ver ] # existe o arquivo binário?
then
    echo ""
    echo "binário $src-$ver gerado com sucesso!"
    echo ""

    time ./$src-$ver

else
    echo ""
    echo "ERRO na compilação do arquivo $src-$ver??? Abortando..."
    echo ""
    # sai com erro 1
    exit 1
#    mcedit $src-$ver.$ext
fi

# apaga as variáveis temporárias do shell...
cmp=
ext=
ver=
src=
param=
cline=

# termina com erro 0, tudo certo!
exit 0
