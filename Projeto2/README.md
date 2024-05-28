# O problema apresentado no código original é uma condição de corrida. Isso ocorre quando várias threads (ou processos) acessam e manipulam dados compartilhados concorrentemente, e o resultado das operações depende da ordem em que o acesso ocorre.
## Feito por Fellipe Jardanovski e Felipe Jiao

## Problema Específico:
    No código original, múltiplas threads tentam realizar a transferência de um valor da conta "from" para a conta "to". 
    A condição de corrida ocorre porque as threads acessam e modificam o saldo das contas sem qualquer sincronização. 
    Isso pode levar a inconsistências no saldo das contas, pois várias threads podem ler e modificar os saldos ao mesmo tempo, levando a operações incorretas.


## Exemplificação do Problema:
    Thread A e Thread B leem o saldo de from ao mesmo tempo. Suponha que from.saldo seja 100.
    Ambas as threads verificam se o saldo é suficiente e determinam que podem transferir o valor. 
    Cada uma decide transferir 10.
    Thread A realiza a operação primeiro: from.saldo é decrementado para 90.
    Thread B, com base na leitura anterior de 100, também decremente from.saldo para 90. 
    Na realidade, from.saldo deveria ser 80 após ambas as transferências

## Como compilar:
    Para executar o programa, é preciso primeiramente criar um arquivo com extensão .c, e colocar o código disponibilizado no arquivo.
    Após isso, compilar o programa utilizando o comando gcc -o nome nome.c, onde nome é o binário do arquivo. 
    Depois, ./nome para executar o programa compilado.

    Exemplo: se o nome do programa é Projeto.c, então para compilar, digite gcc -o Projeto Projeto.c

## Solução proposta:
    Para resolver o problema de condição de corrida, precisamos garantir que o acesso ao saldo das contas seja feito de forma atômica, ou seja, sem interferência de outras threads durante a operação. 
    Isso pode ser feito utilizando mutexes (mutual exclusions), que garantem que apenas uma thread possa acessar e modificar os saldos das contas de cada vez.

## Explicando a solução:
    Mutex: Um mutex é utilizado para garantir que apenas uma thread pode acessar o saldo das contas de cada vez. O mutex é inicializado com pthread_mutex_init e destruído com pthread_mutex_destroy.
    Exclusão Mútua: A função transferencia bloqueia o mutex antes de acessar e modificar os saldos (pthread_mutex_lock) e o libera após a modificação (pthread_mutex_unlock). 
    Isso garante que o bloco de código que verifica o saldo e realiza a transferência seja executado por apenas uma thread de cada vez.
    Thread Safety: Ao usar mutexes, garantimos que as operações de leitura e escrita nos saldos das contas são seguras, evitando resultados incorretos devido à condição de corrida.
    A conta c1 pode trocar de lugar com a conta c2, ou seja, A conta c1 está recebendo enquanto a conta c2 está enviando, mas em um certo momento, elas podem trocar
    de lugar, fazendo com que a conta c1 passe a enviar, enquanto a conta c2, passe a receber.
    Para isso, foi criado uma variável chamada transferencia_direction

## Conclusão:
    A condição de corrida ocorre quando múltiplas threads acessam dados compartilhados concorrentemente sem sincronização adequada, levando a resultados inconsistentes. 
    A utilização de mutexes resolve este problema garantindo que o acesso aos dados compartilhados seja feito de maneira atômica.

1[Execução do código](Captura.png)
