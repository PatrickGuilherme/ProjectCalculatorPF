#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int encontrar_TamArray(float valor)
{
	//Definições de variaveis inteiras, decimais e suas auxiliares
	int valor_Inteiro = (int)valor;
	float valor_Decimal = valor - (int)valor;
	int valor_aux = valor_Inteiro;
	float valor_aux_Decimal = valor_Decimal;
	int cont = 0;
	
	//Contando os espaços para os numeros antes da virgula
	while(valor_aux >= 2)
	{
		valor_aux = valor_aux/2;
		cont++;	
	}
	
	//Caso não haja numeros antes da virgula, não sera contado 1 espaço;
	if(cont!=0)cont++;
	
	//Contando os espaços para os numeros depois da virgula
	while(true)
	{
		if(valor_aux_Decimal >= 1) valor_aux_Decimal -= 1;
		if(valor_aux_Decimal == 0) break;
		valor_aux_Decimal = valor_aux_Decimal*2;
		cont++;
	}
	
	//Retorna o contador
	return cont;
}

int convesao_hexadecimal(double valor, int* numCasas)
{
	//Definição de variaveis
	double valor_Decimal = valor - (int)valor;
	double valor_aux_Decimal = valor_Decimal;
	int tam = encontrar_TamArray(valor), i = 0;
	
	//Processo semelhante a conversão binaria anteriormente
	while(true)
	{
		if(valor_aux_Decimal >= 1) valor_aux_Decimal -= (int)valor_aux_Decimal;
		if(valor_aux_Decimal == (int)valor_aux_Decimal) break;   
		valor_aux_Decimal = valor_aux_Decimal*16;
		//Se o valor for maior que 10 o converterá para seu o valor de sua letra na tabela ASCII
		if(valor_aux_Decimal >= 10)
		{
			numCasas[i] = (int)valor_aux_Decimal + 55;
			printf("%c", numCasas[i]);
		}
		//Caso contrario insere o valor normalmente
		else
		{
			numCasas[i] = (int)valor_aux_Decimal;
			printf("%d", numCasas[i]);
		}
	}
}

