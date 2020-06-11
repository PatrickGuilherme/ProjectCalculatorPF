#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int encontrar_TamArray(float valor)
{
	//Defini��es de variaveis inteiras, decimais e suas auxiliares
	int valor_Inteiro = (int)valor;
	float valor_Decimal = valor - (int)valor;
	int valor_aux = valor_Inteiro;
	float valor_aux_Decimal = valor_Decimal;
	int cont = 0;
	
	//Contando os espa�os para os numeros antes da virgula
	while(valor_aux >= 2)
	{
		valor_aux = valor_aux/2;
		cont++;	
	}
	
	//Caso n�o haja numeros antes da virgula, n�o sera contado 1 espa�o;
	if(cont!=0)cont++;
	
	//Contando os espa�os para os numeros depois da virgula
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
	//Defini��o de variaveis
	double valor_Decimal = valor - (int)valor;
	double valor_aux_Decimal = valor_Decimal;
	int tam = encontrar_TamArray(valor), i = 0;
	
	//Processo semelhante a convers�o binaria anteriormente
	while(true)
	{
		if(valor_aux_Decimal >= 1) valor_aux_Decimal -= (int)valor_aux_Decimal;
		if(valor_aux_Decimal == (int)valor_aux_Decimal) break;   
		valor_aux_Decimal = valor_aux_Decimal*16;
		//Se o valor for maior que 10 o converter� para seu o valor de sua letra na tabela ASCII
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
	//Defini��o de variaveis
	int posicaoVirgula;
	int valor_Inteiro = (int)valor;
	double valor_Decimal = valor - (int)valor;
	int valor_aux = valor_Inteiro;
	double valor_aux_Decimal = valor_Decimal;
	int tam = encontrar_TamArray(valor), i = 0;
	
	//Convers�o do numero inteiro para binario
	while(valor_aux >= 2)
	{
		//Primeiro ele pega o resultado do resto da divis�o entre o valor inteiro e 2
		//e o armazena no array.
		numCasas[i] = (int)valor_aux%2;
		
		//Ap�s isso vai modificar o valor_aux para sua divis�o com dois
		valor_aux = valor_aux/2;
		
		//Mudar� o espa�o no array
		i++;
	}
	
	//Caso o valor inteiro seja zero n�o ser� feito o processo de armazenamento do ultimo valor
	//e n�o ser� invertida o array
	if(i != 0)
	{
		numCasas[i] = (int)valor_aux;
		int j, aux[i + 1], k = 0;
		
		//Invers�o do array
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
	
	//Posi��o da virgula recebe o ultimo espa�o recebido representado pelo i
	posicaoVirgula = i;
	
	//Convers�o numero fracionario para binario
	while(true)
	{
		//Se o valor maior que 1 ira substrair 1
		if(valor_aux_Decimal >= 1) valor_aux_Decimal -= 1;
		//Se o valor for 0 inteiro ent�o o processo acaba
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
	//Declara��o de variaveis que dependem da precis�o
	int BIAS, tam_mantissa, tam_caracteristica, escolhaPrecisao;
	
	while(true)
	{
		//Defini��o da precis�o escolhida
		escolhaPrecisao = ImprimeMenu();
		
		//Caso seja 1 a precis�o � de 32bits
		if(escolhaPrecisao == 1)
		{
			BIAS = 127;
			tam_mantissa = 23;
			tam_caracteristica = 8;	
		}
		//Caso contrario ser� de 64bits
		else if(escolhaPrecisao == 2)
		{
			BIAS = 1023;
			tam_mantissa = 52;
			tam_caracteristica = 11;
		}
		//Caso seja 3 o programa fechar�
		else exit(0);
		
		//Declara��o das variaveis que compoem o resultado de acordo com a precis�o selecionada
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
		
		//Caso seja negativo o sinal ser� 1, no contrario sera zero
		if(numero < 0)
		{
			numero = numero * -1;
			SINAL = 1;	
		}
		else SINAL = 0;
		
		//Chamar� a fun��o para definir o tamanho exato do array do numero em formato binario
		int numCasas[encontrar_TamArray(numero)];
		int expoente;
		
		//Primeiramente o expoente � o valor encontrado na posi��o da virgula
		expoente = conversao_binario(numero, numCasas); 
	    	
	    //Se o expoente � igual a zero ter� que ser feito um processo para definir o valor negativo do expoente
	    if(expoente == 0)
		{
			//Vai ser realizado uma busca para encontrar o primeiro espa�o com valor 1
			for(int i = 0; i < encontrar_TamArray(numero); i++)
			{
				if(numCasas[i] != 1) expoente--;
				else break;
			}
		}
		
		//Elimina o espa�o desnecessario onde ficaria a virgula
		expoente -= 1;
	    printf("EXPOENTE: %d\n\n", expoente);
	    
	    //Convers�o para encontrar a caracteristica (BIAS + EXPOENTE)
	    conversao_binario(BIAS + expoente, CARACTERISTICA_AUX);
	    
	  	//Aqui estamos colacando os ZEROS necess�rios para preencher o espa�o de 8/11 bits das CARACTERISTICAS.  
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
		
		//Definir a posi��o inicial de incers�o dos valores de numCasas para MANTISSA
		int inicio;
		if(expoente < 0)
		{
			inicio = expoente * -1;
		}
		else inicio = 1;
		
		//Processo que passar� os valores para MANTISSA
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
		//Utiliza o atributo do printf(%X) para a convers�o da parte inteira para hexadecimal
		printf ("%X,", (int)numero);
		//Fun��o que converter� o numero fracionario para hexadecimal
		convesao_hexadecimal(numero, numCasas);
		getch(); 
		system("cls");
	}
	return 0;
}


