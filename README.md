# Letter
*Letter* é um jogo de adivinhação de palavras, inspirado no popular <a>[Termo](https://term.ooo)</a>. O objetivo é acertar a palavra secreta em um número limitado de tentativas, recebendo dicas visuais para guiar suas escolhas.

Projeto feito inteiramente utilizando a linguagem C e a biblioteca OpenGL para a matéria de Algoritmos e Programação Estruturada.

## Funcionalidades:
- **Palavras variadas:** as palavras são selecionadas aleatoriamente, proporcionando uma experiência dinâmica.
- **Sistema de pontuação:** mantenha um histórico de desempenho para acompanhar sua evolução.
- **Modo Infinito**: após completar as 5 fases iniciais, é liberado o "Modo Infinito", permitindo jogar com todas as palavras da base de dados.

## Compilando

### Windows

#### Pré-Requisitos
Certifique-se de ter o compilador *GCC* e o *make* instalados no ambiente.

#### Instruções

1. Clone o repositório:

```
git clone https://github.com/GabrielMF771/Letter
```

2. Acesse o diretório do projeto:

```
cd Letter
```

3. Compile o jogo utilizando o `make`:

```
make
```

4. Após a compilação, o executável será gerado no diretório `./bin/:`

```
./bin/Letter.exe
```

--- 

Ou simplesmente:

```
make run
```

O programa irá ser compilado e executado automáticamente.

## Opções de Desenvolvedor

- **Seta para cima:** Alterna entre fase 1 e fase 6

- **Seta para baixo:** Limpa as estatísticas salvas

- **Page Up:** Habilita e desabilita mostrar a resposta da fase no console