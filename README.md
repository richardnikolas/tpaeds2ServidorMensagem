# TP 2 AEDS II - Servidor de Mensagens Instantâneas

<h2>1 - Descrição</h2>
O serviço de mensagens instantâneas permite o envio e recebimento de mensagens de texto em tempo real entre dois ou mais usuários. Este tipo de serviço se popularizou em meados dos anos 2000 através do mensageiro ICQ e posteriormente com o MSN. Atualmente, aplicativos como Gtalk, Facebook mensenger e Whatsapp já estão entre os meios de comunicação mais usados, superando o uso de SMS e e-mails.<br>
Uma das possíveis arquiteturas, de uma aplicação que oferece serviço de mensagens instantâneas via web, é o modelo cliente-servidor. Neste modelo, as mensagens são enviadas a um servidor que realiza algum tipo de processamento e as envia ao destinatário.
Por se tratar de uma aplicação distribuída com múltiplos usuários, pode ocorrer de uma ou mais mensagens chegarem ao mesmo tempo no servidor. Neste caso, o servidor deve possuir alguma política que determine qual destas mensagens será enviada primeiramente.<br>
Outro problema que pode acontecer, é o de algumas mensagens chegarem fora de ordem devido a problemas ou gargalos na comunicação entre o cliente o servidor. Um sistema de mensagens instantâneas deve garantir a ordem de entrega das mensagens pois, caso contrário, a conversa entre dois usuários poderia ficar sem sentido.

<h2>2 - O que deve ser feito</h2>
<p>Neste trabalho vocês devem implementar um simulador de um servidor de mensagens instantâneas via web. Este servidor deve permitir que pares de usuários troquem mensagens entre si. Antes de detalhar a lógica a ser implementada, algumas considerações: <br/><br/>
• Para simplificar, não faremos distinção da direção de comunicação entre um mesmo par de usuários. Ou seja, supondo a existência de dois usuários, A e B, só estamos interessados em saber se uma menagem foi trocada entre A e B, não queremos saber se foi uma mensagem enviada de A para B ou de B para A. <br/>
• Cada mensagem será composta por <b>3 campos</b>: identificador do par de usuários que está trocando a mensagem, identificador de ordem da mensagem, conteúdo da mensagem. O identificador de ordem da mensagem, informa se esta é a primeira, segunda, terceira, ... ou a n-ésima mensagem trocada por aquela par de usuários. Esta informação será necessária para garantir a ordem de entrega das mensagens. </p><br>

<p>Por ser um trabalho de AEDSII e não de Redes de Computadores, só será necessário implementar as estruturas de armazenamento das mensagens e a política que define a ordem de envio das mensagens. O funcionamento básico da comunicação será o seguinte: <br/><br/>
• As mensagens são entregues ao servidor em lotes (conjuntos com uma ou mais mensagens); <br/>
• Durante o recebimento de cada lote, o servidor armazena estas mensagens em listas de esperas para que possam ser enviadas em uma próxima etapa. Cada par de usuários que está se comunicando possui uma lista de espera própria. Assim, cada mensagem do lote será armazenada na lista de espera referente ao par de usuários que está trocando aquela mensagem; <br/>
• Após o recebimento completo de cada lote, as mensagens estão prontas para serem enviadas aos destinatários. Neste momento, o servidor possui várias listas de esperas com várias mensagens em cada lista. Como mencionado, as mensagens podem chegar fora de ordem ao servidor mas devem ser entregues em ordem aos destinat´arios. Assim, cada lista de espera deve estar ordenada crescentemente de acordo com o identificador de ordem de suas mensagens. Note que não é necessário ordenar a lista, basta inserir as mensagens de maneira ordenada; <br/>
• O servidor irá agora, enviar todas as mensagens das listas de espera. Nesta simulação as mensagens serão enviadas sequencialmente. Para definir a ordem de envio deve ser respeitada a seguinte pol´ıtica de prioridade: O par de usuários que trocou menos mensagens até o momento terá prioridade sobre os outros. Em caso de empate entre dois ou mais pares, o par com menor identificador terá prioridade. Note que a prioridade é sobre o par e a cada envio de mensagem estas prioridades mudam; <br/>
• Cada mensagem ao ser enviada, deve ser removida de sua respectiva lista de espera; <br/>
• Após o envio de todas as mensagens nas listas de espera, o servidor receberá um novo lote de mensagens e o processo se repete. Note que os contadores de mensagens trocadas por cada par devem ser mantidos; <br/>
• Se um par de usuários não trocou nenhuma mensagem nos óltimos k lotes de mensagens, sua lista de espera deve ser liberada no servidor para evitar o consumo desnecessário de recursos; <br/>
• Pode ocorrer de um lote conter as mensagens, entre um mesmo par, com identificador de ordem 3 e 4 e a mensagem com identificador 2 ainda não tiver sido enviada e nem estar neste lote. Neste caso, o servidor deve manter as mensagens 3 e 4 na lista de espera e esperar pela chegada da mensagem 2 nos lotes posteriores; <br/>
• Um par de usuários pode iniciar uma conversa a qualquer momento e não necessariamente no primeiro lote de mensagens.</p><br>


