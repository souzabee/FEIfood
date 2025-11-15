# FEIfood

Este projeto implementa um sistema simples em **C** para gerenciamento de alimentos, criação de pedidos e avaliação de pedidos realizados. Ele foi desenvolvido com foco em boas práticas iniciais de programação, manipulação de arquivos e criação de menus interativos para terminal.

O sistema é dividido em etapas lógicas: **início**, **login/cadastro**, **menu principal**, **cadastro de pedidos**, **avaliação**, **consulta** e **busca de alimentos**.

---

##  Estrutura Geral do Programa

O sistema é organizado em diversas funções, cada uma responsável por uma parte específica da aplicação. A seguir, é apresentada uma explicação detalhada:

---

##  1. Função de Início (`inicio`)

Exibe o primeiro menu do programa, onde o usuário pode escolher entre:

* **Cadastrar-se**
* **Fazer login**
* **Sair do programa**

Essa função só termina quando o usuário seleciona a opção de sair.

---

##  2. Cadastro de Usuário (`cadastro`) e Login (`login`)

Essas funções fazem a leitura e gravação de usuários em arquivos externos. São utilizadas para armazenar logins simples.

* **Cadastro:** Recebe nome e senha e salva.
* **Login:** Verifica se os dados informados existem no arquivo.

São essenciais para liberar acesso ao menu principal.

---

##  3. Menu Principal (`menu`)

Após o usuário estar autenticado, ele acessa o menu com as opções:

* Cadastrar pedido
* Consultar pedidos
* Avaliar pedidos
* Buscar alimentos
* Sair

Cada opção chama uma função correspondente.

---

##  4. Cadastro de Pedidos (`cadastrar_pedido`)

Esta função é uma das partes mais importantes do sistema.

### ✔ Objetivo

Permitir que o usuário selecione alimentos existentes no arquivo **alimentos.txt** e os adicione ao seu pedido em **pedidos.txt**, cada pedido ficando em uma nova linha.

###  Como funciona

1. O arquivo `alimentos.txt` é aberto e lido.
2. Os alimentos disponíveis são mostrados.
3. O usuário digita o nome do alimento desejado.
4. O programa verifica se ele existe no arquivo.
5. Caso exista, ele é gravado no arquivo `pedidos.txt`.
6. O usuário pode digitar **0** para finalizar o pedido.
7. Após finalizar, automaticamente é aberta a função de **avaliação do pedido**.

Isso permite cadastrar e avaliar imediatamente.

---

##  5. Avaliação do Pedido (`avaliacao_pedido`)

Após cadastrar um pedido, o usuário pode avaliá‑lo.

### O que a função faz

* Pede ao usuário uma **nota (1 a 5)**.
* Recebe um **comentário opcional**.
* Grava tudo no arquivo **pedidos_avaliados.txt**.

O formato final salvo no arquivo segue o padrão:

```
Pizza Hamburguer - Nota: 5 - Comentário: Muito bom!
```

Isso permite criar um histórico organizado de pedidos avaliados.

---

##  6. Busca de Alimentos (`busca_alimento`)

Permite que o usuário veja a lista de alimentos cadastrados e busque um alimento específico pelo nome.

### Funcionamento

1. Exibe todos os alimentos disponíveis lendo apenas o nome (até o `;`).
2. Permite que o usuário digite o nome que deseja encontrar.
3. Se o alimento existir, suas informações completas são exibidas.

---

##  7. Estrutura dos Arquivos Utilizados

### **alimentos.txt**

Formato:

```
Pizza;Massa, queijo...;230kcal
Hamburguer;Carne, molho...;300kcal
```

### **pedidos.txt**

Cada pedido fica em uma nova linha:

```
Pizza Hamburguer
Feijoada
```

### **pedidos_avaliados.txt**

```
Pizza Hamburguer - Nota: 5 - Comentário: Excelente!
Feijoada - Nota: 4 - Comentário: Muito boa
```

---

##  8. Técnicas Importantes Utilizadas

* Manipulação de arquivos (`fopen`, `fgets`, `fprintf`, `rewind`)
* Uso de `sscanf` para separar informações
* Comparação de strings (`strcmp`)
* Laços `while` com condições de parada
* Repetição de menus interativos
* Organização modular do código em funções independentes

