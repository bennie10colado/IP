import csv
import random


class ExtratordeProbabilidades:
    def __init__(self, nome_arquivo):
        self.arquivo = nome_arquivo
        self.receptaculo = []
        self.banco_de_dados = []
        # self.lista_nums_aleatorios = []

    def carregar_colunas(self, lista_colunas, quantidade):

        with open(self.arquivo, 'r', encoding='cp850') as arq:
            self.banco_de_dados = list(csv.DictReader(arq))
            dicionario = {}
            self.lista_nums_aleatorios = []
            self.receptaculo = []

            for i in self.banco_de_dados:
                for dic, value in i.items():
                    if dic in lista_colunas:
                        dicionario[dic] = value
                self.receptaculo.append(dicionario.copy())

            for j in range(quantidade):
                self.lista_nums_aleatorios.append(
                    random.choice(self.receptaculo))
            # print(self.lista_nums_aleatorios) #CORRETOR, SE QUISER VISUALIZAR ESTA LISTA NO CODIGO, SO TIRAR A #, E VERÁ CLARAMENTE A LISTA DE DICIONARIOS

        # fazer funcionalidade para verificar se determinada lista está vazia

    def descarregar(self):
        self.banco_de_dados.clear()
        print("Descarregada.")
        # print(self.banco_de_dados)

    def prob_apriori(self, caracteristica, value):

        self.linhas_tabela = 0
        contador_v = 0
        num_max = float(0)
        self.lista_aux = []
        self.lista_de_linha = []
        self.resultado = 0

        for linha in self.banco_de_dados:  # cada linha é um dict
            self.linhas_tabela += 1  # contador
            # print(linha) # cada linha de determinada coluna
            self.lista_de_linha.append(linha)

        for dicionarios in self.lista_de_linha:
            if dicionarios[caracteristica] == value:
                # print(dicionarios[caracteristica])
                contador_v += 1
                # print(contador_v)

        # **pode-se fazer um if aqui para se pegar apenas as linhas diferentes de ""

        for i in range(self.linhas_tabela):  # i é a contagem de linhas
            self.lista_aux.append(i)  # lista do numero de linhas
            # num_max sera o valor de baixo da divisao
            num_max = max(self.lista_aux) + 1

        self.resultado = (contador_v / num_max) * 100

        if num_max > 0:
            print('o resultado da probabilidade a priori é: {:.2f}%'.format(
                self.resultado))
        if num_max <= 0:
            print("nao se adicionou linhas ao sistema.")

    def prob_apriori_intervalo(self, caracteristica, inicio, fim):
        c_total = float(0)
        c_nums = float(0)

        lista_valor_inteiro = []
        lista_nums_especifico = []

        for dicionarios in self.lista_nums_aleatorios:
            if dicionarios != "":
                # verifica se o dado é de fato da coluna requerida
                lista_nums_especifico.append(dicionarios[caracteristica])

        for linha in lista_nums_especifico:

            if linha != "":  # retira os ex: odometers = ''
                lista_valor_inteiro.append(int(linha))
                c_total += 1

        for i in lista_valor_inteiro:
            if inicio < i < fim:
                c_nums += 1

        print('o resultado da amostra requisitada anteriormente é: {:.2f}%'.format(
            c_nums * 100 / c_total))

    def prob_condicional(self, caracteristica1, valor1, caracteristica2, valor2):
        count_c1 = float(0)
        count_c2 = float(0)
        c_aux1 = float(0)
        c_aux2 = float(0)
        lista_1 = []  # tem a coluna caracteristica 1
        lista_2 = []  # tem a coluna caracteristica 2

        for dicionarios1 in self.lista_nums_aleatorios:
            if dicionarios1 != "":
                lista_1.append(dicionarios1[caracteristica1])
        for linha in lista_1:
            count_c1 += 1
        c_aux1 = lista_1.count(valor1)
        #print('essa eh a porcentagem entre',valor1,'dentro de',caracteristica1,'com porcentagem igual a:',c_aux1 * 100/count_c1,'%')

        for dicionarios2 in self.lista_nums_aleatorios:
            if dicionarios2 != "":
                lista_2.append(dicionarios2[caracteristica2])
        for linha in lista_2:
            count_c2 += 1
        c_aux2 = lista_2.count(valor2)
        #print('essa eh a porcentagem entre',valor2,'dentro de',caracteristica2,'com porcentagem igual a:',c_aux2 * 100/count_c2,'%')

        porcentagem1 = c_aux1 * 100/count_c1
        porcentagem2 = c_aux2 * 100/count_c2

        if count_c1 != 0 or count_c2 != 0:
            print('o resultado da amostra requisitada anteriormente é: {:.2f}%'.format(
                porcentagem1*porcentagem2/count_c2))

        elif count_c1 == 0:
            print('nao existe caracteristica1 no banco de dados, ou houve um erro de digitação, ou nao foi escolhido pelo sorteio de dados.')

        elif count_c2 == 0:
            print('nao existe caracteristica2 no banco de dados, ou houve um erro de digitação, ou nao foi escolhido pelo sorteio de dados.')

        elif c_aux1 == 0:
            print('nao existe repetiçao do valor1')

        elif c_aux2 == 0:
            print('nao existe repeticao do valor2')
    # se o resultado der 0, ou o valor nao existe, ou nao foi encontrado pelo sorteio de dados,
    # pode-se tentar novamente solicitando uma quantidade maior de numeros

    def prob_dupla(self, caracteristica1, valor1, caracteristica2, inicio, fim):
        count_c1 = float(0)
        count_c2 = float(0)
        c_aux1 = float(0)
        c_aux2 = float(0)
        lista_1 = []  # tem a coluna caracteristica 1
        lista_2 = []  # tem a coluna caracteristica 2
        lista_int = []

        for dicionario1 in self.lista_nums_aleatorios:
            if dicionario1 != "":
                lista_1.append(dicionario1[caracteristica1])
        for linha in lista_1:
            count_c1 += 1

        c_aux1 = lista_1.count(valor1)


        for dicionarios2 in self.lista_nums_aleatorios:
            if dicionarios2 != "":
                lista_2.append(dicionarios2[caracteristica2])
        for linha2 in lista_2:
            if linha2 != "":
                try:
                    lista_int.append(int(linha2))
                    count_c2 += 1
                except:
                    print(f'{linha2} é um valor não-numérico da coluna {caracteristica2}, portanto será ignorado.')

        for i in lista_int:
            if inicio < i < fim:
                c_aux2 += 1

        proporcao1 = c_aux1 / count_c1
        proporcao2 = c_aux2 / count_c2

        if count_c1 != 0 or count_c2 != 0:
            print('o resultado da amostra requisitada anteriormente é: {:.2f}%'.format(proporcao1*proporcao2*100*100/count_c2))

        elif count_c1 == 0:
            print('nao existe caracteristica1 no banco de dados, ou houve um erro de digitação, ou nao foi escolhido pelo sorteio de dados.')

        elif count_c2 == 0:
            print('nao existe caracteristica2 no banco de dados, ou houve um erro de digitação, ou nao foi escolhido pelo sorteio de dados.')

        elif c_aux1 == 0:
            print('nao existe repetiçao do valor1.')

        elif c_aux2 == 0:
            print('nao existe repeticao dos valores dentro do intervalo.')