int conversao_binario(double valor, int* numCasas)
{
	//Definição de variaveis
	int posicaoVirgula;
	int valor_Inteiro = (int)valor;
	double valor_Decimal = valor - (int)valor;
	int valor_aux = valor_Inteiro;
	double valor_aux_Decimal = valor_Decimal;
	int tam = encontrar_TamArray(valor), i = 0;
	
	//Conversão do numero inteiro para binario
	while(valor_aux >= 2)
	{
		//Primeiro ele pega o resultado do resto da divisão entre o valor inteiro e 2
		//e o armazena no array.
		numCasas[i] = (int)valor_aux%2;
		
		//Após isso vai modificar o valor_aux para sua divisão com dois
		valor_aux = valor_aux/2;
		
		//Mudará o espaço no array
		i++;
	}
	
	//Caso o valor inteiro seja zero não será feito o processo de armazenamento do ultimo valor
	//e não será invertida o array
	if(i != 0)
	{
		numCasas[i] = (int)valor_aux;
		int j, aux[i + 1], k = 0;
		
		//Inversão do array
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
	
	//Posição da virgula recebe o ultimo espaço recebido representado pelo i
	posicaoVirgula = i;
	
	//Conversão numero fracionario para binario
	while(true)
	{
		//Se o valor maior que 1 ira substrair 1
		if(valor_aux_Decimal >= 1) valor_aux_Decimal -= 1;
		//Se o valor for 0 inteiro então o processo acaba
		if(valor_aux_Decimal == 0) break;   
		//Caso contrario o processo de multiplicar o valor decimal por 2 continua
		valor_aux_Decimal = valor_aux_Decimal*2;
		//E armazenara o valor inteiro de valor aux decimal
		numCasas[i] = (int)valor_aux_Decimal;
		i++;
	}
	
	return posicaoVirgula;	
}

int ImprimeMenu()
{
	int valor;
	while(true)
	{
		printf("================================================================\n");
		printf("CALCULADORA DE PONTO FLUTUANTE\n");
		printf("================================================================\n\n");
		printf("Digite a precisao desejada: \n");
		printf("[1] 32bits   [2] 64bits  [3] SAIR\n");
		scanf("%d", &valor);
		if(valor == 1|| valor == 2 || valor == 3) break;
		else
		{
			printf("ORDEM INVALIDA");
			getch(); 
			system("cls");
		}
	}

	return valor;
}

int main()
{
	//Declaração de variaveis que dependem da precisão
	int BIAS, tam_mantissa, tam_caracteristica, escolhaPrecisao;
	
	while(true)
	{
		//Definição da precisão escolhida
		escolhaPrecisao = ImprimeMenu();
		
		//Caso seja 1 a precisão é de 32bits
		if(escolhaPrecisao == 1)
		{
			BIAS = 127;
			tam_mantissa = 23;
			tam_caracteristica = 8;	
		}
		//Caso contrario será de 64bits
		else if(escolhaPrecisao == 2)
		{
			BIAS = 1023;
			tam_mantissa = 52;
			tam_caracteristica = 11;
		}
		//Caso seja 3 o programa fechará
		else exit(0);
		
		//Declaração das variaveis que compoem o resultado de acordo com a precisão selecionada
		int SINAL, MANTISSA[tam_mantissa], CARACTERISTICA[tam_caracteristica], CARACTERISTICA_AUX[tam_caracteristica];
		
		//Preenchimento da mantissa com valores zeros
		for(int i = 0; i < tam_mantissa; i++)
		{
			MANTISSA[i] = 0;
		}
	
		//Scanea o numero a ser calculado
		system("cls");
		printf("|| DIGITE O NUMERO A SER CALCULADO ||\n");
		double numero;
		scanf("%lf", &numero);
		
		//Caso seja negativo o sinal será 1, no contrario sera zero
		if(numero < 0)
		{
			numero = numero * -1;
			SINAL = 1;	
		}
		else SINAL = 0;
		
		//Chamará a função para definir o tamanho exato do array do numero em formato binario
		int numCasas[encontrar_TamArray(numero)];
		int expoente;
		
		//Primeiramente o expoente é o valor encontrado na posição da virgula
		expoente = conversao_binario(numero, numCasas); 
	    	
	    //Se o expoente é igual a zero terá que ser feito um processo para definir o valor negativo do expoente
	    if(expoente == 0)
		{
			//Vai ser realizado uma busca para encontrar o primeiro espaço com valor 1
			for(int i = 0; i < encontrar_TamArray(numero); i++)
			{
				if(numCasas[i] != 1) expoente--;
				else break;
			}
		}
		
		//Elimina o espaço desnecessario onde ficaria a virgula
		expoente -= 1;
	    printf("EXPOENTE: %d\n\n", expoente);
	    
	    //Conversão para encontrar a caracteristica (BIAS + EXPOENTE)
	    conversao_binario(BIAS + expoente, CARACTERISTICA_AUX);
	    
	  	//Aqui estamos colacando os ZEROS necessários para preencher o espaço de 8/11 bits das CARACTERISTICAS.  
		int tam = tam_caracteristica - encontrar_TamArray(BIAS + expoente);		
		int cont = 1, i = 0;
		//Inicializar o array CARACTERISTICA com os zeros a esquerda
		for(i = 0; i < tam; i++)
		{
		  CARACTERISTICA[i] = 0;
		}
		//Acrecentar os valores convertidos de CARACTERISTICA_AUX para CARACTERISTICA
		int k = 0; 
		for(int j = i; j < tam_caracteristica; j++)
		{
		   CARACTERISTICA[j] = CARACTERISTICA_AUX[k];
		   k++;
		}
		
		//Definir a posição inicial de incersão dos valores de numCasas para MANTISSA
		int inicio;
		if(expoente < 0)
		{
			inicio = expoente * -1;
		}
		else inicio = 1;
		
		//Processo que passará os valores para MANTISSA
		k = 0;
		for(int i = inicio; i < encontrar_TamArray(numero); i++)
		{
			MANTISSA[k] = numCasas[i];
			k++;
		}
		
		printf("SINAL - CARACTERISTICA - MANTISSA\n");
		
		printf("%d", SINAL);
		printf(" ");
		for(int i = 0; i < tam_caracteristica; i++)
		{
			printf("%d", CARACTERISTICA[i]);
		}
		printf(" ");
		for(int i = 0; i < tam_mantissa; i++)
		{
			printf("%d", MANTISSA[i]);
		}
		printf("\n\n");
		
		printf("CONVERSAO HEXADECIMAL: ");
		//Utiliza o atributo do printf(%X) para a conversão da parte inteira para hexadecimal
		printf ("%X,", (int)numero);
		//Função que converterá o numero fracionario para hexadecimal
		convesao_hexadecimal(numero, numCasas);
		getch(); 
		system("cls");
	}
	return 0;
}


