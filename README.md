# ParticoesVariaveis
 Trabalho da disciplina de Sistemas Operacionais. C++

# Definição 
Neste trabalho foi desenvolvido um simulador simples para demonstrar o processo de alocacao por partições variaveis.
A ideia principal é fazer com que blocos de memoria sejam particionados variavelmente com o espaço necessario para o processo, para isso foi utilizado o metodo first-fit, quando este percorre a memoria se concentra em encontrar o primeiro bloco com tamanho suficiente para o processo.

# Estrutura
A classe main.cpp possui todo o codigo desenvolvido com suas respectivas funções. Foi implementado todo o codigo em uma classe só pensando no processo de correção que possa ser mais facil em vez de possuir varios bibliotecas para cada função do codigo.

Durante a execução do codigo, é mostrado em prompt de comando a memoria principal com seus blocos e a fila de processos, a quantidade de processos é variavel e pode ser alterada dentro do codigo na função principal.

# Execução 
O tempo de execução do programa possui uma estrutura de sleep, para efeitos de visualizacao dos blocos sendo fragmentados e os processos saindo da fila e entrando na memoria.




