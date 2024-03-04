Passo a passo de como adicionar um código fonte no Git Hub importado da AWS:

1. Instalar o git na instância da AWS utilizando o comando sudo yum install git
2. Utilizar o comando ssh-keygen para obter a chave SHA256 pública, que será salva em um diretório especificado dentro da AWS
3. Obter a chave RSA pública com o comando cat com o diretio onde foi salvo a chave SHA256 obtida com o ssh-keygen
4. Utilizando a chave RSA púlica gerada, no deploy key no Git Hub, criar uma nova key com a chave RSA da AWS
5. Com o comando git clone + o ssh do repositório criado no git hub para criar a conexão entre a instância da AWS e o repositório do Git Hub
6. Criar o arquivo README.md com as intruções de como realizar o envio dos arquivos na AWS para o Git
7. Criar um código fonte em qualquer linguagem de programação, como linguagem c ou c++ usando o comando touch nome_do_arquivo.c
8. Utilizar o comando sudo nano nome_do_arquivo.c para acessar o edito do arquivo
9. Com o comando sudo yum group install "Development Tools", é possível instalar o compilar da linguagem C, utilizada nesse caso
10. Após a escrita do código fonte com o Hello World, usar o comando gcc para compilar o arquivo em linguagem C
11. ./nome_do_arquivo para executar o programa compilado
12. Utilizar o comando git add para adicionar os arquivos README.md e o código fonte para entrarem na fila
13. O git commmit fecha o pacote de mudanças e adiciona uma mensagem
14. Por fim, o comando git push origin atualiza o branch, nesse caso o main, já com os arquivos adicionados na instância da AWS