def menu():
    while True:

        print()
        print('=-=-=-=-=-=-=-=-=-=-=-= MENU =-=-=-=-=-=-=-=-=-=-=-=')
        print('1 - Inicializar e Carregar Colunas.                 |')
        print('2 - Descarregar Arquivo.                            |')
        print('3 - Calcular Probabilidade a priori.                |')
        print('4 - Calcular Probabilidade a priori com intervalos. |')
        print('5 - Calcular Probabilidade a priori condicional.    |')
        print('6 - Calcular Probabilidade a priori dupla.          |')
        print('0 - Sair.                                           |')
        print()
        option = int(input('Digite sua opção: '))

        if option == 1:
            print('=-=-=-=-=-=-=-=-=-=-=-= Carregar Colunas =-=-=-=-=-=-=-=-=-=-=-=')

            print('Seja Bem Vindo à inicialização do banco de dados\nPor observação, para que o programa tenha um bom funcionamento deve-se:')
            print('\n1)Iniciar aqui digitando a seguinte seu file.csv\n2)Carregar Colunas ao se digitar os nomes das colunas desejadas e a amostra de quantidade usada nas probabilidades\n3)Seguir com as probabilidades que quiser\n4)Bom proveito.')

            nome_arquivo = input('\nPor favor, digite o nome do seu arquivo csv: ')
            classe_chamada = ExtratordeProbabilidades(nome_arquivo)

            coluna = input('\nInsira o nome das colunas da base (separado por espaço): ')
            # é aconselhavel que se use muito numeros na aquisição de carregar colunas para que se tenha uma probabilidade mais apurada
            quantidade = int(input('\nInsira a quantidade de registros(int): '))
            lista_colunas = coluna.split(' ')

            classe_chamada.carregar_colunas(lista_colunas, quantidade)

        if option == 2:
            classe_chamada.descarregar()

        if option == 3:
            print('=-=-=-=-=-=-=-=-=-=-=-= Probabilidade a Priori =-=-=-=-=-=-=-=-=-=-=-=')
            print('\nProbabilidade a priori é o cálculo da probabilidade dos modelos específicos em relação ao total\nPor favor, aguarde o término do cálculo, pode demorar de 1-2 minutos dependendo da base de dados.\nAgradecemos a paciência.')
            caracteristica = input('\nInsira a caracteristica(coluna) procurada: ')
            valor = input('\nInsira o valor procurado: ')

            classe_chamada.prob_apriori(caracteristica, valor)
            print('Inicializado.')

        if option == 4:
            print('=-=-=-=-=-=-=-=-=-=-=-= Probabilidade a Priori Com intervalo =-=-=-=-=-=-=-=-=-=-=-=')
            caracteristica = input('\nInsira a caracteristica(coluna) desejada: ')
            inicio = int(input('\nInsira o valor inicial do intervalo: '))
            fim = int(input('\nAgora insira o valor final do intervalo: '))
            classe_chamada.prob_apriori_intervalo(caracteristica, inicio, fim)

        if option == 5:
            print('=-=-=-=-=-=-=-=-=-=-=-= Probabilidade a Priori Coondicional =-=-=-=-=-=-=-=-=-=-=-=')
            caracteristica1 = input('\nInsira a caracteristica1(coluna) desejada: ')
            valor1 = input('\nInsira o valor1 procurado: ')

            caracteristica2 = input('\nInsira a caracteristica2(coluna) desejada: ')
            valor2 = input('\nInsira o valor2 procurado: ')
            classe_chamada.prob_condicional(caracteristica1, valor1, caracteristica2, valor2)

        if option == 6:
            print('=-=-=-=-=-=-=-=-=-=-=-= Probabilidade a Priori Dupla =-=-=-=-=-=-=-=-=-=-=-=')

            caracteristica1 = input('\nInsira a caracteristica1(coluna) desejada: ')
            valor1 = input('\nInsira o valor1 procurado: ')
            caracteristica2 = input('\nInsira a caracteristica2(coluna) desejada para se calcular seu intervalo(utilizar somente lista completas de inteiros): ')
            inicio = int(input('\nInsira o valor inicial do intervalo(int): '))
            fim = int(input('\nAgora insira o valor final do intervalo(int): '))

            classe_chamada.prob_dupla(caracteristica1, valor1, caracteristica2, inicio, fim)

        if option == 0:
            print('\nPrograma Finalizado...')
            break

menu()
