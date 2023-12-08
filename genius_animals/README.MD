# Jogo Genius com Arduino e Matriz de LED com Sons de Animais

Este projeto combina Arduino e Python para criar um jogo no estilo Genius. O Arduino controla uma matriz de LEDs, exibindo cores, enquanto o script em Python lida com efeitos sonoros. O usuário interage inserindo sequências correspondentes às cores exibidas.

## Requisitos

- Python 3.x
- Arduino IDE
- Arduino Uno (ou similar)
- Matriz de LEDs
- Alto-falante ou fones de ouvido
- Conexão via USB entre o Arduino e o computador

## Configuração

### Arduino

1. Conecte a matriz de LEDs ao Arduino Uno usando o pino especificado (por exemplo, `PIN 6`).
2. Carregue o código Arduino no Arduino Uno usando a Arduino IDE.

### Python

1. Instale a biblioteca Pygame para Python:

    ```bash
    pip install pygame
    ```

2. Ajuste os caminhos para os arquivos de som no script Python.

3. Certifique-se de que a porta serial especificada em `arduino = serial.Serial(port='COM7', baudrate=9600, timeout=.1)` no script Python corresponda à porta à qual o Arduino está conectado.

## Uso

1. Execute o script Python:

    ```bash
    python genius.py
    ```

2. Siga a sequência de cores exibidas na matriz de LEDs.

3. Insira sua resposta como uma sequência de números (por exemplo, 1,3,0) quando solicitado.

4. Ouça os efeitos sonoros correspondentes a cada cor.

5. O jogo fornecerá feedback sobre se sua sequência estava correta ou não.

6. Divirta-se jogando e tente superar sua pontuação!

## Observações

- Certifique-se de que a matriz de LEDs está corretamente conectada ao Arduino e funcionando.
- Ajuste os arquivos de som e caminhos no script Python para corresponder à sua configuração.
- Personalize o jogo conforme necessário, como alterar o número de cores ou o nível de dificuldade.
