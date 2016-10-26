#!/bin/bash

# Fernanda Jaiara Dellajustina, 18/04/2016 12:57:40

# variáveis definidas para este shell
cmp=gcc
src=bts
ver=v0.47
ext=c
param=" -Wall -O2 "

# apaga o binário antigo, se houver
rm -f $src-$ver

# monta a linha de compilação
cline="$cmp $param -fopenmp $src-$ver.$ext -o $src-$ver -lm $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10} ${11} ${12} ${13} ${14} ${15} ${16} ${17} ${18} ${19} ${20}"

# mensagem
echo ""
echo "-------------------------------------------------------------------------------------"
echo ""
echo Compilando com a linha de comando
echo ""
echo "$cline"

# compila
$cline

# gera um novo script para a mesma linha de compilação
echo $0 $* > ess-remake-$ver.sh
chmod +x ess-remake-$ver.sh

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
