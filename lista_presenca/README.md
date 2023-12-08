# Sistema de Registro de Presença com ESP/NodeMCU e Servidor Web

Este projeto utiliza um módulo ESP/NodeMCU para criar um servidor web com uma interface que permite aos usuários registrar e acompanhar presenças em um evento ou aula. O sistema é projetado para fornecer uma solução simples e eficaz.

## Requisitos

- Módulo ESP8266 (NodeMCU)
- Conexão Wi-Fi para o ESP8266
- Arduino IDE com suporte para ESP8266
- Capacidade de acessar o servidor web a partir de dispositivos conectados à mesma rede Wi-Fi

## Configuração

### ESP/NodeMCU

1. Conecte o sensor de presença ao NodeMCU conforme necessário.
2. Configure as informações de rede Wi-Fi no código do NodeMCU.
3. Carregue o código para o NodeMCU usando a Arduino IDE.


## Uso

1. Após carregar o código no NodeMCU, o dispositivo se conectará à rede Wi-Fi especificada.
2. Abra o monitor serial na Arduino IDE para verificar o endereço IP atribuído ao NodeMCU.
3. Acesse o endereço IP a partir de qualquer dispositivo na mesma rede Wi-Fi para acessar a interface web.
4. Na interface web, os usuários podem registrar suas presenças.

## Observações

- O código fornecido é um exemplo básico. Dependendo dos requisitos específicos, podem ser necessárias melhorias, como autenticação de usuários, armazenamento seguro de dados e personalização da interface web.
- Considere a segurança ao implementar um sistema como este, especialmente se estiver sendo usado em um ambiente público.