<h2>2.1 Exemplo</h2>
Supondo que o simulador acabou de ser inciado, e receba o seguinte lote de mensagens. <br/>

```javascript
3 2 Estou fazendo agora
0 1 Olá, tudo bem com você?
1 2 Não
1 1 Você vem jantar hoje?
0 2 Tudo sim e você?
1 3 Vou ter que trabalhar até mais tarde
2 4 se você lembrar
3 1 Conseguiu fazer o TP?
3 3 Está muito fácil
```

Onde o primeiro inteiro identifica o par de usuários e o segundo a ordem da mensagem. Neste exemplo na mensagem: <br/>

```javascript
3 2 Estou fazendo agora
```

O 3 indica que o par que está trocando esta mensagem é o par de identificador 3, o 2 indica que esta foi a segunda mensagem trocada por este par e Estou fazendo agora é o conteúdo da mensagem. <br>

O servidor irá receber este lote, alocar 4 listas de espera de mensagens e distribuir as mensagens da seguinte forma:

```c
Par 0: [(1,Olá, tudo bem com você?), (2,Tudo sim e você?)]
Par 1: [(1,Você vem jantar hoje?), (2,Não), (3,Vou ter que trabalhar até mais tarde)]
Par 2: [(4,se você lembrar)]
Par 3: [(1,Conseguiu fazer o TP?), (2,Estou fazendo agora), (3,Esta muito fácil)]
```
Recebido todo o lote, ele deverá enviar as mensagens respeitando as restrições definidas na seção anterior. A principal restrição é que o par de usuários que trocou menos mensagens até agora, tem prioridade sobre os outros. Como nenhum par trocou nenhuma mensagem até agora todos possuem a mesma prioridade. O critério de desempate diz que em caso de empate, o par com menor identificador terá prioridade. Neste caso as mensagens serão enviadas na seguinte ordem:

```javascript
Ordem | Número de mensagens trocadas | Mensagem escolhida
1       [0,0,0,0] 0 1                  Olá, tudo bem com você?
2       [1,0,0,0] 1 1                  Você vem jantar hoje?
3       [1,1,0,0] 3 1                  Conseguiu fazer o TP?
4       [1,1,0,1] 0 2                  Tudo sim e você?
5       [2,1,0,1] 1 2                  Não
6       [2,2,0,1] 3 2                  Estou fazendo agora
7       [2,2,0,2] 1 3                  Vou ter que trabalhar até mais tarde
8       [2,3,0,2] 3 3                  Está muito fácil
```

<i>*Note que a mensagem "2 4 se você lembrar" não foi enviada pois as mensagens 1, 2, e 3 da conversa deste par ainda não foi enviada. *O vetor na segunda coluna representa o número de mensagens que cada par já trocou entre si. A primeira posição é referente ao par com identificador 0, a segunda ao par com identificador 1 e assim sucessivamente.</i>

<h2>3 Entrada e saída</h2>
<p>A entrada será realizada através da entrada padrão <b>stdin</b>. Primeiramente será informados um inteiro <i>1 <= k <= 1000</i> que indica o número máximo de lotes recebidos que um par de usuários pode ficar sem trocar mensagens. Exemplo: se k = 7, o servidor acabou de receber o 9º lote de mensagens e o par i só trocou mensagens no primeiro e segundo lote, a lista de espera deste par deverá ser
desalocada. <br/>
Posteriormente serão passados os lotes de mensagens. Cada lote se inicia com a string Lote i onde <i>1 <= i <= 10000</i> é o número do lote e termina com a string Fim. Dentro de cada lote serão passadas as mensagens. Cada mensagem será enviada em uma linha e contém três campos separados por ponto e virgula (;). O primeiro campo será um identificador inteiro do par de usuários que está trocando a mensagem, o segundo o identificador inteiro de ordem da mensagem e o terceiro o conteúdo: ID Par;ID Ordem;Conteudo. O tamanho máximo de conteúdo de uma mensagem é de 500 caracteres. <br/>
Para informar que não serão enviados mais lotes será passado uma linha contendo -1. <br/>
Exemplo de entrada com k = 10 e os dois lotes utilizados no exemplo anterior ficam da seguinte forma: </p>

```
10
Lote 1
3;2;Estou fazendo agora
0;1;Olá, tudo bem com você?
1;2;Não
1;1;Você vem jantar hoje?
0;2;Tudo sim e você?
1;3;Vou ter que trabalhar até mais tarde
2;4;se você lembrar
3;1;Conseguiu fazer o TP?
3;3;Esta muito fácil
Fim

Lote 2
2 2 Vou
2 3 leva na aula amanhã
0 3 Tudo bem tbm
4 2 Parabéns! Que dia vamos comemorar?
2 1 Vai precisar da grana?
4 1 Passei no vestibular!
3 4 Está mesmo
Fim
-1
```

<br>
<p>ESPECIFICAÇÃO COMPLETA NA PASTA <b>"ABOUT"</b></p>
