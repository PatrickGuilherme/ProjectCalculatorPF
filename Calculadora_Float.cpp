#include <stdio.h>
#include <stdlib.h>

int encontrar_TamArray(float valor)
{
	int valor_Inteiro = (int)valor;
	float valor_Decimal = valor - (int)valor;
	int valor_aux = valor_Inteiro;
	float valor_aux_Decimal = valor_Decimal;
	
	int cont = 0;
	
	while(valor_aux >= 2)
	{
		valor_aux = valor_aux/2;
		cont++;	
	}
	
	cont++;
	
	while(true)
	{
		valor_aux_Decimal = valor_aux_Decimal*2;
		cont++;
		if(valor_aux_Decimal >= 1) valor_aux_Decimal -= 1;
		if(valor_aux_Decimal == 0) break;   
	}
	
	return cont;
}

int conversao_binario(float valor, int* numCasas)
{
	int posicaoVirgula;
	
	int valor_Inteiro = (int)valor;
	float valor_Decimal = valor - (int)valor;
	int valor_aux = valor_Inteiro;
	float valor_aux_Decimal = valor_Decimal;
	int tam = encontrar_TamArray(valor), i = 0;
	
	while(valor_aux >= 2)
	{
		numCasas[i] = (int)valor_aux%2;
		
		valor_aux = valor_aux/2;
		i++;
	}
	numCasas[i] = (int)valor_aux;
	
	int j, aux[i + 1], k = 0;
	
	for(j = i; j >= 0; j--)
	{
		aux[k] = numCasas[j];
		k++;		
	}
	for(j = 0; j <= i; j++)
	{
		numCasas[j] = aux[j];
	}
	
	i++;
	posicaoVirgula = i;
		
	while(true)
	{
		valor_aux_Decimal = valor_aux_Decimal*2;
		numCasas[i] = (int)valor_aux_Decimal;
		i++;
		if(valor_aux_Decimal >= 1) valor_aux_Decimal -= 1;
		if(valor_aux_Decimal == 0) break;   
	}
	
	return posicaoVirgula;	
}

int main()
{
	float numero;
	scanf("%f", &numero);
	int numCasas[encontrar_TamArray(numero)];
	int posicaoVirgula;
	
    posicaoVirgula = conversao_binario(numero, numCasas);
    printf("%d/n", posicaoVirgula);
    
    for(int i = 0; i < encontrar_TamArray(numero); i++)
	{
		printf("%d", numCasas[i]);
	}
    
	return 0;
}


