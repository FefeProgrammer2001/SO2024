# O problema apresentado no código original é uma condição de corrida. Isso ocorre quando várias threads (ou processos) acessam e manipulam dados compartilhados concorrentemente, e o resultado das operações depende da ordem em que o acesso ocorre.
## Feito por Fellipe Jardanovski e Felipe Jiao

## Problema Específico:
    No código original, múltiplas threads tentam realizar a transferência de um valor da conta "from" para a conta "to". 
    A condição de corrida ocorre porque as threads acessam e modificam o saldo das contas sem qualquer sincronização. 
    Isso pode levar a inconsistências no saldo das contas, pois várias threads podem ler e modificar os saldos ao mesmo tempo, levando a operações incorretas.


## Exemplificação do Problema:
    Thread A e Thread B leem o saldo de from ao mesmo tempo. Suponha que from.saldo seja 100.
    Ambas as threads verificam se o saldo é suficiente e determinam que podem transferir o valor. Cada uma decide transferir 10.
    Thread A realiza a operação primeiro: from.saldo é decrementado para 90.
    Thread B, com base na leitura anterior de 100, também decremente from.saldo para 90. Na realidade, from.saldo deveria ser 80 após ambas as transferências

## Como compilar:
    Para executar o programa, é preciso primeiramente criar um arquivo com extensão .c, e colocar o código disponibilizado no arquivo.
    Após isso, compilar o programa utilizando o comando gcc -o nome nome.c, onde nome é o binário do arquivo. Depois, ./nome para executar o programa compilado.

    Exemplo: se o nome do programa é Projeto.c, então para compilar, digite gcc -o Projeto Projeto.c

1[Execução do código](Captura)
