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
	
	if(cont!=0)cont++;
	
	while(true)
	{
		if(valor_aux_Decimal >= 1) valor_aux_Decimal -= 1;
		if(valor_aux_Decimal == 0) break;
		valor_aux_Decimal = valor_aux_Decimal*2;
		cont++;
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
	if(i != 0)
	{
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
	}
	posicaoVirgula = i;
		
	while(true)
	{
		if(valor_aux_Decimal >= 1) valor_aux_Decimal -= 1;
		if(valor_aux_Decimal == 0) break;   
		valor_aux_Decimal = valor_aux_Decimal*2;
		numCasas[i] = (int)valor_aux_Decimal;
		i++;
	}
	
	return posicaoVirgula;	
}

int main()
{
	int BIAS = 127, SINAL, MANTISSA[23], CARACTERISTICA[8], CARACTERISTICA_AUX[8];
	
	for(int i = 0; i < 23; i++)
	{
		MANTISSA[i] = 0;
	}
	
	float numero;
	scanf("%f", &numero);
	
	if(numero < 0)
	{
		numero = numero * -1;
		SINAL = 1;	
	}
	else SINAL = 0;
	
	int numCasas[encontrar_TamArray(numero)];
	int expoente;
	expoente = conversao_binario(numero, numCasas); 
    
    if(expoente == 0)
	{
		for(int i = 0; i < encontrar_TamArray(numero); i++)
		{
			if(numCasas[i] != 1) expoente--;
			else break;
		}
	}
	
	expoente -= 1;
    printf("%d     %d\n", SINAL, expoente);
    conversao_binario(BIAS + expoente, CARACTERISTICA_AUX);
    
  	//Aqui estamos colacando os ZEROS necessários para preencher o espaço de 8 bits das CARACTERISTICAS.  
	int tam = 8 - encontrar_TamArray(BIAS + expoente);		
	int cont = 1, i = 0;
	for(i = 0; i < tam; i++)
	{
	  CARACTERISTICA[i] = 0;
	}
	int k = 0; 
	for(int j = i; j < 8; j++)
	{
	   CARACTERISTICA[j] = CARACTERISTICA_AUX[k];
	   k++;
	}
	
	int inicio;
	if(expoente < 0)
	{
		inicio = expoente * -1;
	}
	else inicio = 1;
	
	k = 0;
	for(int i = inicio; i < encontrar_TamArray(numero); i++)
	{
		MANTISSA[k] = numCasas[i];
		k++;
	}
	
	printf("%d", SINAL);
	printf(" ");
	for(int i = 0; i < 7; i++)
	{
		printf("%d", CARACTERISTICA[i]);
	}
	printf(" ");
	for(int i = 0; i < 23; i++)
	{
		printf("%d", MANTISSA[i]);
	}
	printf(" ");
	return 0;
}


