# Arduino-Python Macro

Este projeto permite a interação entre um Arduino e um computador via porta serial para executar macros ou abrir programas em Python. Os botões conectados ao Arduino são mapeados para letras específicas e, quando pressionados, enviam essas letras pela porta serial para o computador, onde um script em Python aguarda para interpretar esses comandos.

## Requisitos

- Python 3.x
- Arduino IDE
- Arduino Uno (ou similar)
- Conexão USB entre o Arduino e o computador

## Configuração

### Arduino

1. Conecte os botões aos pinos definidos no código Arduino (`a_btn`, `b_btn`, `c_btn`, `d_btn`, `e_btn`, `f_btn`).
2. Carregue o código Arduino no seu Arduino Uno usando a Arduino IDE.

### Python

1. Instale a biblioteca serial para Python usando o seguinte comando:

    ```bash
    pip install pyserial
    ```

2. Modifique as variáveis `app_a`, `app_b`, ..., no script Python para os caminhos dos programas ou macros que deseja executar ao pressionar os botões correspondentes.

3. Certifique-se de que a porta serial definida em `arduino = serial.Serial(port='COM8', baudrate=9600, timeout=.1)` no script Python corresponda à porta COM à qual o Arduino está conectado.

## Uso

1. Execute o script Python.
   
    ```bash
    python keyboard.py
    ```

2. Pressione os botões conectados ao Arduino para executar as ações definidas nos programas/macro correspondentes no script Python.

## Notas

- Certifique-se de que as portas e os caminhos dos programas estejam corretamente configurados no script Python.
- Este é um exemplo básico e pode ser expandido para incluir mais botões ou ações conforme necessário.
